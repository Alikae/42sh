# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester_tools.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 09:09:16 by thdelmas          #+#    #+#              #
#    Updated: 2019/07/28 10:10:35 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

ask_for_out () {
	user_in=""
	while true ; do
		echo '\033[0;31;40m[\o/] [ SELECT DISPLAY ]\033[0;0m'
		echo '[ 0 ] [ Exit / None ]'
		echo '[ 1 ] [ Stdout Tgt Shell ]'
		echo '[ 2 ] [ Stdout Ref Shell ]'
		echo '[ 3 ] [ Stdout Diff ]'
		echo '[ 4 ] [ Stderr Tgt Shell ]'
		echo '[ 5 ] [ Stderr Ref Shell ]'
		echo '[ 6 ] [ Stderr Diff ]'
		printf '\033[0;31;40m[/o\] [ Choose wisely: \033[0;0m'
		read user_in
		if [[ "$user_in" -eq "1" ]] ; then
			clear
			echo "[ 1 ] [ Stdout Tgt Shell: $out_file_tgt ]"
			cat "$out_file_tgt"
		elif [[ "$user_in" -eq "2" ]] ; then
			clear
			echo "[ 2 ] [ Stdout Ref Shell: $out_file_ref ]"
			cat "$out_file_ref"
		elif [[ "$user_in" -eq "3" ]] ; then
			clear
			echo "[ 3 ] [ Stdout Diff: $out_file_diff ]"
			cat "$out_file_diff"
		elif [[ "$user_in" -eq "4" ]] ; then
			clear
			echo "[ 4 ] [ Stderr Tgt Shell: $err_file_tgt ]"
			cat "$err_file_tgt"
		elif [[ "$user_in" -eq "5" ]] ; then
			clear
			echo "[ 5 ] [ Stderr Ref Shell: $err_file_ref ]"
			cat "$err_file_ref"
		elif [[ "$user_in" -eq "6" ]] ; then
			clear
			echo "[ 6 ] [ Stderr Diff: $err_file_diff ]"
			cat "$err_file_diff"
		else
			break ;
		fi
	done
}
