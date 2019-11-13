/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_palias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 00:16:34 by tmeyer            #+#    #+#             */
/*   Updated: 2019/11/12 19:45:09 by thdelmas         ###   ########.fr       */
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
