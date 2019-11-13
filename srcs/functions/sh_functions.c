/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_interpreter_tcillard.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:18:46 by tcillard          #+#    #+#             */
/*   Updated: 2019/06/04 10:17:31 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "test.h"
//#include "includes/tokenizer/sh_tokens.h"
#include <sys/stat.h>
#include <unistd.h>

/*
** ft_store_sub malloc and store in a new token
*/

void	ft_store_sub(t_token **new_sub, t_token *sub)
{
	if (sub->next)
	{
		if (!((*new_sub)->next = malloc(sizeof(t_token))))
			exit(-1);
		ft_store_sub(&((*new_sub)->next), sub->next);
	}
	else
		(*new_sub)->next = NULL;
	if (sub->sub)
	{
		if (!((*new_sub)->sub = malloc(sizeof(t_token))))
			exit(-1);
		ft_store_sub(&((*new_sub)->sub), sub->sub);
	}
	else
		(*new_sub)->sub = NULL;
	(*new_sub)->type = sub->type;
	(*new_sub)->content = ft_strdup(sub->content);
}

/*
** ft_cpy_token return a copy of a token and sub token
*/

t_token	*ft_cpy_token(t_token *token)
{
	t_token	*new_token;

	if (!(new_token = malloc(sizeof(t_token))))
		exit(-1);
	new_token->next = NULL;
	if (token->sub)
	{
		if (!(new_token->sub = malloc(sizeof(t_token))))
			exit(-1);
		ft_store_sub(&(new_token->sub), token->sub);
	}
	else
		new_token->sub = NULL;
	return (new_token);
}

/*
** ft_free_sub free all sub
*/

void	ft_free_sub(t_token *sub)
{
	if (sub->next)
		ft_free_sub(sub->next);
	if (sub->sub)
		ft_free_sub(sub->sub);
	if (sub->content)
		free(sub->content);
	if (sub->next)
		free(sub->next);
}

/*
** ft_free_token free the actual token in func_lib
*/

void	ft_free_token(t_func **func_lib, t_token *token)
{
	t_token	*cpy;

	ft_free_sub((*func_lib)->token);
	free((*func_lib)->token->content);
	free((*func_lib)->token);
	(*func_lib)->token = ft_cpy_token(token);
}

/*
** ft_store_func prepare the func_lib to register the func
** if the func name exist it do nothings
** if the func_lib exist but it not find the name it create a new link in next
** if the func_lib not exist it create the func_lib
*/

void	store_func(t_func **func_lib, t_token *token)
{
	t_func	*cpy;

	cpy = *func_lib;
	while ((*func_lib) && (*func_lib)->next && ft_strcmp((*func_lib)->name, token->content) != 0)
		*func_lib = (*func_lib)->next;
	if (*func_lib && ft_strcmp((*func_lib)->name, token->content) == 0)
		ft_free_token(func_lib, token);
	else if (*func_lib)
	{
		if (!((*func_lib)->next = malloc(sizeof(t_func))))
			exit (-1);
		(*func_lib) = (*func_lib)->next;
		(*func_lib)->name = ft_strdup(token->content);
		(*func_lib)->next = NULL;
		(*func_lib)->token = ft_cpy_token(token);
	}
	else if (!(*func_lib))
	{
		if (!(*func_lib = malloc(sizeof(t_func))))
			exit (-1);
		(*func_lib)->name = ft_strdup(token->content);
		(*func_lib)->next = NULL;
		(*func_lib)->token = ft_cpy_token(token);
	}
	if (cpy)
		(*func_lib) = cpy;
}
