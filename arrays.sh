function edits(){
  for i in "...component" "...component"
do
    set -- $i
    echo fastreplacestring.exe $1 $2
done
};
# files=$1
# # echo $1

# for i in $files
# do echo $i
# done
file=$1
while IFS= read -r cmd; do
    edits $cmd
done < "$file"
