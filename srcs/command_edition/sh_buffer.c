/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/02 22:48:52 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_command_edition.h"
#include "sh.h"


static void		convert_str_spaces(char **str, int *k)
{
	int i;

	i = 0;
	if (str[0][0] != '\033' && str[0][1] != 0 && *k == 0)
		*k += 1;
	else
		return ;
	sh_prompt();
	while (str[0][i])
	{
		if (str[0][i] == '\t' || str[0][i] == '\n' || str[0][i] == '\r'
				|| str[0][i] == '\v' || str[0][i] == '\f')
			str[0][i] = ' ';
		i++;
	}
}

static int		sh_byteswaiting(void)
{
	int		byteswaiting;

	ioctl(0, FIONREAD, &byteswaiting);
	return (byteswaiting);
}

char			*sh_buffer(int *k)
{
	char	*str;
	char	*buf[BUFFER];
	char	*temp;
	int		ret;

	str = NULL;
	temp = NULL;
	ft_bzero(buf, BUFFER);
	if ((ret = read(0, buf, BUFFER - 1)) <= 0)
		return (NULL);
	ret = sh_byteswaiting();
	if (ret)
	{
		if (!(temp = (char*)ft_memalloc(ret + 1)))
			return (NULL);
		if (read(0, temp, ret) < 0)
		{
			ft_memdel((void**)&temp);
			return (NULL);
		}
	}
	str = ft_strconv_w(ft_strjoin((const char*)buf, temp));
	ft_memdel((void**)&temp);
	convert_str_spaces(&str, k);
	return (str);
}
