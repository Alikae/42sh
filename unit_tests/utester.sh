#!/bin/sh

log_file=./ulogs
logref=./logref
logfail=./logfail
ptofail=./pipefail
pref=./piperef
shtofail=./42sh
shref=/bin/sh
custom_script=
ut_scripts=(\
	'./unit_tests/sh_test_env.sh'\
	)

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
	echo '[ Testing Minishell ]'
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
	$shtofail $test_script >>$logfail 2>&1 &
	$shref $test_script >>$logref 2>&1 &

	diff $logref $logfail > $log_file
	cat $log_file
	rm -f $logref $logfail $pref $ptofail
}

test_custom_script () {
	echo '[ Testing Custom Script  ]'
	if [ -z $1 ] ; then
		printf "Enter shell script's path: "
		read custom_script
		if [ -r $1 ] ; then
			test_script_sh "$custom_script"
		else
			echo 'No such script.\n'
		fi
	fi
}

sh_unit_tests () {
	ls
}

while [ -z $user_in ] ; do
	clear
	echo '\033[0;31;40m[\o/] [ SHELL U-TESTER ]\033[0;0m'
	echo '[ 0 ] [ Exit ]'
	echo '[ 1 ] [ Test Minishell ]'
	echo '[ 2 ] [ Test 21sh ]'
	echo '[ 3 ] [ Test 42sh ]'
	echo '[ 4 ] [ Test custom script ]'
	echo '[ 5 ] [ Run unit tests ]'
	printf '\033[0;31;40m[/o\] [ Choose wisely: \033[0;0m'
	read user_in
done

if [[ "$user_in" -eq "1" ]] ; then
	test_minishell
elif [[ "$user_in" -eq "2" ]] ; then
	echo '[ Testing 21sh ]'
	test_21sh
elif [[ "$user_in" -eq "3" ]] ; then
	echo '[ Testing 42sh ]'
	test_42sh
elif [[ "$user_in" -eq "4" ]] ; then
	test_custom_script $custom_script
elif [[ "$user_in" -eq "5" ]] ; then
	echo '[ Unit Tests ]'
	sh_unit_tests
else
	echo '[ Exit ]'
fi

