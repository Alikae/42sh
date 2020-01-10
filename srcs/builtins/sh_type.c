/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:32:04 by thdelmas          #+#    #+#             */
/*   Updated: 2020/01/09 09:49:23 by tmeyer           ###   ########.fr       */
/*   Updated: 2019/11/01 17:40:51 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_types.h"
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

int	sh_type_alias(char *str)
{
	char **tmp;
	int len;

	if ((tmp = sh()->aliases))
		while (*tmp)
		{
			len = ft_strclen(str, '=');
			if (!strncmp(str, *tmp, len))
			{
				write(STDOUT_FILENO, *tmp, len);
				ft_putstr(" is aliased to `");
				ft_putstr(*tmp + len + 1);
				ft_putendl("'");
				return (1);
			}
			tmp++;
		}
	return (0);
}

int	sh_type_fun(char *str)
{
	t_token *fun = sh()->functions;
	while (fun)
	{
		if (!ft_strcmp(fun->content, str))
		{
			ft_putstr(fun->content);
			ft_putendl(" is a shell function");
			return (1);
		}
	}
	return (0);
}

void	sh_type_type(char *str)
{
	if (!sh_type_keyword(str) && !sh_type_builtin(str)
			&& !sh_type_fun(str) && !sh_type_alias(str))
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
