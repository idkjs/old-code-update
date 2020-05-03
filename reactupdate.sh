#!/bin/zsh

file=edits.cfg
function edits(){
  for i in "React.Update ReasonReact.Update" "React.NoUpdate ReasonReact.NoUpdate" "React.UpdateWithSideEffects ReasonReact.UpdateWithSideEffects"
do
    set -- $i
    echo fastreplacestring.exe $1 $2
done
};

while IFS= read -r cmd; do
    edits $cmd
done < "$file"
