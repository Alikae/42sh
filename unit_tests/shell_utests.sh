#!/bin/sh

cmd_file_1=$UT_log_dir/cmd_file_1
cmd_file_0=$UT_log_dir/cmd_file_0
utests='
pwd
/usr/bin/env
env
setenv
ls ; ls
set YOLO bar ; /usr/bin/env
set YOLO=bar ; /usr/bin/env
setenv FOO=bar ; /usr/bin/env
setenv FOO bar ; /usr/bin/env
unsetenv FOO ; env
setenv PATH "/bin:/usr/bin"; ls ; echo yolo
setenv PATH="/bin:/usr/bin"; ls ; echo yolo
set PATH="/bin:/usr/bin"; ls ; echo yolo
set PATH "/bin:/usr/bin"; ls ; echo yolo
set
unsetenv PATH ; ls
unsetenv
unset
unset PATH ; ls
foo
echo $#
ls ; echo $!
ls ; echo $?
ls fail ; echo $?
ls ; echo $_
ls ; echo $#
ls
ls -laF
ls -l -a -F
ls
ls /bin /boot /sbin /dev /home
ls | cat -e
ls | sort | cat -e
base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e s/1/Yes/g -e s/0/No/g
echo "Testing redirections," > /tmp/test.txt ; cat /tmp/test.txt ; rm /tmp/test.txt ; ls /tmp
echo "Testing redirections," > /tmp/test.txt ; cat /tmp/test.txt ; echo "Testing redirections," > /tmp/test.txt ; cat /tmp/test.txt ; rm /tmp/test.txt ; ls /tmp
echo "Testing redirections," > /tmp/test.txt ; cat /tmp/test.txt ; echo "Testing redirections," > /tmp/test.txt ; cat /tmp/test.txt ; wc -c < /tmp/test.txt ; rm /tmp/test.txt ; ls /tmp
PATH="" ; ls
ls something || ls
ls || ls something
ls -1; touch test_file; ls -1; rm test_file
ls -l && ls
/bin/ls
/bin/ls -laF
/bin/ls -l -a -F
/bin/ls
/bin/ls /bin /boot /sbin /dev /home
echo iT works
cd /tmp && pwd
cd .. && pwd
cd && pwd
cd - && pwd
rm nosuchfile 2>&-
ls nosuchfile 2>&-
ls >&-
rm nosuchfile 2>&1 | cat -e
ls
ls *
ls ./*
ls */*
echo "No dollar character" 1>&2 | cat -e
echo `ls -l`
cd
cd /path/to/dir
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi; ls; rm -rf test; ls
exit'

ret1=
ret2=
UT_test_ok="0"
UT_test_num="0"

shell_utests_stdin ()
{
	printf "\033[0;36;40m[ Stdin: ] \033[0;0m"
	printf "\033[0;36;40m[ Stdin: ] \033[0;0m" >> $UT_res_file
	echo "$1" | $UT_sh_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt
	echo "$1" | $UT_sh_ref >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	ret2=$?
	print_kook $ret1 $ret2 "$1"
}

shell_utests_file ()
{
	printf "\033[0;36;40m[ File: ] \033[0;0m"
	printf "\033[0;36;40m[ File: ] \033[0;0m" >> $UT_res_file
	echo "$1" > $test_file
	$UT_sh_tgt $test_file >$UT_out_file_tgt 2>$UT_err_file_tgt
	$UT_sh_ref $test_file >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	ret2=$?
	print_kook $ret1 $ret2 "$1"
}

shell_utests_arg ()
{
	printf "\033[0;36;40m[ -c: ] \033[0;0m"
	printf "\033[0;36;40m[ -c: ] \033[0;0m" >> $UT_res_file
	$UT_sh_tgt -c "$1" >$UT_out_file_tgt 2>$UT_err_file_tgt
	$UT_sh_ref -c "$1" >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	ret2=$?
	print_kook $ret1 $ret2 "$1"
}

shell_utests ()
{

	stdin='false'
	arg='false'
	script_file='false'
	test_file=./unit_tests/test_file
	utests_base='
	something unkown
	ls
	pwd'

	echo "$utests_base" > $cmd_file_0
	echo "$utests" > $cmd_file_1
	for i in ${utests_base[@]}
	do
		if [ "$stdin" = 'false' ]
		then
			echo \'$i\' | $UT_sh_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt
			echo \'$i\' | $UT_sh_ref >$UT_out_file_ref 2>$UT_err_file_ref
			diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
			ret2=$(cat $UT_err_file_tgt)
			ret1=$(cat $UT_out_file_tgt)
			if [ "$ret1" != '' ] || [ "$ret2" != '' ]
			then
				stdin='true'
			fi
		fi

		if [ "$arg" = 'false' ]
		then
			$UT_sh_tgt -c \'$i\' >$UT_out_file_tgt 2>$UT_err_file_tgt
			$UT_sh_ref -c \'$i\' >$UT_out_file_ref 2>$UT_err_file_ref
			ret2=$(cat $UT_err_file_tgt)
			ret1=$(cat $UT_out_file_tgt)
			if [ "$ret1" != '' ] || [ "$ret2" != '' ]
			then
				arg='true'
			fi
		fi

		echo "$i" > $test_file
		if [ "$script_file" = 'false' ]
		then
			$UT_sh_tgt $test_file >$UT_out_file_tgt 2>$UT_err_file_tgt
			$UT_sh_ref $test_file >$UT_out_file_ref 2>$UT_err_file_ref
			ret2=$(cat $UT_err_file_tgt)
			ret1=$(cat $UT_out_file_tgt)
			if [ "$ret1" != '' ] || [ "$ret2" != '' ]
			then
				script_file='true'
			fi
		fi

		if [ "$stdin" = 'true' ] && [ "$arg" = 'true' ] && [ "$script_file" = 'true' ]
		then
			break ;
		fi
	done
	if [ "$stdin" = 'false' ]
	then
		echo "\033[0;36;40m[ Testing: Stdin ] \033[0;31;40m[ KO ]\033[0;0m"
		echo "\033[0;36;40m[ Testing: Stdin ] \033[0;31;40m[ KO ]\033[0;0m" >> $UT_res_file
	fi
	if [ "$arg" = 'false' ]
	then
		echo "\033[0;36;40m[ Testing: Arg ] \033[0;31;40m[ KO ]\033[0;0m"
		echo "\033[0;36;40m[ Testing: Arg ] \033[0;31;40m[ KO ]\033[0;0m" >> $UT_res_file
	fi
	if [ "$script_file" = 'false' ]
	then
		echo "\033[0;36;40m[ Testing: File ] \033[0;31;40m[ KO ]\033[0;0m"
		echo "\033[0;36;40m[ Testing: File ] \033[0;31;40m[ KO ]\033[0;0m" >> $UT_res_file
	fi
	while read i
	do
		if [ "$arg" = 'true' ]
		then
			shell_utests_arg "$i"
		fi
		if [ "$script_file" = 'true' ]
		then
			shell_utests_file "$i"
		fi
		if [ "$stdin" = 'true' ]
		then
			shell_utests_stdin "$i"
		fi
		echo
		if [ $ret1 -eq '0' ]
		then
			UT_test_ok="$( expr "$UT_test_ok" + 1 )"
		fi
		UT_test_num="$( expr "$UT_test_num" + 1 )"
	done <$cmd_file_1
	echo "\033[0;36;40m[ $UT_sh_tgt ] [ Score: $UT_test_ok / $UT_test_num ]\033[0;0m"
	echo "\033[0;36;40m[ $UT_sh_tgt ] [ Score: $UT_test_ok / $UT_test_num ]\033[0;0m" >> $UT_res_file
	read -p "Display result ? (y/n): " ans
	if [ "$ans" = 'y' ]
	then
		cat $UT_res_file
	fi
	rm $test_file $cmd_file_1 $cmd_file_0 2>> "$UT_log_file"
}
