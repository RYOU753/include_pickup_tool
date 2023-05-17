use std::env;
use std::io;
use std::error::Error;
use std::io::Write;
use std::os::windows::process;
use std::path;
use std::fs;
use std::path::{PathBuf,Path};
extern crate clap;
use clap::Parser;

/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
	/// クラスのヘッダファイルを格納しているフォルダパス
	class_dirs:Vec<PathBuf>,
	/// インクルードするフォルダを作る場所
	#[arg(short,long,value_name = "PATH")]
	include_path: Option<PathBuf>,
	/// ヘッダファイルを一つにまとめる
	#[arg(short,long,default_value_t = false)]
	all_pack:bool,
}

fn main() {
	//.hのがあるフォルダの絶対パス(or相対パス)を取得
	let args = Args::parse();
	println!("{:?}",args);

	//exeファイルの絶対パスを取得
	let exe_pathbuf = env::current_dir().unwrap_or_else(|err| {
		println!("exe not found path {err}");
		std::process::exit(1);
	});
	//exeと同じ階層にIncludeフォルダを作成
	const INCLUDE_DIR_NAME:&str = "Include";
	match fs::create_dir(args.include_path.clone().unwrap_or(Path::new(INCLUDE_DIR_NAME).to_path_buf())){
		Ok(()) => {
			println!("succes create Include dir");
		},
		Err(e) => {
			println!("failed create Include dir {e}");
			std::process::exit(1);
		},
	};
	let include_path = match args.include_path{
		Some(p) => p.join(INCLUDE_DIR_NAME),
		None => exe_pathbuf.join(INCLUDE_DIR_NAME),
	};
	//最初からフォルダパスがあるか
	/* let path_list:Vec<String>;
	if !is_target(&args.class_dirs)
	{
		println!("入力");
		path_list = get_target_path1();
	}else{
		path_list = args.class_dirs;
	} */
	//ヘッダファイルの絶対パスリスト
	let header_path_list = all_target(args.class_dirs.clone());
	//Includeからみたヘッダファイルの相対パスリスト
	let mut is_first = true;
	for header_path in header_path_list.unwrap(){
		let relative = header_path.strip_prefix(&exe_pathbuf).unwrap();
		let relative_buf = path::Path::new("..").join(relative);
		let header_file = relative.file_name().unwrap();
		if args.all_pack {
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

fn all_target(args: Vec<PathBuf>) -> Result<Vec<path::PathBuf>, Box<dyn Error>>{
	println!("{:?}",args);
	let mut files:Vec<path::PathBuf> = Vec::new();
	for arg in args.iter(){
		dir_h(&mut files, &arg);
	}
	Ok(files)
}

fn dir_h(files:&mut Vec<path::PathBuf>,p :&PathBuf)-> std::io::Result<()>{
	let dir = fs::read_dir(p)?;
	for item in dir.into_iter() {
		let path = item?.path();
		if path.is_file() && (path.extension().unwrap() == "h"){
			files.push(path);
		}
		else if path.is_dir(){
			dir_h(files,&path);
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

fn get_input() -> String {
	let mut input = String::new();
	io::stdin().read_line(&mut input).ok();
	return input.trim().to_string();
}

fn is_target(args: &Vec<String>) -> bool {
	args.len() >= 2
}
