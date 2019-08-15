# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester_tools.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 09:09:16 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/15 16:07:24 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

ask_for_out () {
	while true ; do
		echo '\033[0;31;40m[\o/] [ SELECT DISPLAY ]\033[0;0m'
		echo '[ 0 ] [ Exit / None ]'
		echo '[ 1 ] [ Stdout Tgt Shell ]'
		echo '[ 2 ] [ Stdout Ref Shell ]'
		echo '[ 3 ] [ Stdout Diff ]'
		echo '[ 4 ] [ Stderr Tgt Shell ]'
		echo '[ 5 ] [ Stderr Ref Shell ]'
		echo '[ 6 ] [ Stderr Diff ]'
		echo '[ 7 ] [ Next ]'
		printf '\033[0;31;40m[/o\] [ Choose wisely: \033[0;0m'
		read user_in
		case $user_in in
			0)
				clear
				exit;;
			1)
				clear
				echo "[ 1 ] [ Stdout Tgt Shell: $out_file_tgt ]"
				cat "$out_file_tgt";;
			2)
				clear
				echo "[ 2 ] [ Stdout Ref Shell: $out_file_ref ]"
				cat "$out_file_ref";;
			3)
				clear
				echo "[ 3 ] [ Stdout Diff: $out_file_diff ]"
				cat "$out_file_diff";;
			4)
				clear
				echo "[ 4 ] [ Stderr Tgt Shell: $err_file_tgt ]"
				cat "$err_file_tgt";;
			5)
				clear
				echo "[ 5 ] [ Stderr Ref Shell: $err_file_ref ]"
				cat "$err_file_ref";;
			6)
				clear
				echo "[ 6 ] [ Stderr Diff: $err_file_diff ]"
				cat "$err_file_diff";;
			*)
				break ;
		esac
	done
}

print_kook () {
	if [ "$1" -eq '1' ] && [ "$2" -eq '1' ]
	then
		echo "\033[0;36;40m[ $3 ] \033[0;31;40m[ OUT: KO ]\033[0;0m \033[0;31;40m[ ERR: KO ]\033[0;0m"
		echo "\033[0;36;40m[ $3 ] \033[0;31;40m[ OUT: KO ]\033[0;0m \033[0;31;40m[ ERR: KO ]\033[0;0m\n\033[0;36;40m[ Stdout REPORT ]\033[0;0m" >> $UT_res_file
		echo "<Your shell: $UT_sh_tgt\n>Ref shell: $UT_sh_ref" >> $UT_res_file
		cat "$UT_out_file_diff" >> $UT_res_file
		echo "\033[0;36;40m[ Stderr REPORT ]\033[0;0m" >> $UT_res_file
		cat "$UT_err_file_diff" >> $UT_res_file
	elif [ "$1" -eq '0' ] && [ "$2" -eq '0' ]
	then
		echo "\033[0;36;40m[ $3 ] \033[0;32;40m[ OUT: OK ]\033[0;0m \033[0;32;40m[ ERR: OK ]\033[0;0m"
		echo "\033[0;36;40m[ $3 ] \033[0;32;40m[ OUT: OK ]\033[0;0m \033[0;32;40m[ ERR: OK ]\033[0;0m" >> $UT_res_file
	elif [ "$1" -eq '0' ] && [ "$2" -eq '0' ]
	then
		echo "\033[0;36;40m[ $3 ] \033[0;31;40m[ OUT: KO ]\033[0;0m \033[0;32;40m[ ERR: OK ]\033[0;0m"
		echo "\033[0;36;40m[ $3 ] \033[0;31;40m[ OUT: KO ]\033[0;0m \033[0;32;40m[ ERR: OK ]\033[0;0m\n\033[0;36;40m[ Stdout REPORT ]\033[0;0m" >> $UT_res_file
		echo "<Your shell: $UT_sh_tgt\n>Ref shell: $UT_sh_ref" >> $UT_res_file
		cat "$UT_out_file_diff" >> $UT_res_file
	elif [ "$1" -eq '1' ] && [ "$2" -eq '1' ]
	then
		echo "\033[0;36;40m[ $3 ] \033[0;32;40m[ OUT: OK ]\033[0;0m \033[0;31;40m[ ERR: KO ]\033[0;0m"
		echo "\033[0;36;40m[ $3 ] \033[0;32;40m[ OUT: OK ]\033[0;0m \033[0;31;40m[ ERR: KO ]\033[0;0m\n\033[0;36;40m[ Stderr REPORT ]\033[0;0m" >> $UT_res_file
		echo "<Your shell: $UT_sh_tgt\n>Ref shell: $UT_sh_ref" >> $UT_res_file
		cat "$UT_err_file_diff" >> $UT_res_file
	fi
}
