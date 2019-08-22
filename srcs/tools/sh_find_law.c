/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_find_law.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:10:03 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/22 15:14:19 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*sh_find_law(struct stat sb)
{
	int		i;
	char	*law;

	if (!(law = malloc(sizeof(char) * 10)))
		exit(-1);
	law[9] = '\0';
	i = -1;
	while (++i <= 8)
	{
		if (((sb.st_mode & S_IRUSR) && i == 0)
				|| ((sb.st_mode & S_IRGRP) && i == 3)
				|| ((sb.st_mode & S_IROTH) && i == 6))
			law[i] = 'r';
		else if (((sb.st_mode & S_IWUSR) && i == 1)
				|| ((sb.st_mode & S_IWGRP) && i == 4)
				|| ((sb.st_mode & S_IWOTH) && i == 7))
			law[i] = 'w';
		else if (((sb.st_mode & S_IXUSR) && i == 2)
				|| ((sb.st_mode & S_IXGRP) && i == 5)
				|| ((sb.st_mode & S_IXOTH) && i == 8))
			law[i] = 'x';
		else
			law[i] = '-';
	}
	return (law);
}
