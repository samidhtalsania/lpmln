#!/bin/bash
OP='op-'
FILES=tests/input*.txt

if type ./lpmln >/dev/null 2>&1; then
	echo "Using executable found in current directory"
	exec=./lpmln
elif type lpmln >/dev/null 2>&1; then
	echo "Using executable available in system."
	exec=lpmln
else
	echo >&2 "LPMLN required to be installed for testing but it's not.  Aborting."; exit 1;
fi

NEW_UUID=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)

success="true"

for f in $FILES
do
	name=$(echo $f | sed "s_.*\/__")
	$exec $f > /tmp/t
	c=$OP$name
	if ! cmp -s tests/$c /tmp/t
	then
		echo "Test failed for $f"
		success="false" 
	fi   
done


if [[ "$success" == "true" ]]; then
	echo "All cases passed!"
fi