/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	st;
	size_t	end;

	if (!s)
		return (NULL);
	st = 0;
	end = ft_strlen(s) - 1;
	while (st <= end && (s[st] == ' ' || s[st] == '\n' || s[st] == '\t'))
		st++;
	if (st == end)
		return (NULL);
	while (end > st && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		end--;
	return (ft_strndup(s + st, end - st + 1));
}
