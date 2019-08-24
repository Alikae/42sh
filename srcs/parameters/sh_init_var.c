/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:36:07 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/20 15:26:12 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "sh_env.h"
#include "libft.h"

t_env	*sh_init_var(const char *key, const char *value)
{
	t_env	*var;

	if (!key || !*key)
		return (NULL);
	if ((var = sh_get_env(key)))
	{
		sh_set_value(var->key, value);
		return (var);
	}
	if (!(var = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->next = NULL;
	return (var);
}
