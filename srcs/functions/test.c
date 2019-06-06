#include "test.h"
#include "string.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *c)
{
	char	*cpy;
	int		i;

	i = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * ft_strlen(c) + 1)))
		return (0);
	while (c[i])
	{
		cpy[i] = c[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

t_token *create_token(int type, const char *content)
{
	t_token *tok = malloc(sizeof(t_token));
	tok->type = type;
	tok->content = strdup(content);
	tok->next = 0;
	tok->sub = 0;
	return (tok);
}

t_token	*gen_tokens2()
{
	t_token *begin;
	t_token *actual;
	actual = create_token(1, "-9if-");
	begin = actual;
	actual->sub = create_token(2, "-group-");
	actual->sub->sub = create_token(3, "true");
	actual->sub->next = create_token(4, "-group-");
	actual->sub->next->sub = create_token(5, "ls");
	actual->sub->next->sub->next = create_token(6, "..");
	actual->sub->next->sub->next->next = create_token(7, "-|-");
	actual->sub->next->sub->next->next->next = create_token(8, "cat");
	actual->next = create_token(9, "-;-");
	actual = actual->next;
	actual->next = create_token(10, "ls");
	actual = actual->next;
	actual->next = create_token(12, "/");
	return (begin);
}

void	print_token(t_token *token)
{
	printf("content=%s\n", token->content);
	printf("type=%i\n", token->type);
	if (token && token->sub)
		print_token(token->sub);
	if (token && token->next)
		print_token(token->next);
}

void	print_func(t_func *func_lib)
{
	while (func_lib)
	{
		printf("%s\n", func_lib->name);
		print_token(func_lib->token->sub);
		func_lib = func_lib->next;
	}
}
int	main()
{
	t_token	*token;
	t_func	*func_lib;

	func_lib = NULL;
	token = gen_tokens2();
	store_func(&func_lib, token);
	print_func(func_lib);
	store_func(&func_lib, token);
	print_func(func_lib);
	token->content = ft_strdup("et un nouveau");
	store_func(&func_lib, token);
	print_func(func_lib);
}
