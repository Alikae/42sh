/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_treat_arth_var_inc_dec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 01:59:27 by tcillard          #+#    #+#             */
/*   Updated: 2020/02/02 02:32:22 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

char	*sh_inc_dec_with_env(t_env *env, short int opt)
{
	char	*cpy;
	char	*del;

	del = env->value;
	cpy = ft_strdup(env->value);
	if ((opt & 1) == 1 || (opt & 2) == 2)
	{
		if ((opt & 1) == 1)
			env->value = sh_long_itoa(sh_long_atoi(cpy) + 1);
		if ((opt & 2) == 2)
			env->value = sh_long_itoa(sh_long_atoi(cpy) - 1);
		ft_memdel((void**)&del);
	}
	if ((opt & 4) == 4 || (opt & 8) == 8)
	{
		del = env->value;
		if ((opt & 4) == 4)
			env->value = sh_long_itoa(sh_long_atoi(cpy) + 1);
		else if ((opt & 8) == 8)
			env->value = sh_long_itoa(sh_long_atoi(cpy) - 1);
		ft_memdel((void**)&del);
		return (cpy);
	}
	ft_memdel((void**)&cpy);
	return (ft_strdup(env->value));
}

char	*sh_inc_dec_create_env(short int opt, char *str)
{
	char	*cpy;
	char	*del;

	del = NULL;
	cpy = NULL;
	if ((opt & 1) == 1)
		cpy = sh_long_itoa(1);
	else if ((opt & 2) == 2)
		cpy = sh_long_itoa(-1);
	else
		cpy = ft_strdup("0");
	if ((opt & 4) == 4)
		del = sh_long_itoa(sh_long_atoi(cpy) + 1);
	else if ((opt & 8) == 8)
		del = sh_long_itoa(sh_long_atoi(cpy) - 1);
	else
		del = sh_long_itoa(sh_long_atoi(cpy));
	sh_setev(str, del);
	ft_memdel((void**)&del);
	return (cpy);
}

void	sh_sub_arith_var(char **str)
{
	int			i;
	short int	opt;
	int			i_cpy;

	i = 0;
	opt = 0;
	i_cpy = 0;
	while ((*str)[i] && !(sh()->abort_cmd))
	{
		opt = 0;
		i = sh_skip_white_space(*str, i);
		if (!(sh_all_char_operator((*str)[i])))
		{
			if (i >= 2 && (*str)[i - 1] == '+' && (*str)[i - 2] == '+')
				opt = 1;
			else if (i >= 2 && (*str)[i - 1] == '-' && (*str)[i - 2] == '-')
				opt = 2;
			i_cpy = i;
			if (sh_check_valid_var_name(*str, &i))
				i = sh_record_arth(str, i_cpy, opt);
		}
		if ((*str)[i])
			i++;
	}
}
