/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:13:54 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/23 19:13:01 by thdelmas         ###   ########.fr       */
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
	if ((tmp = sh_getev("OLDPWD")) || (tmp = sh_setev("OLDPWD", NULL)))
		tmp->exported = 1;
	if ((tmp = sh_getev("PWD")) || (tmp = sh_setev("PWD", tmp2)))
		tmp->exported = 1;
}
