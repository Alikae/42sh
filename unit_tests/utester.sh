#!/bin/sh

pipe=./testpipe
ptofail=./pipefail
pref=./piperef
shtofail=./42sh
shref=/bin/sh

cmd[0]='env'
cmd[1]='ls'
cmd[2]='ls /'

mkfifo $pipe $ptofail $pref

## Tests
$shref <$pipe &

testy () {
	echo "echo '\n''UT: $shref: $1'" > $pipe
	echo "$1" > $pipe
}

for i in "${cmd[@]}"
do
testy "$i"
done

rm -f $pipe $pref $ptofail
