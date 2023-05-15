use std::env;
use std::io;
use std::error::Error;
use std::path;
use std::fs;
fn main() {
    //.hのがあるフォルダの絶対パス(or相対パス)を取得
    let args: Vec<String> = env::args().collect();
    println!("{:?}",args);
    //exeファイルの絶対パスを取得
    match env::current_dir() {
        Ok(exe_path) => println!("Path of this executable is: {}",
                                 exe_path.display()),
        Err(e) => println!("failed to get current exe path: {e}"),
    };
    //exeと同じ階層にIncludeフォルダを作成
    fs::create_dir("Include");
    //最初からフォルダパスがあるか
    let mut pathList:Vec<String>;
    if is_target(&args)
    {
        println!("ターゲットあり");
        pathList = get_target_path2(&args);
    }
    else
    {
        println!("入力");
        pathList = get_target_path1();
    }
    let mut headerPathList = all_target(pathList);
    println!("{:?}",headerPathList);
    get_input();
}

fn all_target(args: Vec<String>) -> Result<Vec<path::PathBuf>, Box<dyn Error>>{
    print!("{:?}",args);
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
        if path.is_file(){
            files.push(path);
        }
        else if path.is_dir(){
            dir_h(files,&path.to_str().unwrap().to_string());
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
