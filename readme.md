# Task List
This is a small CLI program to manage a todo.txt

## About The Project

This was a single man(small) project that I had to do back in my 10th class at school.


## Project Structure
  src/
 │  ├──  main.cpp
 │  ├──  vars.h
 │  ├──  todo.h
 │  ├──  utils.h
 │  ├──  date.h
 │  └──  TodoList.h
 ├──  .gitattributes
 ├──  .gitignore
 ├──  LICENSE
 └──  readme.md

## Getting Started

### Prerequisites
You will need a c++ compiler like ``clangd`` or ``gcc``.

### Installation

1. Clone the repo and compile
```sh
git clone https://github.com/raj23689/CppTodo.git
cd src
g++ main.cpp -o todo
```
2. Move the file into a directory which is included in your PATH [ONLY FOR LINUX] 
```sh
mkdir -p ~/.local/bin
mv todo ~/.local/bin
```
** For Windows just compile the program and use it.

## Usage
You can pass commands for example like this without entering the program
```
todo -a example task due jul 12.
todo -r example task

todo -a ex -d 06/16
```
You can list tasks without entering the program
```
todo -l
```
Or enter the program and watch modifications as they happen
```
todo
```
You can pass multiple arguments separated by a string set in variables.h
```
Command: -a example -d 06/12 and another task -d 20:00
Command: -r example and 1 and 4-6
Command: -m 2 update -d dec and 3 another update
```


