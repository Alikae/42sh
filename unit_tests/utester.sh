# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 08:54:49 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/13 12:47:17 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

ut_dir="./unit_tests"
log_dir="$ut_dir/logs"
log_file="./ulogs"
sh_ref="/bin/bash"
sh_tgt="/bin/sh"

#(I/)O REPORT FILES
err_file_ref="$log_dir/err_ref.report"
err_file_tgt="$log_dir/err_tgt.report"
err_file_diff="$log_dir/err_diff.report"
out_file_diff="$log_dir/out_diff.report"
out_file_ref="$log_dir/out_ref.report"
out_file_tgt="$log_dir/out_tgt.report"

#I(/O) PIPE
pipe_in_ref="$log_dir/pipe_in_ref"
pipe_in_tgt="$log_dir/pipe_in_tgt"

#Externs Files
. "$ut_dir/utester_tools.sh"
. "$ut_dir/utester_msh.sh"
. "$ut_dir/utest_env.sh"

test_custom_cmds () {
	echo '[ Testing custom commands ]'
	#Insert your commands here
	cmd=(\
		'foo'\
		'ls'\
		'exit'\
		)

	## Tests
	$sh_tgt <$pipe_in_tgt >$out_file_tgt 2>$err_file_tgt &
	$sh_ref <$pipe_in_ref >$out_file_ref 2>$err_file_ref &
	for i in "${cmd[@]}"
	do
		echo "[ Sending command: "$i" to "$sh_tgt"... ]"
		echo "echo [ Sending command: "$i" to "$sh_tgt"... ]" >> $pipe_in_tgt
		echo "$i" >> $pipe_in_tgt
		echo "[ Sending command: "$i" to "$sh_ref"... ]"
		echo "echo [ Sending command: "$i" to "$sh_tgt"... ]" >> $pipe_in_ref
		echo "$i" >> $pipe_in_ref
		echo "exit" >> $pipe_in_tgt
		echo "exit" >> $pipe_in_ref
	done
diff $out_file_ref $out_file_tgt > $out_file_diff
diff $err_file_ref $err_file_tgt > $err_file_diff
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
		$sh_tgt <$pipe_in_tgt >$out_file_tgt 2>$err_file_tgt &
		cat $custom_script >> $pipe_in_tgt
		$sh_ref <$pipe_in_ref >$out_file_ref 2>$err_file_ref &
		cat $custom_script >> $pipe_in_ref
		echo "exit" >> $pipe_in_tgt
		echo "exit" >> $pipe_in_ref
	fi
	echo '[ Done ]'
diff $out_file_ref $out_file_tgt > $out_file_diff
diff $err_file_ref $err_file_tgt > $err_file_diff
ask_for_out
}


if [ ! -d "$log_dir" ]; then
	mkdir "$log_dir"
	touch $out_file_ref $out_file_tgt $err_file_ref $err_file_tgt
	touch $out_file_diff $err_file_diff
fi
#CLEAR
rm -f $pipe_in_ref $pipe_in_tgt
mkfifo $pipe_in_tgt $pipe_in_ref
echo -n '' > $out_file_ref
echo -n '' > $out_file_tgt
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
	test_21sh
elif [[ "$user_in" -eq "3" ]] ; then
	echo '[ Testing 42sh ]'
	test_42sh
elif [[ "$user_in" -eq "4" ]] ; then
	test_custom_script $1
elif [[ "$user_in" -eq "5" ]] ; then
	test_custom_cmds
elif [[ "$user_in" -eq "6" ]] ; then
	utest_env
fi
rm -f $pipe_in_ref $pipe_in_tgt
echo '[ Exit ]'
