#!/bin/sh

utests=(\
	'something unkown'\
	'ls'\
	'pwd'\
	)
shtgt=/bin/sh
stdin='false'
arg='false'
script_file='false'
test_file=./unit_tests/test_file

if [ "$(echo 'echo ok' | $shtgt)" = 'ok' ]
then
	echo stdin true
	stdin='true'
fi

if [ "$($shtgt -c 'echo ok')"  = 'ok' ]
then
	echo arg true
	arg='true'
fi

echo 'echo ok' > $test_file
if [ "$($shtgt $test_file)" = 'ok' ]
then
	echo script_file true
	script_file='true'
fi
rm $test_file
