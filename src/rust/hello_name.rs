# 0 "/home/adam/proj/github/lang-comparision/src/hello_name/rust.rs"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/adam/proj/github/lang-comparision/src/hello_name/rust.rs"







use std::io::{self, Write};

fn main(){

 print!("Enter your name: ");


 io::stdout().flush().unwrap();


 let mut name = String::new();
 io::stdin()
  .read_line(&mut name)
  .expect("Unable to read line");




 name.pop();


 println!("Hello {}!", name);

}
