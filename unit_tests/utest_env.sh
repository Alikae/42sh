utest_env () {
	test_env_cmd=(\
		'set'\
		'ls'\
		)
	for i in "${test_env_cmd[@]}"
	do
		clear
		echo "[ Sending command: $i to $sh_tgt... ]"
		echo "$i" | $sh_tgt >>$out_file_tgt 2>>$err_file_tgt &
		echo "[ Sending command: $i to $sh_ref... ]"
		echo "$i" | $sh_ref >>$out_file_ref 2>>$err_file_ref &
		diff $out_file_tgt $out_file_ref > $out_file_diff
		diff $err_file_tgt $err_file_ref > $err_file_diff
		ask_for_out
		echo 'EOF UNIT TEST ENV'
	done
}
