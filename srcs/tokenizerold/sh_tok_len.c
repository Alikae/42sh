/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tok_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:47:42 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/08 23:56:52 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		sh_tok_len(const char *in)
{
	t_toktype type;
	int i;
	char *tmp;

	type = SH_EOS;
	i = -1;
	while (in[++i])
	{
		if (type != SH_EOS && type != SH_WORD && SH_EOS != sh_match_tok_op(in, i))
			;
		else if (type != SH_EOS && type != SH_WORD && SH_EOS == sh_match_tok_op(in, i))
			return (type);
		else if ((!quotes || !*quotes || quotes[ft_strlen(quotes) - 1] == in[i]) && (in[i] == '\'' || in[i] == '"' || in[i] == '\\'))
			q
		else if ((!quotes || !*quotes) && (in[i] == '$' || in[i] == '`' ))
			sh_set_tok_type(in + i, &type);
		else if (type == SH_EOS && SH_EOS != sh_match_tok_op(in, i))
			sh_set_tok_type(in + i, &type);
		else if (type == SH_EOS && ft_isblank(in[i]))
			return (type);
		else if (in[i] == '#')
			return (type);
		else if (type != SH_WORD)
			type = SH_WORD;
	}
	return (i);
}
