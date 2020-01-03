#include "sh_word_expansion.h"

void	sh_next_value(t_exp *exp)
{
	int		i;
	
	i = exp->i;
	while (exp->content[i] != '}')
		i++;
	if (!(exp->value = malloc(i + 1)))
		exit (-1);
	i = exp->i;
	while (exp->content[i] != '}')
	{
		exp->value[i] = exp->content[i];
		i++;
	}
	exp->value[i] = '\0';
}

void	sh_add_var(t_exp *exp)
{
	exp->find = (*exp->env);
	while (exp->find->next)
		exp->find = exp->find->next;
	if (!(exp->find->next = malloc(sizeof(t_env))))
		exit(-1);
	exp->find = exp->find->next;
	exp->find->key = ft_strdup(exp->name);
	exp->find->value = ft_strdup(exp->value);
}

void	sh_assign_word(t_exp *exp)
{
	int		i;

	i = 0;
	sh_next_word(exp);
	printf("next word = %s\n", exp->content);
	if (exp->content[exp->i] == '~' || exp->content[exp->i] == '$'
			|| exp->content[exp->i] == '`')
		sh_word_expansion(exp);
	else
		sh_next_value(exp);
	printf("exp->value = %s\n", exp->value);
	if (exp->find)
	{
		free(exp->find->value);
		exp->find->value = ft_strdup(exp->value);
	}
	else
		sh_add_var(exp);
}
