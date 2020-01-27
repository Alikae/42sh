/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:16:08 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:16:12 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		pattern_is_only_stars(char *pattern)
{
	while (*pattern == '*')
		pattern++;
	return (!*pattern);
}

int		str_match_pattern(char *str, char *pattern, int start, int end)
{
	int		i;

	i = 0;
	while (start <= end && pattern[i])
	{
		if (pattern[i] == '*')
		{
			while (start <= end)
			{
				if (str_match_pattern(str, pattern + i + 1, start, end))
					return (1);
				start++;
			}
			return (!pattern[i + 1]);
		}
		else if (pattern[i] != '?' && pattern[i] != str[start])
			return (0);
		start++;
		i++;
	}
	return (start > end && pattern_is_only_stars(pattern + i));
}

char	*subtitute_suffix_pattern(char *str, char *pattern, short s_or_l)
{
	int		start;

	if (!pattern || !*pattern || !str || !*str)
		return ((!str) ? ft_strdup("") : ft_strdup(str));
	if (s_or_l == 0)
	{
		start = ft_strlen(str);
		while (start > -1 && !str_match_pattern(str,
					pattern, start, (int)ft_strlen(str) - 1))
			start--;
	}
	else
	{
		start = 0;
		while (start < (int)ft_strlen(str) && !str_match_pattern(str,
					pattern, start, (int)ft_strlen(str) - 1))
			start++;
	}
	if (start < 0 || start == (int)ft_strlen(str))
		return (ft_strdup(str));
	return (ft_strndup(str, start));
}

char	*subtitute_prefix_pattern(char *str, char *pattern, short s_or_l)
{
	int		end;

	if (!pattern || !*pattern || !str || !*str)
		return ((!str) ? ft_strdup("") : ft_strdup(str));
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
		while (end > -1 && !str_match_pattern(str, pattern, 0, end))
			end--;
	}
	if (end < 0 || end == (int)ft_strlen(str))
		return (ft_strdup(str));
	return (ft_strdup(str + end + 1));
}
