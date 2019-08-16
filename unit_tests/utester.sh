# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 08:54:49 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/16 16:39:55 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

readonly UT_dir="./unit_tests"
readonly UT_log_dir="$UT_dir/logs"
readonly UT_log_file="$UT_dir/u.log"
#readonly UT_sh_tgt="./42sh"
readonly UT_sh_tgt="../goinfre/42sh/42sh"
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
		'exit'\
		)

	## Tests
	$UT_sh_tgt <$pipe_in_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt &
	$UT_sh_ref <$pipe_in_ref >$UT_out_file_ref 2>$UT_err_file_ref &
	for i in "${cmd[@]}"
	do
		echo "[ Sending command: "$i" to "$UT_sh_tgt"... ]"
		echo "echo [ Sending command: "$i" to "$UT_sh_tgt"... ]" >> $pipe_in_tgt
		echo "$i" >> $pipe_in_tgt
		echo "[ Sending command: "$i" to "$UT_sh_ref"... ]"
		echo "echo [ Sending command: "$i" to "$UT_sh_tgt"... ]" >> $pipe_in_ref
		echo "$i" >> $pipe_in_ref
		echo "exit" >> $pipe_in_tgt
		echo "exit" >> $pipe_in_ref
	done
	diff $UT_out_file_ref $UT_out_file_tgt > $UT_out_file_diff
	diff $UT_err_file_ref $UT_err_file_tgt > $UT_err_file_diff
	ask_for_out
}


test_custom_script () {
	echo '[ Testing Custom Script ]'
	if [ ! -z "$1" ]
	then
		custom_script="$1"
	else
		echo 'You can specify path via positionnal params (ARGV)'
	fi
	while [ ! -r "$custom_script" ]
	do
		printf "Enter shell script's path: "
		read custom_script
		if [ "$custom_script" = "exit" ] ; then
			break ;
		elif [ ! -e "$custom_script" ] ; then
			echo "No such script. Type 'exit' to quit."
		fi
	done
	if [ -r "$custom_script" ] ; then
		$UT_sh_tgt <$pipe_in_tgt >$UT_out_file_tgt 2>$UT_err_file_tgt &
		cat $custom_script >> $pipe_in_tgt
		$UT_sh_ref <$pipe_in_ref >$UT_out_file_ref 2>$UT_err_file_ref &
		cat $custom_script >> $pipe_in_ref
		echo "exit" >> $pipe_in_tgt
		echo "exit" >> $pipe_in_ref
	fi
	echo '[ Done ]'
	diff $UT_out_file_ref $UT_out_file_tgt > $UT_out_file_diff
	diff $UT_err_file_ref $UT_err_file_tgt > $UT_err_file_diff
	ask_for_out
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
	echo '[ Testing 21sh ]'
	utest_21sh
elif [[ "$user_in" -eq "3" ]] ; then
	echo '[ Testing 42sh ]'
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
