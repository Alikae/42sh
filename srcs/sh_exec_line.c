/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:34:58 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/10 04:23:24 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"
#include "libft.h"
#include "libshutil.h"
#include "sh.h"
#include <stdlib.h>

int		(*sh_is_builtin(const char *cmd))(int , char **, t_env **)
{
	if (!ft_strcmp(cmd, "set"))
		return (&sh_set);
	else if (!ft_strcmp(cmd, "true"))
		return (&sh_true);
	return (NULL);
}

void	sh_exec_line(const char *input)
{
	t_token *tok;
	int	(*p)(int, char **, t_env **);

	ft_putendl("Shell: exec_line.c\n---");
	ft_putstr("INPUT: ");
	p = NULL;
	if (input)
	{
		ft_putendl(input);
		tok = sh_tokenizer(input);
		if (tok)
			print_all_tokens(tok, 0);
		if ((p = sh_is_builtin(input)))
			p(1, NULL, &(sh()->params));
	}
	return ;
}
