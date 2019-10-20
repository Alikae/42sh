/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:32:04 by thdelmas          #+#    #+#             */
/*   Updated: 2019/10/20 16:55:55 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

int	(*sh_is_builtin(const char *cmd))(int ac, char **av, t_env **ev);

int	sh_type_keyword(char *str)
{
	int 		i;
	static char 	*keyword[] = { "if", "then", "else", "elif", "fi", "case", "esac",
		"for", "select", "while", "until", "do", "done", "in",
		"function", "time", "{", "}", "!", "[[", "]]", NULL};
	i = -1;
	while (keyword[++i])
	{
		if (!strcmp(keyword[i], str))
		{
			ft_putstr(str);
			ft_putendl(" is a shell keyword");
			return (1);
		}
	}
	return (0);
}

int	sh_type_builtin(char *str)
{
	if (sh_is_builtin(str))
	{
		ft_putstr(str);
		ft_putendl(" is a shell builtin");
		return (1);
	}
	return (0);
}

void	sh_type_type(char *str)
{
	if (!sh_type_keyword(str) && !sh_type_builtin(str))
	{
		ft_putstr_fd("sh: type: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not found", 2);
	}

}

int	sh_type(int ac, char **av, t_env **ev)
{
	int	i;

	i = 0;
	(void)ev;
	while (++i < ac)
		sh_type_type(av[i]);
	return (0);
}
