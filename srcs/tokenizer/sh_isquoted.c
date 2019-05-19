/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_isquoted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 21:32:56 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/13 23:35:47 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sh_set_quotes(char **quotes, char c, char *last)
{
	char buff[2];
	size_t len;

	buff[0] = c;
	buff[1] = '\0';
	len = ft_strlen(*quotes);
	*last = len > 0 ? (*quotes)[len - 1] : '\0';
	if (*last == c)
		(*quotes)[len - 1] = '\0';
	else
		*quotes = ft_strjoin_free(*quotes, buff, *quotes);
	len = ft_strlen(*quotes);
	*last = len > 0 ? (*quotes)[len - 1] : '\0';
}

static int sh_eff_quotes(char c, char last)
{
	if (last == c && (c == '\'' || c == '\\' || c == '"' || c == '`'))
		return (1);
	if (c == '\\' && last != '\\')
		return (1);
	else if (c == '`' && last != '\\' && last != '\'')
		return (1);
	else if (c == '"' && last != '\\' && last != '`')
		return (1);
	else if (c == '\'' && !last)
		return (1);
	return (0);
}

int		sh_isquoted(const char *str, int index)
{
	char *quotes;
	char last;
	size_t len;
	size_t i;

	quotes = ft_strdup("");
	i = -1;
	if (index <= 0)
		return (0);
	last = '\0';
	while (str[++i] && i < index)
	{
		ft_putendl(str + i);
		ft_putendl(quotes);
		len = ft_strlen(quotes);
		if (sh_eff_quotes(str[i], last))
			sh_set_quotes(&quotes, str[i], &last);
		if (last == '\\' && (str[i] != '\\' || (i > 0 && str[i - 1] == '\\')))		
			sh_set_quotes(&quotes, last, &last);
	}
	free(quotes);
	return (last != '\0');
}
