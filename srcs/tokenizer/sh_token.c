/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:55:05 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/02 20:13:15 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokens.h"

t_token	*sh_init_token(char type, char *content)
{
	t_token *tok;

	if (!(tok = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	tok->type = type;
	tok->content = content;
	tok->sub = NULL;
	tok->next = NULL;
	return (tok);
}
