#!/bin/zsh

file=edits.cfg
function edits(){
  for i in "ReasonReact.Update Update" "ReasonReact.NoUpdate NoUpdate" "ReasonReact.UpdateWithSideEffects UpdateWithSideEffects"
do
    set -- $i
    echo fastreplacestring.exe $1 $2
done
};

while IFS= read -r cmd; do
    edits $cmd
done < "$file"
