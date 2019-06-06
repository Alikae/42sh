/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_advance_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:58:37 by thdelmas          #+#    #+#             */
/*   Updated: 2019/06/07 01:08:34 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sh_advance_word(char *input, size_t *i)
{
	while (input[*i])
	{
		if (input[*i] == '<' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == '>' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == '&' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == '|' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == ' ' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == ';' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == '\t' && !sh_isquoted(input, *i))
			break;
		else if (input[*i] == '\n' && !sh_isquoted(input, *i))
			break;
		(*i)++;
	}
}
