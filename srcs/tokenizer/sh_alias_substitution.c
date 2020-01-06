#include "sh.h"
#include "sh_types.h"
#include "sh_builtins.h"

int		sh_alias_value_len(char *alias, int *ind)
{
	int		i;
	int		j;

	i =	0;
	j = 0;
	while (alias[i] != '=' && alias[i])
		i++;
	i++;
	j = i;
	*ind = i;
	while (alias[i])
		i++;
	return (i - j);
}

int		sh_cmd_len(t_toktool *t, int in)
{
	int		i;
	
	i = in;
	while (t->input[i] && t->input[i] != ' ')
		i++;
	return (i - in);
}

void	sh_sub_alias_command(t_toktool *t, char *alias, int in)
{ 
	int		len;
	int		i;
	int		j;
	char	*cmd;

	j = 0;
	len  = sh_alias_value_len(alias, &j) - sh_cmd_len(t, in);
	i = 0;
	if (!(cmd = (char*)malloc(len + ft_strlen(t->input) + 1)))
		exit (-1);
	while (i < in)
	{
		cmd[i] = t->input[i];
		i++;
	}
	while (alias[j])
		cmd[i++] = alias[j++];
	j = t->i;
	t->i = in;
	while (t->input[j])
		cmd[i++] = t->input[j++];
	cmd[i] = '\0';
	t->input = cmd;
}


char	*sh_find_sub_alias(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		i_str;

	i = 0;
	tab = sh()->aliases;
	if (tab)
	{
		while (tab[i])
		{
			j = 0;
			i_str = 0;
			while (str[i_str] && str[i_str] == tab[i][j] && tab[i][j] != '=')
			{
				j++;
				i_str++;
			}
			if (tab[i][j] == '=' && !str[i_str])
				return (tab[i]);
			i++;
		}
	}
	return (NULL);
}

char	*sh_find_alias(t_toktool *t, int i)
{
	char	*str;
	int		j;
	char	*tab;

	j = 0;
	if (!(str = (char*)malloc(t->i - i + 1)))
		exit(-1);
	while (t->input[i] && i < t->i)
		str[j++] = t->input[i++];
	str[j] = '\0';
	tab = sh_find_sub_alias(str);
	ft_memdel((void**)&str);
	return (tab);
}

unsigned int	sh_find_max_len(char **stack)
{
	int				j;
	unsigned int	max;

	j = 0;
	max = 0;
	while (stack[j])
	{
		if (ft_strlen(stack[j]) > max)
			max = ft_strlen(stack[j]);
		j++;
	}
	return (max);
}

void	sh_print_ident_size(unsigned int max, unsigned int len, char c)
{
	while (len <= max)
	{
		ft_putchar(c);
		len++;
	}
}

void	sh_print_alias_loop_error(char **stack, int loop)
{
	unsigned int	max;
	int				i;

	max = sh_find_max_len(stack);
	i = 0;
	printf("42sh: recursive alias error: %s\n", stack[0]);
	while (stack[i + 1])
	{
		ft_putstr(stack[i]);
		if (i == loop)
		{
			ft_putstr("<--");
			sh_print_ident_size(max, ft_strlen(stack[i]), '-');
			ft_putstr("|\n");
		}
		else
		{
			sh_print_ident_size(max, ft_strlen(stack[i]), ' ');
			ft_putstr("   |\n");
		}
		i++;
	}
	ft_putstr(stack[i]);
	ft_putstr("<--");
	sh_print_ident_size(max, ft_strlen(stack[i++]), '-');
	ft_putstr("|\n\n");
}

int		sh_check_stack(char **stack, char *alias)
{
	int		i;

	i = 0;
	while (stack[i + 1] && (ft_strcmp(stack[i], alias) != 0))
		i++;
	if (stack[i + 1])
		return (i);
	else
		return (-1);
}

void	sh_record_alias(char ***stack, char *alias)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = NULL;
	while ((*stack) && (*stack)[i])
		i++;
	if (!(cpy = malloc(sizeof(char *) * (i + 2))))
		exit (-1);
	i = 0;
	while (*stack && (*stack)[i])
	{
		cpy[i] = ft_strdup((*stack)[i]);
		i++;
	}
	cpy[i++] = ft_strdup(alias);
	cpy[i] = 0;
	ft_free_tabstr(*stack);
	printf("%p\n", *stack);
	*stack = cpy;
}

int		sh_push_alias(char *alias)
{
	char	**stack;
	int		ret;

	ret = 0; 
	stack = sh()->alias_stack;
	sh_record_alias(&stack, alias);
	sh()->alias_stack = stack;
	if ((ret = sh_check_stack(stack, alias)) != -1)
		return (0);
	return (1);
}

int		count_alias_word_in_str(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (count_token_words_in_str(str + i));
}

int		sh_treat_alias(char *alias, t_toktool *t, int begin, int *before)
{
	int		len;
	
	len = 0;
	if (!(sh_push_alias(alias)))
		return (0);;
	len = (ft_strlen(alias) - 1);
	if ((alias[len] == ' ' || alias[len] == '\n'
			|| alias[len] == '\t') && !(sh()->alias_end))
		(*before) = 1;
	if (sh()->alias_end)
		sh()->alias_end--;
	sh_sub_alias_command(t, alias, begin);
	sh()->alias_end = sh()->alias_end + count_alias_word_in_str(alias);
	return (1);
}

int		sh_alias_substitution(t_toktool *t, int word_begin)
{
	char		*alias;
	static int	before = 0;

	alias = NULL;
	if (!(sh()->alias_end) && sh()->alias_stack)
	{
		ft_free_tabstr((sh()->alias_stack));
		sh()->alias_stack = NULL;
	}
	if (before || t->word_nb == 1)
	{
		if (before && !(sh()->alias_end))
			before = 0;
		if ((alias = sh_find_alias(t, word_begin)))
		{
			if (sh_treat_alias(alias, t, word_begin, &before))
				return (1);
			return (0);
		}
	}
	return (0);
}
