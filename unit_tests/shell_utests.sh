#!/bin/sh

cmd_file=./cmd_file
cmd_file_base=./cmd_file_bae
utests='
foo
/bin/ls
/bin/ls -laF
/bin/ls -l -a -F
echo iT works
pwd
cd /tmp && pwd
cd ..
pwd
cd
pwd
cd -
pwd
ls
exit'
ret1=
ret2=

shell_utests_stdin ()
{
	cat $cmd_file | while read i
do
	echo "$i" | $UT_sh_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt
	echo "$i" | $UT_sh_ref >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	ret2=$?
	if [ -z "$(cat $UT_out_file_diff)" ]
	then
		print_kook $ret1 $ret2 "$i"
	else
		print_kook $ret1 $ret2 "$i"
	fi
done	
}

shell_utests_file ()
{
	cat $cmd_file | while read i
do
	echo "$i" > $test_file
	$UT_sh_tgt $test_file >$UT_out_file_tgt 2>$UT_err_file_tgt
	$UT_sh_ref $test_file >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	ret2=$?
	if [ -z "$(cat $UT_out_file_diff)" ]
	then
		print_kook $ret1 $ret2 "$i"
	else
		print_kook $ret1 $ret2 "$i"
	fi
done	
rm $test_file
}

shell_utests_arg ()
{
	cat $cmd_file | while read i
do
	$UT_sh_tgt -c "$i" >$UT_out_file_tgt 2>$UT_err_file_tgt
	$UT_sh_ref -c "$i" >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	ret1=$?
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	ret2=$?
	if [ -z "$(cat $UT_out_file_diff)" ]
	then
		print_kook $ret1 $ret2 "$i"
	else
		print_kook $ret1 $ret2 "$i"
	fi
done	
}

shell_utests ()
{
	utests_base='
something unkown
ls
pwd'
	stdin='false'
	arg='false'
	script_file='false'
	test_file=./unit_tests/test_file

	echo "$utests_base" > $cmd_file_base
	echo "$utests" > $cmd_file
	for i in ${utests_base[@]}
	do
		if [ "$stdin" = 'false' ]
		then
			echo \'$i\' | $UT_sh_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt
			echo \'$i\' | $UT_sh_ref >$UT_out_file_ref 2>$UT_err_file_ref
			diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
			ret2=$?
			diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
			ret1=$?
			if [ $ret1 -eq '0' ] || [ $ret2 -eq '0' ]
			then
				stdin='true'
				shell_utests_stdin
			fi
		fi

		if [ "$arg" = 'false' ]
		then
			$UT_sh_tgt -c \'$i\' >$UT_out_file_tgt 2>$UT_err_file_tgt
			$UT_sh_ref -c \'$i\' >$UT_out_file_ref 2>$UT_err_file_ref
			diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
			ret2=$?
			diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
			ret1=$?
			if [ $ret1 -eq '0' ] || [ $ret2 -eq '0' ]
			then
				arg='true'
				shell_utests_arg
			fi
		fi

		echo "$i" > $test_file
		if [ "$script_file" = 'false' ]
		then
			$UT_sh_tgt $test_file >$UT_out_file_tgt 2>$UT_err_file_tgt
			$UT_sh_ref $test_file >$UT_out_file_ref 2>$UT_err_file_ref
			diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
			ret2=$?
			diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
			ret1=$?
			if [ $ret1 -eq '0' ] || [ $ret2 -eq '0' ]
			then
				script_file='true'
				shell_utests_file
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
	fi
	if [ "$arg" = 'false' ]
	then
		echo "\033[0;36;40m[ Testing: Arg ] \033[0;31;40m[ KO ]\033[0;0m"
	fi
	if [ "$script_file" = 'false' ]
	then
		echo "\033[0;36;40m[ Testing: File ] \033[0;31;40m[ KO ]\033[0;0m"
	fi
	rm $test_file $cmd_file $cmd_file_base 2>> "$UT_log_file"
}
