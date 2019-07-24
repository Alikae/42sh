#!/bin/sh

log_file=./ulogs
logref=./logref
logfail=./logfail
ptofail=./pipefail
pref=./piperef
shtofail=./42sh
shref=/bin/sh

cmd=(\
	'foo'\
	'/bin/ls'\
	'/bin/ls -laF'\
	'/bin/ls -l -a -F'\
	'echo iT works'\
	'pwd'\
	'cd /tmp'\
	'pwd'\
	'cd ..'\
	'pwd'\
	'cd '\
	'pwd'\
	'cd -'\
	'pwd'\
	'ls'\
	'exit'\
	)

mkfifo $logref $logfail $ptofail $pref

## Tests
$shtofail <$ptofail >>$logfail 2>&1 &
$shref <$pref >>$logref 2>&1 &

testy () {
	echo "echo '\n''UT: $shtofail: $1'" > $ptofail
	echo "$1" > $ptofail
	echo "echo '\n''UT: $shref: $1'" > $pref
	echo "$1" > $pref
}

for i in "${cmd[@]}"
do
testy "$i"
done

diff $logref $logfail > $log_file
cat $log_file

rm -f $logref $logfail $pref $ptofail
