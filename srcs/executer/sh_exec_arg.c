/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:06:25 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/12 16:31:34 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "t_token.h"
#include "stdlib.h"
#include <fcntl.h>

int	sh_exec_arg(void)
{
	t_opt	*opt;
	char	*ret;

	ret = NULL;
	opt = NULL;
	ft_putendl("sh_exec_arg");
	if (NULL != (opt = ft_fetch_opt("c", 1, sh()->opt)) && opt->arg)
		ret = opt->arg;
	ft_putendl("sh_exec_arg");
	if (ret && *ret && (sh()->ast = tokenize_input(ret)))//line
	{
		print_all_tokens(sh(), sh()->ast, 0);
		exec_script(sh(), sh()->ast, 0);
	}
}
