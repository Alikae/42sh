#!/bin/sh

stdin='false'
arg='false'
script_file='false'
test_file=./unit_tests/test_file
utests_base='
something unkown
ls
pwd'

cmd_file_1=$UT_log_dir/cmd_file_1
cmd_file_0=$UT_log_dir/cmd_file_0
utests='
pwd
/usr/bin/env
env
exit'

ret1=
ret2=
UT_test_ok="0"
UT_test_num="0"

shell_utests_stdin ()
{
	printf "\033[0;36;40m[ Stdin: $1 ] \033[0;0m"
	printf "\033[0;36;40m[ Stdin: $1 ] \033[0;0m" >> $UT_res_file
	echo "$1" | $UT_sh_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt
	echo "$1" | $UT_sh_ref >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	print_kook $ret1 $?
}

shell_utests_file ()
{
	printf "\033[0;36;40m[ File: $1 ] \033[0;0m"
	printf "\033[0;36;40m[ File: $1 ] \033[0;0m" >> $UT_res_file
	echo "$1" > $test_file
	$UT_sh_tgt $test_file >$UT_out_file_tgt 2>$UT_err_file_tgt
	$UT_sh_ref $test_file >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	print_kook $ret1 $?
}

shell_utests_arg ()
{
	printf "\033[0;36;40m[ -c: $1 ] \033[0;0m"
	printf "\033[0;36;40m[ -c: $1 ] \033[0;0m" >> $UT_res_file
	$UT_sh_tgt -c "$1" >$UT_out_file_tgt 2>$UT_err_file_tgt
	$UT_sh_ref -c "$1" >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	print_kook $ret1 $?
}

sh_utests_tests ()
{
	echo "\n\033[0;36;40m[ File: $1 ]\033[0;0m"
	echo "\n\033[0;36;40m[ File: $1 ]\033[0;0m" >> $UT_res_file
	while read i
	do
		printf "\n"
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
	done <$1
}

shell_utests ()
{
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
	sh_utests_tests "$cmd_file_1"
	tests_fd_lst="$(ls $UT_dir/tests/ | grep .utest)"
	for i in ${tests_fd_lst[@]}
	do
		sh_utests_tests "$UT_dir/tests/$i"
	done
	echo "\033[0;36;40m[ $UT_sh_tgt ] [ Score: $UT_test_ok / $UT_test_num ]\033[0;0m"
	echo "\033[0;36;40m[ $UT_sh_tgt ] [ Score: $UT_test_ok / $UT_test_num ]\033[0;0m" >> $UT_res_file
	read -p "Display result ? (y/n): " ans
	if [ "$ans" = 'y' ]
	then
		cat $UT_res_file
	fi
	rm $test_file $cmd_file_1 $cmd_file_0 2>> "$UT_log_file"
}
