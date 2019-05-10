/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_match_tok_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:22:07 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/10 08:58:43 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"

// <     >     >|     <<     >>     <&     >&     <<-     <>
// &   &&   (   )   ;   ;;   newline   |   ||

static t_toktype sh_is_tok_redir(const char *s)
{
	if (!s)
		return (SH_EOS);
	else if (*s == '<' && s[1] == '<' && s[2] == '-')
		return (SH_DLESSDASH);
	else if (*s == '<' && s[1] == '<')
		return (SH_DLESS);
	else if (*s == '<' && s[1] == '&')
		return (SH_LESSAND);
	else if (*s == '<' && s[1] == '>')
		return (SH_LESSGREAT);
	else if (*s == '<')
		return (SH_LESS);
	else if (*s == '>' && s[1] == '|')
		return (SH_CLOBBER);
	else if (*s == '>' && s[1] == '&')
		return (SH_GREATAND);
	else if (*s == '>' && s[1] == '>')
		return (SH_DGREAT);
	else if (*s == '>')
		return (SH_GREAT);
	return (SH_EOS);
}

static t_toktype sh_is_tok_ctrl(const char *s)
{
	if (!s)
		return (SH_EOS);
	else if (*s == '&' && s[1] == '&')
		return (SH_AND_IF);
	else if (*s == '&')
		return (SH_AND);
	else if (*s == '(')
		return (SH_LSUBSH);
	else if (*s == ')')
		return (SH_RSUBSH);
	else if (*s == ';' && s[1] == ';')
		return (SH_DSEMI);
	else if (*s == ';')
		return (SH_SEMI);
	else if (*s == '\n')
		return (SH_NEWLINE);
	else if (*s == '|' && s[1] == '|')
		return (SH_OR_IF);
	else if (*s == '|')
		return (SH_OR);
	else
		return (SH_EOS);
}

t_toktype sh_match_tok_op(const char *s1, int i)
{
	if (i > 2 && sh_is_tok_redir(s1 + i - 2))
		return (sh_is_tok_redir(s1 + i - 2));
	else if (i > 1 && sh_is_tok_redir(s1 + i - 1))
		return (sh_is_tok_redir(s1 + i - 1));
	else if (sh_is_tok_redir(s1 + i))
		return (sh_is_tok_redir(s1 + i));
	else if (i > 1 && sh_is_tok_ctrl(s1 + i - 1))
		return (sh_is_tok_ctrl(s1 + i - 1));
	else if (sh_is_tok_ctrl(s1 + i))
		return (sh_is_tok_ctrl(s1 + i));
	else
		return (SH_EOS);
}
