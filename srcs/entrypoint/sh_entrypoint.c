/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_entrypoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:10:48 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/10 15:25:17 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "21sh.h"
#include "21sh_command_line.h"

#include "sh_tokenizer.h"

void	sh_entrypoint(t_sh *sh)
{
	char **command;
	int z;
	
	z = -1;
	command = arguments();
	while (command && command[++z])
	{
		write(1, command[z], ft_strlen(command[z]));
		ft_putendl("TOKENIZER HERE:");
		ft_putendl(command[z]);
	}
	return ;
}
