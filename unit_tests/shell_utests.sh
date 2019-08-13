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

shell_utests_stdin ()
{
	cat $cmd_file | while read i
do
	echo "$i" | $UT_sh_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt
	echo "$i" | $UT_sh_ref >$UT_out_file_ref 2>$UT_err_file_ref
	diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	if [ -z "$(cat $UT_out_file_diff)" ]
	then
		print_kook ok "$i"
	else
		print_kook ko "$i"
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
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	if [ -z "$(cat $UT_out_file_diff)" ]
	then
		print_kook ok "$i"
	else
		print_kook ko "$i"
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
	diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
	if [ -z "$(cat $UT_out_file_diff)" ]
	then
		print_kook ok "$i"
	else
		print_kook ko "$i"
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
			diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
			if [ "$?" -eq '0' ]
			then
				print_kook ok Stdin
				stdin='true'
				shell_utests_stdin
			fi
		fi

		if [ "$arg" = 'false' ]
		then
			$UT_sh_tgt -c \'$i\' >$UT_out_file_tgt 2>$UT_err_file_tgt
			$UT_sh_ref -c \'$i\' >$UT_out_file_ref 2>$UT_err_file_ref
			diff "$UT_err_file_tgt" "$UT_err_file_ref" > $UT_err_file_diff
			diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
			if [ "$?" -eq '0' ]
			then
				print_kook ok '-c input'
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
			diff "$UT_out_file_tgt" "$UT_out_file_ref" > $UT_out_file_diff
			if [ "$?" -eq '0' ]
			then
				print_kook ok 'File input'
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
		print_kook ko Stdin
	fi
	if [ "$arg" = 'false' ]
	then
		print_kook ko '-c input'
	fi
	if [ "$script_file" = 'false' ]
	then
		print_kook ko 'File input'
	fi
	rm $test_file 2>&-
}
