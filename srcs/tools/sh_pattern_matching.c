/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 00:50:22 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/04 01:39:23 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		str_match_pattern(const char *str, const char *pattern, int start, int end)
{
	int	i;

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

//short_or_long: 
//o = short
//1 = long
char	*subtitute_suffix_pattern(const char *str, const char *pattern, short short_or_long)
{
	unsigned long	start;

	if (short_or_long == 0)
	{
		start = ft_strlen(str) - 1;
		while (start >= 0 && !str_match_pattern(str, pattern, start, ft_strlen(str) - 1))
			start--;
	}
	else
	{
		start = 0;
		while (start < ft_strlen(str) && !str_match_pattern(str, pattern, start, ft_strlen(str) - 1))
			start++;
	}
	if (!str_match_pattern(str, pattern, start, ft_strlen(str - 1)))
		return (ft_strdup(str));
	return (ft_strndup(str, start));
}

char	*subtitute_prefix_pattern(const char *str, const char *pattern, short short_or_long)
{
	unsigned long	end;
	unsigned long	start;

	start = 0;
	if (short_or_long == 0)
	{
		end = 0;
		while (start < ft_strlen(str) && !str_match_pattern(str, pattern, 0, end))
			start++;
	}
	else
	{
		end = ft_strlen(str) - 1;
		while (start >= 0 && !str_match_pattern(str, pattern, 0, end))
			start--;
	}
	if (!str_match_pattern(str, pattern, 0, end))
		return (ft_strdup(str));
	return (ft_strdup(str + start));
}
