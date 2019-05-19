/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_reserved.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 20:14:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/19 16:52:50 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_toktype	sh_is_ctl_word(const char *str)
{
	if (!ft_strcmp(str, "case"))
		return (SH_CASE);
	if (!ft_strcmp(str, "elif"))
		return (SH_ELIF);
	if (!ft_strcmp(str, "else"))
		return (SH_ELSE);
	if (!ft_strcmp(str, "if"))
		return (SH_IF);
	if (!ft_strcmp(str, "for"))
		return (SH_FOR);
	if (!ft_strcmp(str, "in"))
		return (SH_IN);
	if (!ft_strcmp(str, "until"))
		return (SH_UNTIL);
	if (!ft_strcmp(str, "while"))
		return (SH_WHILE);
	return (SH_EOS);	
}
t_toktype	sh_is_lbrace(const char *str)
{
	if (*str == '{')
		return (SH_LBRACE);
	if (!ft_strcmp(str, "do"))
		return (SH_DO);
	if (!ft_strcmp(str, "then"))
		return (SH_THEN);
	return (SH_EOS);
}

t_toktype	sh_is_rbrace(const char *str)
{
	if (*str == '}')
		return (SH_RBRACE);
	if (!ft_strcmp(str, "done"))
		return (SH_DONE);
	if (!ft_strcmp(str, "fi"))
		return (SH_FI);
	if (!ft_strcmp(str, "esac"))
		return (SH_ESAC);
	return (SH_EOS);
}

t_toktype	sh_is_reserved(const char *str)
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
