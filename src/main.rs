use std::env;
use std::io;
use std::error::Error;
use std::io::Write;
use std::path;
use std::fs;
fn main() {
	//.hのがあるフォルダの絶対パス(or相対パス)を取得
	let args: Vec<String> = env::args().collect();
	println!("{:?}",args);
	//exeファイルの絶対パスを取得
	let exe_pathbuf = match env::current_dir(){
		Ok(exe_path) => exe_path,
		Err(e) => panic!("failed to get current exe path: {e}"),
	};
	//exeと同じ階層にIncludeフォルダを作成
	fs::create_dir("Include");
	let include_path = exe_pathbuf.join("Include");
	//最初からフォルダパスがあるか
	let path_list:Vec<String>;
	if is_target(&args)
	{
		println!("ターゲットあり");
		path_list = get_target_path2(&args);
	}
	else
	{
		println!("入力");
		path_list = get_target_path1();
	}
	//個別にヘッダをつくるか一戸にまとめるか
	println!("allで一つのファイルにまとめる");
	let cmd = get_input();
	//ヘッダファイルの絶対パスリスト
	let header_path_list = all_target(path_list);
	//Includeからみたヘッダファイルの相対パスリスト
	let mut is_first = true;
	for header_path in header_path_list.unwrap(){
		let relative = header_path.strip_prefix(&exe_pathbuf).unwrap();
		let relative_buf = path::Path::new("..").join(relative);
		let header_file = relative.file_name().unwrap();
		if cmd == "all" {
			create_all_header(&include_path.join("all_header.h"), relative_buf.to_string_lossy().to_string(),&mut is_first);
		}else{
			create_header(&include_path.join(header_file),relative_buf.to_string_lossy().to_string());
		}
		println!("{}",relative_buf.display());
	}
	//println!("{:?}",headerPathList);
	get_input();
}
fn create_all_header(path:&path::PathBuf,write:String,is_first:&mut bool)->std::io::Result<()>{
	let mut file: fs::File;
	if *is_first {
		file = fs::File::create(path)?;
		file.write_all(String::from("#pragma once\n").as_bytes());
		*is_first=false;
	}else{
		file = fs::File::options().append(true).open(path)?;
	}
	file.write_all(format!("#include \"{}\"\n",write).as_bytes());
	return Ok(());
}

fn create_header(path:&path::PathBuf,write:String)->std::io::Result<()>{
	let mut file = fs::File::create(path)?;
	file.write_all(format!("#pragma once\n#include \"{}\"\n",write).as_bytes())?;

	return Ok(());
}

fn all_target(args: Vec<String>) -> Result<Vec<path::PathBuf>, Box<dyn Error>>{
	println!("{:?}",args);
	let mut files:Vec<path::PathBuf> = Vec::new();
	for arg in args.iter(){
		dir_h(&mut files, &arg);
	}
	Ok(files)
}

fn dir_h(files:&mut Vec<path::PathBuf>,p :&String)-> std::io::Result<()>{
	let dir = fs::read_dir(p)?;
	for item in dir.into_iter() {
		let path = item?.path();
		if path.is_file() && (path.extension().unwrap() == "h"){
			files.push(path);
		}
		else if path.is_dir(){
			dir_h(files,&path.to_string_lossy().to_string());
		}
	}
	return Ok(());
}

fn get_target_path1() -> Vec<String>{
	let w = get_input();
	let path = path::Path::new(&w);
	println!("path_dir->({})",w);
	println!("存在:{}",path.is_dir());

	return vec![w];
}

fn get_target_path2(args: &Vec<String>) -> Vec<String>{
	let mut v = args.clone();
	v.remove(0);
	return v;
}

fn get_input() -> String {
	let mut input = String::new();
	io::stdin().read_line(&mut input).ok();
	return input.trim().to_string();
}

fn is_target(args: &Vec<String>) -> bool {
	args.len() >= 2
}
