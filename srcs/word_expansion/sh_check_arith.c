#include "sh.h"
#include "sh_word_expansion.h"

int		sh_error_expression_name(char *str)
{
	printf("42sh: bad math expression: (error is \"%s\"\n", str);
	sh()->abort_cmd = 1;
	return (0);
}

int		sh_check_value(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i] && ((str[i] >= '0' && str[i] <= '9') || sh_all_char_operator(str[i])))
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i])
		return (sh_error_expression_name(str + i));
	else
		return (1);
}

long int	sh_find_arth_var_value(char **str)
{
	t_env *env;

	env = sh()->params;
	while (env && (ft_strcmp(*str, env->key) != 0))
		env = env->next;
	ft_memdel((void**)str);
	if (env && sh_check_value(env->value))
		return (sh_long_atoi(env->value));
	sh()->abort_cmd = 1;
	return (0);
}

void		sh_sub_var(char *value, char **str, int begin, int end)
{
	char	*sub;
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!(sub = malloc(ft_strlen(value) + (end - begin))))
		exit (-1);
	while (i < begin)
	{
		sub[i] = (*str)[i];
		i++;
	}
	while (value[j])
		sub[i++] = value[j++];
	while ((*str)[end])
		sub[i++] = (*str)[end++];
	sub[i] = '\0';
	free(*str);
	*str = sub;
	printf("str = %s\n", *str); 
}

void		sh_record_arth(char **str, int i)
{
	int		i_cpy;
	int		i_sub;
	char		*name;

	i_cpy = i;
	i_sub = 0;
	while ((*str)[i_cpy] && (*str)[i_cpy] != ' ' && (*str)[i_cpy] != '\n'
			&& (*str)[i_cpy] != '\t' && !(sh_all_char_operator((*str)[i_cpy])))
		i_cpy++;
	if (!(name = malloc(i_cpy - i + 1)))
		exit(-1);
	i_cpy = i;
	while ((*str)[i] && (*str)[i] != '\t' && (*str)[i] != ' '
			&& (*str)[i] != '\n' && !(sh_all_char_operator((*str)[i])))
		name[i_sub++] = str[i++];
	name[i_sub] = '\0';
	name = sh_find_arth_var_value(&name);
	sh_sub_var(name, str, i_cpy, i);
	exit (-1);
}

int		sh_check_valid_var_name(char *str, int i)
{
	while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n'
			&& !(sh_all_char_operator(str[i])) && str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int		sh_valid_arith(char **str)
{
	int		i;
	int		par;

	i = 0;
	par = 0;
	return (1);
	while (str[i] && !(sh()->abort_cmd))
	{
		if (str[i] == '(')
			par++;
		else if (str[i] == ')')
			par--;
		else if (!(sh_all_char_operator(str[i])))
		{
			if (sh_check_valid_var_name(str, i)
				sh_record_arth(str, i);
		}
		i++;
	}
	return (0);
}
