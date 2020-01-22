/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:15:43 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/22 04:09:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_command_edition.h"
#include "sh.h"

/*static */int		sh_byteswaiting(void)
{
	int		byteswaiting;

	ioctl(0, FIONREAD, &byteswaiting);
	return (byteswaiting);
}

char			*sh_buffer(void)
{
	char	*str;
	char	*buf[BUFFER];
	char	*temp;
	int		ret;

	str = NULL;
	temp = NULL;
	ft_bzero(buf, BUFFER);
	struct termios t;
       ret = tcgetattr(0, &t);
//    dprintf(2, "111%lu    ret %i<-\n", (unsigned long)t.c_lflag & (unsigned long)ICANON, ret);
  //  dprintf(2, "111ECHO%lu<-\n", (unsigned long)t.c_lflag & (unsigned long)ECHO);
    //dprintf(2, "111ECHONL%lu<-\n", (unsigned long)t.c_lflag & (unsigned long)ECHONL);
	if ((ret = read(0, buf, BUFFER)) <= 0)
		return (NULL);
//	ret = sh_byteswaiting();
//	printf("BYTES: %i\n", ret);
/*	if (ret)
	{
		if (!(temp = (char*)ft_memalloc(ret + 1)))
			return (NULL);
       tcgetattr(0, &t);
    dprintf(2, "222%lu<-\n", (unsigned long)t.c_lflag & (unsigned long)ICANON);
		if (read(0, temp, ret) < 0)
		{
			ft_memdel((void**)&temp);
			return (NULL);
		}
	}
*/	str = ft_strconv_w(ft_strjoin((const char*)buf, temp));
	ft_memdel((void**)&temp);
	return (str);
}
