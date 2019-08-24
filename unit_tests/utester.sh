# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 08:54:49 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/20 18:04:57 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

readonly UT_dir="./unit_tests"
readonly UT_log_dir="$UT_dir/logs"
readonly UT_log_file="$UT_dir/u.log"
readonly UT_sh_tgt="./42sh"
#readonly UT_sh_tgt="../goinfre/42sh/42sh"
readonly UT_sh_ref="/bin/sh"

#(I/)O REPORT FILES
readonly UT_err_file_ref="$UT_log_dir/err_ref.report"
readonly UT_err_file_tgt="$UT_log_dir/err_tgt.report"
readonly UT_err_file_diff="$UT_log_dir/err_diff.report"
readonly UT_out_file_diff="$UT_log_dir/out_diff.report"
readonly UT_out_file_ref="$UT_log_dir/out_ref.report"
readonly UT_out_file_tgt="$UT_log_dir/out_tgt.report"
readonly UT_res_file="$UT_log_dir/unit_tests.report"

#I(/O) PIPE
pipe_in_ref="$UT_log_dir/pipe_in_ref"
pipe_in_tgt="$UT_log_dir/pipe_in_tgt"

#Externs Files
. "$UT_dir/shell_utests.sh"
. "$UT_dir/utester_tools.sh"
. "$UT_dir/utester_msh.sh"
. "$UT_dir/utest_env.sh"

test_custom_cmds () {
	echo '[ Testing custom commands ]'
	#Insert your commands here
	cmd=(\
		'foo'\
		'ls'\
		'echo $HOME'\
		'exit'\
		)

	## Tests
	for i in "${cmd[@]}"
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
	done
	display_result
}


test_custom_script () {
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
	PS3='Choose your cmd file: '
	tests_fd_lst="$(ls $UT_dir/tests/ | grep .utest) exit"
	select i in $tests_fd_lst
	do
		echo "\033[0;36;40m[ $i ]\033[0;0m"
		if [ "$i" = 'exit' ] ; then
			exit ;
		fi
		sh_utests_tests "$UT_dir/tests/$i"
		echo "\033[0;36;40m[ $UT_sh_tgt ] [ Score: $UT_test_ok / $UT_test_num ]\033[0;0m"
		echo "\033[0;36;40m[ $UT_sh_tgt ] [ Score: $UT_test_ok / $UT_test_num ]\033[0;0m" >> $UT_res_file
		break ;
	done
	read -p "Display result ? (y/n): " ans
	if [ "$ans" = 'y' ]
	then
		cat $UT_res_file
	fi
	rm $test_file $cmd_file_1 $cmd_file_0 2>> "$UT_log_file"

}


if [ ! -d "$UT_log_dir" ]; then
	mkdir "$UT_log_dir"
fi
#CLEAR
rm -f $pipe_in_ref $pipe_in_tgt
mkfifo $pipe_in_tgt $pipe_in_ref
echo -n '' > $UT_out_file_ref
echo -n '' > $UT_out_file_tgt
echo -n '' > $UT_err_file_tgt
echo -n '' > $UT_err_file_ref
echo -n '' > $UT_log_file
echo -n '' > $UT_res_file
#
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
	utest_minishell
elif [[ "$user_in" -eq "2" ]] ; then
	utest_21sh
elif [[ "$user_in" -eq "3" ]] ; then
	utest_42sh
elif [[ "$user_in" -eq "4" ]] ; then
	test_custom_script $1
elif [[ "$user_in" -eq "5" ]] ; then
	test_custom_cmds
elif [[ "$user_in" -eq "6" ]] ; then
	shell_utests
fi
rm -f $pipe_in_ref $pipe_in_tgt
echo '[ Exit ]'
