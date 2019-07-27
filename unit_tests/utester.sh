#!/bin/sh

log_dir="./unit_tests/logs"
log_file="./ulogs"
sh_ref="/bin/bash"
sh_tgt="/bin/sh"

err_file_ref="$log_dir/err_ref.report"
err_file_tgt="$log_dir/err_tgt.report"
out_file_ref="$log_dir/out_ref.report"
out_file_tgt="$log_dir/out_tgt.report"

pipe_in_ref="$log_dir/pipe_in_ref"
pipe_in_tgt="$log_dir/pipe_in_tgt"

ut_scripts=(\
	'./unit_tests/sh_test_env.sh'\
	)



test_custom_cmds () {
	echo '[ Testing custom commands ]'
	#Insert your commands here
	cmd=(\
		'foo'\
		'ls'\
		'exit'\
		)

	## Tests
	$sh_tgt <$pipe_in_tgt 2>$err_file_tgt | tee $out_file_tgt &
	$sh_ref <$pipe_in_ref 2>$err_file_ref | tee $out_file_ref &
	for i in "${cmd[@]}"
	do
		echo "[ Sending command: "$i" to "$sh_tgt"... ]" | tee -a $out_file_tgt
		echo "[ Sending command: "$i" to "$sh_ref"... ]" | tee -a $out_file_ref
	done

	diff $out_file_ref $out_file_tgt > $log_file
}

test_minishell () {
	echo '[ Testing Minishell ]'
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

	## Tests
	$sh_tgt <$pipe_in_tgt 2>$err_file_tgt &
	$sh_ref <$pipe_in_ref 2>$err_file_ref &
	for i in "${cmd[@]}"
	do
		echo "[ Sending command: "$i" to "$sh_tgt"... ]" | tee -a $out_file_tgt
		echo "$i" >> $pipe_in_tgt
		echo "[ Sending command: "$i" to "$sh_ref"... ]" | tee -a $out_file_ref
		echo "$i" >> $pipe_in_ref
	done

	diff $out_file_ref $out_file_tgt > $log_file
	cat $log_file


	rm -f $out_file_ref $out_file_tgt $pipe_in_ref $pipe_in_tgt
}

test_script_arg () {
	mkfifo $out_file_ref $out_file_tgt $pipe_in_tgt $pipe_in_ref
	$sh_tgt $test_script >>$out_file_tgt 2>&1 &
	$sh_ref $test_script >>$out_file_ref 2>&1 &

	diff $out_file_ref $out_file_tgt > $log_file
	cat $log_file
}

test_custom_script () {
	echo '[ Testing Custom Script  ]'
	while [ ! -r "$custom_script" ]
	do
		printf "Enter shell script's path: "
		read custom_script
		if [ "$custom_script" = "exit" ] ; then
			break ;
		elif [ -r "$custom_script" ] ; then
			test_script_arg "$custom_script"
		else
			echo "No such script. Type 'exit' to quit."
		fi
	done
}

sh_unit_tests () {
	ls
}

if [ ! -d "$log_dir" ]; then
	mkdir "$log_dir"
	touch $out_file_ref $out_file_tgt $err_file_ref $err_file_tgt
fi
rm -f $pipe_in_ref $pipe_in_tgt
mkfifo $pipe_in_tgt $pipe_in_ref
while [ -z $user_in ] ; do
	clear
	echo '\033[0;31;40m[\o/] [ SHELL U-TESTER ]\033[0;0m'
	echo '[ 0 ] [ Exit ]'
	echo '[ 1 ] [ Test Minishell ]'
	echo '[ 2 ] [ Test 21sh ]'
	echo '[ 3 ] [ Test 42sh ]'
	echo '[ 4 ] [ Test custom script ]'
	echo '[ 5 ] [ Test custom commands ]'
	echo '[ 6 ] [ Run unit tests ]'
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
	test_custom_cmds
elif [[ "$user_in" -eq "6" ]] ; then
	echo '[ Unit Tests ]'
	sh_unit_tests
fi
rm -f $pipe_in_ref $pipe_in_tgt
echo '[ Exit ]'
