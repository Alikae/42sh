#include "t_token.h"
#include "stdlib.h"
#include "libft.h"
#include "error.h"

//ATTENTION STRDUP
char	*dupfilsdup(const char *in)
{
	char	*new;
	int		len;

	if (!in)
		return (0);
	len = (in) ? ft_strlen(in) : 1;
	if (!(new = (char*)malloc(sizeof(char))))
		return (0);
	new[len] = 0;
	if (in)
		ft_strcpy(new, in);
	return (new);
}

t_token	*find_token_by_key_until(t_token *tok_begin, t_token *tok_end, t_toktype *type, t_toktype (*types)[2])
{
	if (type)
		*type = 0;
	while (tok_begin && tok_begin != tok_end)
	{
		if (tok_begin->type == (*types)[0] || tok_begin->type == (*types)[1])
		{
			if (type)
				*type = tok_begin->type;
			return (tok_begin);
		}
		tok_begin = tok_begin->next;
	}
	if (type)
		*type = (tok_begin) ? tok_begin->type : 0;
	return ((tok_begin) ? tok_begin : 0);
}

t_token	*create_token(t_toktype type, const char *content)
{
	t_token	*tok;

	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		exit(ERROR_MALLOC);
//ATTENTION STRDUP
//APPRENEZ A CODER
	if (!(tok->content = dupfilsdup(content)) && content)
		exit(ERROR_MALLOC);
	tok->type = type;
	tok->sub = 0;
	tok->next = 0;
	return (tok);	
}

t_token	*create_token_n(t_toktype type, const char *content, int n)
{
	t_token	*tok;

	if (!(tok = (t_token*)malloc(sizeof(t_token))))
		exit(ERROR_MALLOC);
	if (!(tok->content = ft_strndup(content, n)))
		exit(ERROR_MALLOC);
	tok->type = type;
	tok->sub = 0;
	tok->next = 0;
	return (tok);	
}

void	delete_token(t_token *tok)
{
	free(tok->content);
	free(tok);
}
