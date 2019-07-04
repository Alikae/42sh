/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 07:51:30 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/04 17:19:53 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

void	sh_prompt(void)
{
	char *prompt;
	char *tmp;

	if (!(tmp = ft_strnew(PATH_MAX + 1)))
		return ;
	tmp = getcwd(tmp, PATH_MAX);
	prompt = ft_strjoin("\033[0;31m", tmp);
	free(tmp);
	tmp = ft_strjoin(prompt, "\033[0m");
	free(prompt);
	prompt = ft_strjoin(tmp, "\033[0;33m c> \033[0m");
	free(tmp);
	ft_putstr(prompt);
	free(prompt);
}
