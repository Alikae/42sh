/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:21:54 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/20 16:48:41 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_tokens.h"

t_toktype	sh_is_ctl_word(const char *str)
{
	if (!ft_match("case", str))
		return (SH_CASE);
	if (!ft_match("elif", str))
		return (SH_ELIF);
	if (!ft_match("else", str))
		return (SH_ELSE);
	if (!ft_match("if", str))
		return (SH_IF);
	if (!ft_match("for", str))
		return (SH_FOR);
	if (!ft_match("in", str))
		return (SH_IN);
	if (!ft_match("until", str))
		return (SH_UNTIL);
	if (!ft_match("while", str))
		return (SH_WHILE);
	return (SH_EOS);	
}
t_toktype	sh_is_lbrace(const char *str)
{
	if (*str == '{')
		return (SH_LBRACE);
	if (!ft_match("do", str))
		return (SH_DO);
	if (!ft_match("then", str))
		return (SH_THEN);
	return (SH_EOS);
}

t_toktype	sh_is_rbrace(const char *str)
{
	if (*str == '}')
		return (SH_RBRACE);
	if (!ft_match("done", str))
		return (SH_DONE);
	if (!ft_match("fi", str))
		return (SH_FI);
	if (!ft_match("esac", str))
		return (SH_ESAC);
	return (SH_EOS);
}

t_toktype	sh_get_res(const char *str)
{
	t_toktype	tmp;

	if (!str || !*str)
		return (SH_EOS);
	if (*str == '!')
		return (SH_BANG);
	if (SH_EOS != (tmp = sh_is_rbrace(str)))
		return (tmp);
	if (SH_EOS != (tmp = sh_is_lbrace(str)))
		return (tmp);
	if (SH_EOS != (tmp = sh_is_ctl_word(str)))
		return (tmp);
	return (SH_EOS);
}
