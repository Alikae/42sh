#!/bin/sh

log_file=./ulogs
logref=./logref
logfail=./logfail
ptofail=./pipefail
pref=./piperef
shtofail=./42sh
shref=/bin/sh
test_script=

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

testy () {
	echo "echo '\n''UT: $shtofail: $1'" > $ptofail
	echo "$1" > $ptofail
	echo "echo '\n''UT: $shref: $1'" > $pref
	echo "$1" > $pref
}

test_minishell () {
	mkfifo $logref $logfail $ptofail $pref

	## Tests
	$shtofail <$ptofail >>$logfail 2>&1 &
	$shref <$pref >>$logref 2>&1 &

	for i in "${cmd[@]}"
	do
		testy "$i"
	done

	diff $logref $logfail > $log_file
	cat $log_file

	rm -f $logref $logfail $pref $ptofail
}

test_script_sh () {
	mkfifo $logref $logfail $ptofail $pref
	if [ -z $test_script ] ; then
		printf "Enter shell script's path: "
		read test_script
	fi
	$shtofail $test_script >>$logfail 2>&1 &
	$shref $test_script >>$logref 2>&1 &

	diff $logref $logfail > $log_file
	cat $log_file
	rm -f $logref $logfail $pref $ptofail
}

while [ -z $user_in ] ; do
	echo 'Test Minishell - 1'
	echo 'Test Script Mode - 2'
	printf "Choose testing mode: "
	read user_in
	clear
done
if [ "$user_in" -eq "1" ] ; then
	test_minishell
elif [ "$user_in" -eq "2" ] ; then
	test_script_sh
else
	echo 'bad input'
fi
