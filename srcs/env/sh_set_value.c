/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:34:22 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 23:01:56 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

void	sh_set_value(const char *key, const char *value)
{
	t_var		*var;
	t_env		*env;

	if (!key || !*key)
		return (NULL);
	if (!(tmp = sh_get_var(key)))
		return (sh_set_var(key, value));
	ft_strdel(&(tmp->value));
	tmp->value = ft_strdup(value);
		return (NULL);
}
