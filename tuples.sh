
# Based on the answer given by @eduardo-ivanec without setting/resetting the IFS, one could simply do:

for i in "c 3" "e 5"
do
    set -- $i
    echo $1 and $2
done
for i in "ReasonReact.Update Update" "ReasonReact.NoUpdate NoUpdate" "ReasonReact.UpdateWithSideEffects UpdateWithSideEffects"
do
    set -- $i
    echo "rs" $1 $2
done


declare -afFirtx pairs=(
  [c]=3
  [e]=5
)
for key in "${!pairs[@]}"; do
  value="${pairs[$key]}"
  echo "key is $key and value is $value"
done

function _add_bs_dependency(){
 NEWDEPS=$1
 echo ✨${NEWDEPS} ✨
}
