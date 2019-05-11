/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:10:48 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 19:59:53 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "21sh.h"
#include "sh_command_line.h"

#include "sh_tokenizer.h"

void	sh_entrypoint(t_sh *sh)
{
	char **command;
	int z;
	
	z = -1;
	command = sh_arguments();
	while (command && command[++z])
	{
		write(1, command[z], ft_strlen(command[z]));
		ft_putendl("TOKENIZER HERE:");
		ft_putendl(command[z]);
	}
	return ;
}
