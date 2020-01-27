/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:59:49 by ede-ram          #+#    #+#             */
/*   Updated: 2019/03/24 16:59:53 by ede-ram         ###   ########.fr       */
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
