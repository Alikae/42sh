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

int		sh_error_path(char *cmd, char *path, int error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(path, 2);
	if (error & ENOENT)
		write(2, ": No such file or directory\n", 28);
	if (error & ENOTDIR)
		write(2, ": Not a director\n", 17);
	if (error & EACCES)
		write(2, ": Permission denied\n", 20);
	return (-1);
}
