#!/bin/zsh
fastreplacestring.exe src/Router.re "...component ...component"
files=$1
function edits(){
  for i in "...component ...component"
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
# while IFS= read -r cmd; do
#     edits $cmd
# done < "$file"
