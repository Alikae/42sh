
int	ft_match(t_token *token, char *condition, t_sh *p)
{
	while (token)
	{
		if (ft_match(condition, token->content))
		{
			ft_exec_script(p, token->sub, NULL);
			return (1);
		}
		token = token->next;
	}
	return (0);
}

void	ft_compound_case(t_token *token, t_sh *p)
{
	while (token->sub)
	{
		if (ft_match(token->sub, token->content, p))
			breack ;
		token->sub = token->sub->next;
	}
}
