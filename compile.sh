#! /usr/bin/bash

git submodules update

_source_files=$(find src/ -type f -name "*.cpp")
echo $_source_files
g++ -Wall -g -fsanitize=address -Iinclude -Ijson/single_include $_source_files -o outFile