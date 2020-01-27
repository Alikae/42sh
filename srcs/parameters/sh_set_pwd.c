/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include <limits.h>

void	sh_set_pwd(void)
{
	char	tmp2[PATH_MAX + 1];
	t_env	*tmp;

	ft_bzero(tmp2, PATH_MAX + 1);
	getcwd(tmp2, PATH_MAX);
	if (!(tmp = sh_getev("OLDPWD")))
	{
		if ((tmp = sh_setev("OLDPWD", NULL)))
			tmp->exported = 1;
	}
	else
		tmp->exported = 1;
	if (!(tmp = sh_getev("PWD")))
	{
		if ((tmp = sh_setev("PWD", tmp2)))
			tmp->exported = 1;
	}
	else
		tmp->exported = 1;
}
