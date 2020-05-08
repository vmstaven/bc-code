#!/bin/bash

# 2 inputs (directories) 

# CONSTANTS #########################################################################################################

dirStart=$(pwd)                         # dir_start/
IFS=', ' read -r -a array <<< "$@"      # array = {dir1/, dir2/, dir3/}
length=$(($#-1))                        # array.length()
dirDest="${!#}"                         # array.end()

echo "# DEBUG #########################################################################################################"

echo "length: $length"
echo "dirDest: $dirDest"
echo "dirStart: $dirStart"
echo "i_max: ${array[@]}" 

echo "#################################################################################################################"

mkdir frames # global frames
mkdir masks  # global masks
global_i=0

echo "dirStart: $dirStart"
echo "dirDest: $dirDest"

total_num_of_files=0
for dir in "${array[@]:0:$length}"
do
    total_num_of_files=$(($(ls -1 $dir/frames | wc -l) + $total_num_of_files ))  
done

for dir in "${array[@]:0:$length}"
do

    cd $dirStart/$dir/frames
    num_of_files=$(ls -1 | wc -l)

    # In folder
    for i in $(seq 1 $num_of_files)
    do
        ln -sf $dirStart/$dir/frames/$( echo $(ls -1 | sed -n $i\ p) ) $dirStart/$dirDest/frames/dp_$global_i.png
        cd ../masks
        ln -sf $dirStart/$dir/masks/$( echo $(ls -1 | sed -n $i\ p) ) $dirStart/$dirDest/masks/dp_$global_i.png
        global_i=$(($global_i+1))
        echo -ne "Progress: $( echo "$global_i/$total_num_of_files * 100" | bc -l )% | Handling image $global_i/$total_num_of_files \r"
        cd $dirStart/$dir/frames
    done

done

global_i=0