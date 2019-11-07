/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:00:45 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/05 02:17:56 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "libft.h"

int			is_compound(t_toktype type)
{
	if (type == SH_WHILE || type == SH_UNTIL
			|| type == SH_IF || type == SH_FOR
			|| type == SH_CASE || type == SH_BRACES
			|| type == SH_SUBSH)
		return (1);
	return (0);
}

t_toktype	word_is_actual_terminator(const char *word, int len, t_toktype actual_compound)
{
	if (actual_compound == SH_WHILE)
	{
		if (!ft_strncmp(word, "do", len) && len == 2)
			return (SH_DO);
	}
	if (actual_compound == SH_DO)
	{
		if (!ft_strncmp(word, "done", len) && len == 4)
			return (SH_DONE);
	}
	if (actual_compound == SH_IF || actual_compound == SH_ELIF)
	{
		if (!ft_strncmp(word, "then", len) && len == 4)
			return (SH_THEN);
	}
	if (actual_compound == SH_THEN)
	{
		if (!ft_strncmp(word, "elif", len) && len == 4)
			return (SH_ELIF);
		if (!ft_strncmp(word, "else", len) && len == 4)
			return (SH_ELSE);
		if (!ft_strncmp(word, "fi", len) && len == 2)
			return (SH_FI);
	}
	if (actual_compound == SH_ELSE)
	{
		if (!ft_strncmp(word, "fi", len) && len == 2)
			return (SH_FI);
	}
	if (actual_compound == SH_BRACES)
	{
		if (!ft_strncmp(word, "}", len) && len == 1)
			return (SH_BRACES);
	}
	if (actual_compound == SH_CASE)
	{
		if (!ft_strncmp(word, "esac", len) && len == 4)
			return (SH_ESAC);
	}
	if (actual_compound == SH_SUBSH)
	{
		if (!ft_strncmp(word, ")", len) && len == 1)
			return (SH_SUBSH_END);
	}
	return (0);
}

t_toktype	word_is_reserved_2(const char *word, int len)
{
	if (len == 3 && !ft_strncmp(word, "for", len))
		return (SH_FOR);
	else if (len == 1 && !ft_strncmp(word, "!", len))
		return (SH_BANG);
	else if (len == 2 && !ft_strncmp(word, "in", len))
		return (SH_IN);
	else if (len == 1 && !ft_strncmp(word, "{", len))
		return (SH_BRACES);
	else if (len == 1 && !ft_strncmp(word, "(", len))
		return (SH_SUBSH);
	else if (len == 1 && !ft_strncmp(word, ")", len))
		return (SH_SUBSH_END);
	return (0);
}

t_toktype	word_is_reserved(const char *word, int len)
{
	if (len == 5 && !ft_strncmp(word, "while", len))
		return (SH_WHILE);
	else if (len == 2 && !ft_strncmp(word, "if", len))
		return (SH_IF);
	else if (len == 4 && !ft_strncmp(word, "then", len))
		return (SH_THEN);
	else if (len == 4 && !ft_strncmp(word, "elif", len))
		return (SH_ELIF);
	else if (len == 4 && !ft_strncmp(word, "else", len))
		return (SH_ELSE);
	else if (len == 2 && !ft_strncmp(word, "fi", len))
		return (SH_FI);
	else if (len == 2 && !ft_strncmp(word, "do", len))
		return (SH_DO);
	else if (len == 4 && !ft_strncmp(word, "done", len))
		return (SH_DONE);
	else if (len == 4 && !ft_strncmp(word, "case", len))
		return (SH_CASE);
	else if (len == 4 && !ft_strncmp(word, "esac", len))
		return (SH_ESAC);
	else if (len == 5 && !ft_strncmp(word, "until", len))
		return (SH_UNTIL);
	return (word_is_reserved_2(word, len));
}
