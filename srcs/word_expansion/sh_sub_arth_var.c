/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/31 03:02:27 by tcillard         ###   ########.fr       */
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

void		sh_find_begin_end(short int opt, int *beg, int *end)
{
	if ((opt & 1) == 1 || (opt & 2))
		*beg = *beg - 2;
	if ((opt & 4) == 4 || (opt & 8) == 8)
		*end = *end + 2;
}

int			sh_record_arth(char **s, int i, short int opt)
{
	int		i_cpy;
	int		i_sub;
	char	*name;

	i_cpy = i;
	i_sub = 0;
	while ((*s)[i_cpy] && (*s)[i_cpy] != ' ' && (*s)[i_cpy] != '\n'
			&& (*s)[i_cpy] != '\t' && !(sh_all_char_operator((*s)[i_cpy])))
		i_cpy++;
	if (!(name = malloc(i_cpy - i + 1)))
		destructor(-1);
	i_cpy = i;
	while ((*s)[i] && (*s)[i] != '\t' && (*s)[i] != ' '
			&& (*s)[i] != '\n' && !(sh_all_char_operator((*s)[i])))
		name[i_sub++] = (*s)[i++];
	name[i_sub] = '\0';
	if ((*s)[i] && (*s)[i + 1] && (*s)[i] == '+' && (*s)[i + 1] == '+')
		opt = opt + 4;
	else if ((*s)[i] && (*s)[i + 1] && (*s)[i] == '-' && (*s)[i + 1] == '-')
		opt = opt + 8;
	if (!(name = sh_find_arth_var_value(&name, opt)))
		return (0);
	sh_find_begin_end(opt, &i_cpy, &i);
	sh_sub_var(&name, s, i_cpy, i);
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
