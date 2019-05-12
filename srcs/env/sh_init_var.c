/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:36:07 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 23:27:57 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

t_var	*sh_init_var(const char *key, const char *value)
{
	t_var	*var;

	if (!key || !*key)
		return (NULL);
	if ((var = sh_get_var(key)))
	{
		sh_set_value(var->key, value);
		return (var);
	}
		if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->next = NULL;
	return (var);
}
