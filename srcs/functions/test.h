#ifndef TEST_H
# define TEST_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
typedef struct	s_token
{
	struct s_token	*sub;
	struct s_token	*next;
	int		type;
	char *content;
}		t_token;

typedef struct	s_func
{
	char		*name;
	t_token		*token;
	struct s_func	*next;	
}		t_func;

t_token	*gen_tokens2();
void	store_func(t_func **func_lib, t_token *token);
char	*ft_strdup(const char *str);
int	ft_strlen(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
#endif
