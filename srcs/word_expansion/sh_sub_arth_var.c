/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sub_arth_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:00:41 by tcillard          #+#    #+#             */
/*   Updated: 2020/01/23 10:06:52 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"

char		*sh_tab_fusion_free(char ***tab)
{
	int		j;
	int		i;
	int		i_name;
	char	*name;

	i = 0;
	i_name = 0;
	if (!(name = malloc(sh_tab_len(*tab) + 1)))
		destructor(-1);
	while ((*tab)[i])
	{
		j = 0;
		while ((*tab)[i][j])
			name[i_name++] = (*tab)[i][j++];
		i++;
	}
	name[i_name] = '\0';
	i = 0;
	while ((*tab)[i])
		ft_memdel((void**)&((*tab)[i++]));
	free(*tab);
	*tab = NULL;
	return (name);
}

void		sh_add_opt(char **name, short int opt)
{
	char	**tab;
	int		i;
	char	*cpy;

	i = 0;
	tab = sh_strsplit_arth(*name);
	i = 0;
	while (tab[i])
	{
		if (!(sh_all_char_operator(*tab[i])))
		{
			cpy = tab[i];
			tab[i] = sh_long_itoa(sh_long_atoi(tab[i]) + opt);
			ft_memdel((void**)&cpy);
		}
		i++;
	}
	free(*name);
	*name = sh_tab_fusion_free(&tab);
}

int			sh_record_arth(char **str, int i, short int opt)
{
	int		i_cpy;
	int		i_sub;
	char	*name;

	i_cpy = i;
	i_sub = 0;
	while ((*str)[i_cpy] && (*str)[i_cpy] != ' ' && (*str)[i_cpy] != '\n'
			&& (*str)[i_cpy] != '\t' && !(sh_all_char_operator((*str)[i_cpy])))
		i_cpy++;
	if (!(name = malloc(i_cpy - i + 1)))
		destructor(-1);
	i_cpy = i;
	while ((*str)[i] && (*str)[i] != '\t' && (*str)[i] != ' '
			&& (*str)[i] != '\n' && !(sh_all_char_operator((*str)[i])))
		name[i_sub++] = (*str)[i++];
	name[i_sub] = '\0';
	if (!(name = sh_find_arth_var_value(&name)))
		name = ft_strdup("0");
	if (opt)
	{
		sh_add_opt(&name, opt);
		i_cpy = i_cpy - 2;
	}
	sh_sub_var(&name, str, i_cpy, i);
	return (0);
}

int			sh_check_valid_var_name(char *str, int *i)
{
	int		letter;
	int		i_cpy;

	i_cpy = *i;
	letter = 0;
	while (str[*i] != '\t' && str[*i] != ' ' && str[*i] != '\n'
			&& !(sh_all_char_operator(str[*i])) && str[*i] != ')'
			&& str[*i] && !letter)
	{
		if ((str[*i] < '0' || str[*i] > '9')
				&& str[*i] != ')' && str[*i] != '(')
			letter++;
		(*i)++;
	}
	if (!letter)
		return (0);
	*i = i_cpy;
	while (str[*i] != '\t' && str[*i] != ' ' && str[*i] != '\n'
			&& !(sh_all_char_operator(str[*i])) && str[*i] != ')' && str[*i])
	{
		if (str[*i] >= '0' && str[*i] <= '9')
			return (sh_error_not_valide_arth_name(str, i_cpy));
		(*i)++;
	}
	return (1);
}

void		sh_sub_arith_var(char **str)
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
				opt = -1;
			i_cpy = i;
			if (sh_check_valid_var_name(*str, &i))
				i = sh_record_arth(str, i_cpy, opt);
		}
		if ((*str)[i])
			i++;
	}
}
