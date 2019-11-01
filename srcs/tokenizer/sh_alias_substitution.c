#include "sh.h"
#include "sh_types.h"

int		sh_alias_len(char *alias, int *ind)
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

int		sh_cmd_len(t_tokenize_tool *t)
{
	int		i;
	
	i = t->i;
	while (t->input[i] && t->input[i] != ' ')
		i++;
	return (i - t->i);
}

void	sh_sub_alias_command(t_tokenize_tool *t, char *alias)
{ 
	int		cmd_len;
	int		alias_len;
	int		i;
	int		j;
	char	*cmd;

	j = 0;
	alias_len = sh_alias_len(alias, &j);
	cmd_len = sh_cmd_len(t);
	i = 0;
	if (!(cmd = (char*)malloc(alias_len + ft_strlen(t->input) - cmd_len + 1)))
		exit (-1);
	while (i < t->i)
	{
		cmd[i] = t->input[i];
		i++;
	}
	while (alias[j])
		cmd[i++] = alias[j++];
	j = i - alias_len + cmd_len;
	while (t->input[j])
		cmd[i++] = t->input[j++];
	cmd[i] = '\0';
//	free((void*)t->input);
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
			if (!(str[i_str]))
				return (tab[i]);
			i++;
		}
	}
	return (NULL);
}

char	*sh_find_alias(t_tokenize_tool *t)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i =  t->i;
	while (t->input[i] != ' ' && t->input[i])
		i++;
	if (!(str = (char*)malloc(i - t->i + 1)))
		exit(-1);
	i = t->i;
	while (t->input[i] != ' ' && t->input[i])
		str[j++] = t->input[i++];
	str[j] = '\0';
	return (sh_find_sub_alias(str));
}
/*
void	sh_push_alias(char *alias)
{
	static char	**stack;

	if (!stack)
	{
		if (!(stack = malloc(sizeof(char*) * 2))
			exit(-1);
	}
}*/

int		sh_alias_substitution(t_tokenize_tool *t)
{
	char		*alias;
	static int	before = 0;
	int			len;

	len = 0;
	if (before || t->word_nb == 1)
	{
		before = 0;
		if ((alias = sh_find_alias(t)))
		{
	//		sh_push_alias(alias);
			len = ft_strlen(alias) - 1;
			if (alias[len] == ' ' && alias[len] == '\n' && alias[len] == '\t')
				before = 1;
			sh_sub_alias_command(t, alias);
			return (1);
		}
	}
	return (0);
}
