/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 07:51:30 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/08 22:53:19 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_env.h"
#include <stdlib.h>
#include <limits.h>

void	sh_prompt(void)
{
	char *prompt;
	char *tmp;

	prompt = NULL;
	tmp = NULL;
	if (!(tmp = sh_getev_value("PS1")))
	{
		if (!(tmp = ft_strnew(PATH_MAX + 1)))
			return ;
		tmp = getcwd(tmp, PATH_MAX);
		prompt = ft_strjoin("\033[0;31m", tmp);
		free(tmp);
		tmp = ft_strjoin(prompt, "\033[0m");
		free(prompt);
		prompt = ft_strjoin(tmp, "\033[0;33m c> \033[0m");
		ft_memdel((void**)&tmp);
		ft_putstr(prompt);
		ft_memdel((void**)&prompt);
	}
	else
		ft_putstr(tmp);
}
