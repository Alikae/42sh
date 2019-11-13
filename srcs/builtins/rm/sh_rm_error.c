/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rm_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:29:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/03 21:30:09 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		sh_error_rm_opt(char c)
{
	write(2, "rm: illegal option -- ", 23);
	write(2, &c, 1);
	write(2, "\nusage: rm [-f | -i] [-dPRrvW] file ...", 39);
	write(2, "\nunlink file\n", 13);
	return (-1);
}

int		sh_rm_directory(char *path)
{
	write(2, "rm: ", 4);
	ft_putstr_fd(path, 2);
	write(2, ": is a directory\n", 17);
	return (-1);
}
