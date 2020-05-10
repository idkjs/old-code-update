#!/bin/zsh

files=$1
function edits(){
  for i in "...component" "...ReactCompat.component"
do
    set -- $i
    echo fastreplacestring.exe $1 $2
done
};
for file in $files
do
    echo $file
    edits $file
done

