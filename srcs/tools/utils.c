/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:31:38 by maboye            #+#    #+#             */
/*   Updated: 2019/05/12 14:54:08 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

void        ft_prompt()
{
    char    path[256];
    int     i;

    ft_bzero(path, 256);
    getcwd(path, 255);
    if ((i = ft_strlen(path)) > 0)
    {
        while (--i > 0 && path[i] && path[i] != '/')
            ;
        ft_strcpy(path, &path[++i]);
        ft_printf(1, "%s%s%s: ", TUR, path, X);
    }
    else
        ft_putstr("$> ");
}

int         my_putchar(int c)
{
    return(write(2, &c, 1));
}
