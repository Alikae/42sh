/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 00:50:22 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/10 01:40:48 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		str_match_pattern(char *str, char *pattern, int start, int end)
{
	int		i;

	i = -1;
	if (!pattern || !*pattern)
		return (1);
	while (str[start] && pattern[++i])
	{
		if (pattern[i] == '*')
		{
			while (start <= end)
			{
				if (str_match_pattern(str, pattern + i + 1, start, end))
					return (1);
				start++;
			}
			return (0);
		}
		else if (pattern[i] != str[start] && pattern[i] != '?')
			return (0);
		start++;
	}
	return (pattern[i] ? 0 : 1);
}

char	*subtitute_suffix_pattern(char *str, char *pattern, short s_or_l)
{
	int		start;

	if (s_or_l == 0)
	{
		start = ft_strlen(str) - 1;
		while (start >= 0
			&& !str_match_pattern(str, pattern, start, ft_strlen(str) - 1))
			start--;
	}
	else
	{
		start = 0;
		while (start < (int)ft_strlen(str)
			&& !str_match_pattern(str, pattern, start, (int)ft_strlen(str) - 1))
			start++;
	}
	if (!str_match_pattern(str, pattern, start, ft_strlen(str - 1)))
		return (ft_strdup(str));
	return (ft_strndup(str, start));
}

char	*subtitute_prefix_pattern(char *str, char *pattern, short s_or_l)
{
	int		end;

	if (s_or_l == 0)
	{
		end = 0;
		while (end < (int)ft_strlen(str)
			&& !str_match_pattern(str, pattern, 0, end))
			end++;
	}
	else
	{
		end = ft_strlen(str) - 1;
		while (end >= 0 && !str_match_pattern(str, pattern, 0, end))
			end--;
	}
	if (!str_match_pattern(str, pattern, 0, end))
		return (ft_strdup(str));
	return (ft_strdup(str + end));
}
