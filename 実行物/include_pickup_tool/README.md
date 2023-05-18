# ver 1.2
+ コマンド形式の方法に変更  
```
Usage: include_pickup_tool.exe [OPTIONS] [CLASS_DIRS]...

Arguments:
  [CLASS_DIRS]...  クラスのヘッダファイルを格納しているフォルダパス  

Options:
  -i, --include-make-dir-path <PATH>  インクルードするフォルダを作る場所  
  -a, --all-pack                      ヘッダファイルを一つにまとめる  
  -h, --help                          Print help  
  -V, --version                       Print version  
```
# ver 1.1
+ 一つのヘッダファイルにまとめれるようにするコマンドを実装  
# ver 1.0
+ exeファイルがある階層にIncludeフォルダが作られる  
ヘッダファイルがあるフォルダをexeにドラッグアンドドロップするか、絶対パスを書くかのどちらかをすると始まります。  

作成者 RYOU753  
ver 1.2