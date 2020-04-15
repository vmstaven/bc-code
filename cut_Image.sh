#!/bin/bash

img_in=$1
num_of_pieces=$2
width=$3
height=$4
dims_cut=$(echo "sqrt($num_of_pieces)" | bc)
tile_width=$(($width/$dims_cut))
tile_height=$(($height/$dims_cut))

echo $num_of_pieces
echo $width
echo $height
echo $dims_cut
echo $tile_height
echo $tile_width

echo $dims_cut

for i in $(seq 0 $(($dims_cut-1))) 
do 
    for j in $(seq 0 $(($dims_cut-1))) 
    do 
        echo "x = $(($j*$tile_width))"
        echo "y = $(($i*$tile_height))"
        gdal_translate -srcwin $(($j*$tile_width)) $(($i*$tile_height)) $tile_width $tile_height -of GTiff $img_in "slice_$i-$j.tif"
    done
done

