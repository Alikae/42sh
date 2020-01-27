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

#include "sh.h"
#include "libft.h"
#include "sh_entrypoint.h"

static char	*find_path(void)
{
	char	*path;

	if (sh()->dir)
	{
		path = ft_strjoin(sh()->dir, "/.42sh_rc");
		return (path);
	}
	return (NULL);
}

int			sh_parse_rc(void)
{
	char	*path;
	int		ret;

	path = find_path();
	ret = sh_script(path);
	ft_memdel((void**)&path);
	return (ret);
}
