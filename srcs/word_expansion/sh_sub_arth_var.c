#include "sh.h"
#include "sh_word_expansion.h"

int		sh_error_expression_name(char *str)
{
	printf("42sh: bad math expression: error is \"%s\"\n", str);
	sh()->abort_cmd = 1;
	return (0);
}

int		sh_check_value(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > '9' || str[i] < '0') && !sh_all_char_operator(str[i]))
			break ;
		i++;
	}
	if (str[i])
		return (sh_error_expression_name(str + i));
	else
		return (1);
}

char		*sh_find_arth_var_value(char **str)
{
	t_env *env;

	env = sh()->params;
	while (env && (ft_strcmp(*str, env->key) != 0))
		env = env->next;
	ft_memdel((void**)str);
	if (env && sh_check_value(env->value))
		return (ft_strdup(env->value));
	return (0);
}

void		sh_sub_var(char *value, char **str, int begin, int end)
{
	char	*sub;
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!(sub = malloc(ft_strlen(value) + (ft_strlen(*str) - (end - begin)) + 3)))
		exit (-1);
	while (i < begin)
	{
		sub[i] = (*str)[i];
		i++;
	}
	sub[i++] = '(';
	while (value[j])
		sub[i++] = value[j++];
	sub[i++] = ')';
	while ((*str)[end])
		sub[i++] = (*str)[end++];
	sub[i] = '\0';
	free(*str);
	*str = sub;
}

unsigned int	sh_tab_len(char **tab)
{
	int		i;
	int		j;
	int		len;
	
	i = 0;
	len = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			++j && ++len;
		i++;
	}
	return (len);
}

char		*sh_tab_fusion_free(char ***tab)
{
	int		j;
	int		i;
	int		i_name;
	char	*name;

	i = 0;
	i_name = 0;
	if (!(name = malloc(sh_tab_len(*tab))))
		exit (-1);
	while ((*tab)[i])
	{
		j = 0;
		while ((*tab)[i][j])
			name[i_name++] = (*tab)[i][j++];
		i++;
	}
	name[i_name] = '\0';
	i = 0;
	while ((*tab)[i])
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
	return (name);
}

void		sh_add_opt(char **name, short int opt)
{
	char	**tab;
	int		i;
	char	*cpy;

	i = 0;
	tab = sh_strsplit_arth(*name);
	while (tab[i])
	{
		if (!(sh_all_char_operator(*tab[i])))
		{
			cpy = tab[i];
			tab[i] = sh_long_itoa(sh_long_atoi(tab[i]) + opt);
			free(cpy);
		}
		i++;
	}
	*name = sh_tab_fusion_free(&tab);
}

void		sh_record_arth(char **str, int i, short int opt)
{
	int		i_cpy;
	int		i_sub;
	char	*name;

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
		name[i_sub++] = (*str)[i++];
	name[i_sub] = '\0';
	if (!(name = sh_find_arth_var_value(&name)))
		name = ft_strdup("0");
	if (opt)
	{
		sh_add_opt(&name, opt);
		i_cpy = i_cpy - 2;
	}
	sh_sub_var(name, str, i_cpy, i);
	free(name);
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

void		sh_sub_arith_var(char **str)
{
	int			i;
	short int	opt;

	i = 0;
	while ((*str)[i] && !(sh()->abort_cmd))
	{
		while ((*str)[i] == ' ' || (*str)[i] == '\t' || (*str)[i] == '\n')
			i++;
		opt = 0;
		if (!(sh_all_char_operator((*str)[i])) && ((str)[i] < 0 || (*str)[i] > 9)
			&& (*str)[i] != ')' && (*str)[i] != '(')
		{
			if (i >= 2 && (*str)[i - 1] == '+' && (*str)[i - 2] == '+')
				opt = 1;
			else if (i >= 2 && (*str)[i - 1] == '-' && (*str)[i - 2] == '-')
				opt = -1;
			if (sh_check_valid_var_name(*str, i))
				sh_record_arth(str, i, opt);
		}
	i++;
	}
}
