#!/bin/bash

# 2 inputs (directories) 
#   

dir_start=$(pwd)
dir_1=$1
dir_2=$2

cd "$dir_1"

num_of_files_1=$(ls -1 "*.JPG" | wc -l)

cd $dir_start

cd $dir_2

num_of_files_2=$(ls -1 "*.JPG" | wc -l)

cd $dir_start

cd "$dir_1"

i=0

for filename in $(ls -1) 
do
    mv $filename "$i.JPG"
    i=$(($i+1))    
done

cd "$dir_start"

cd "$dir_2"

for filename in $(ls -1) 
do
    mv $filename "$i.JPG"
    i=$(($i+1))
done

# Images has been given the correct names
# fuse folders

cd $dir_start

mkdir img

cd "$dir_1"

pwd

mv *.JPG "$dir_start/img"

cd "$dir_start"

cd "$dir_2"

mv *.JPG "$dir_start/img"












































