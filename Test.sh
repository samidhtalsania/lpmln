#!/bin/bash
op='op-'
asp='ASP'
files=tests/input*.txt

if type ./lpmln >/dev/null 2>&1; then
	echo "Using executable found in current directory"
	exec=./lpmln
elif type lpmln >/dev/null 2>&1; then
	echo "Using executable available in system."
	exec=lpmln
else
	echo >&2 "LPMLN required to be installed for testing but it's not.  Aborting."; exit 1;

fi

success="true"

for f in $files
do
	ff=${f#*/}
	if [[ "$ff" == *$asp* ]]; then
		args=" -a "	
	fi

	name=$(echo $f | sed "s_.*\/__")
	$exec $args $f > /tmp/t
	c=$op$name
	if ! cmp -s tests/$c /tmp/t
	then
		echo "Test failed for $f"
		success="false" 
	fi   
done


if [[ "$success" == "true" ]]; then
	echo "All cases passed!"
fi