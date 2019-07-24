#!/bin/sh

pipe=~/goinfre/testpipe
ptofail=~/goinfre/pipefail
pref=~/goinfre/piperef
shtofail=./42sh
shref=/bin/bash


if [[ ! -p $pipe ]]; then
	mkfifo $pipe
fi
if [[ ! -p $ptofail ]]; then
	mkfifo $ptofail
fi
if [[ ! -p $pref ]]; then
	mkfifo $pref
fi

## Tests
set -o noclobber
$shref <$pipe &

testy () {
	echo "echo '\n''UT: $shref: $1'" > $pipe
	echo "$1" > $pipe
}

testy "env"
testy "ls /"
testy "ls"

rm -f $pipe $pref $ptofail
