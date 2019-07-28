# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester_msh.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 08:55:34 by thdelmas          #+#    #+#              #
#    Updated: 2019/07/28 09:52:45 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

utest_minishell () {
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
	$sh_tgt <$pipe_in_tgt >$out_file_tgt 2>$err_file_tgt &
	$sh_ref <$pipe_in_ref >$out_file_ref 2>$err_file_ref &
	for i in "${cmd[@]}"
	do
		echo "[ Sending command: "$i" to "$sh_tgt"... ]"
		echo "echo [ Sending command: "$i" to "$sh_tgt"... ]" >> $pipe_in_tgt
		echo "$i" >> $pipe_in_tgt
		echo "[ Sending command: "$i" to "$sh_ref"... ]"
		echo "echo [ Sending command: "$i" to "$sh_ref"... ]" >> $pipe_in_ref
		echo "$i" >> $pipe_in_ref
	done
}
