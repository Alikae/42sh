
void	ft_match(t_token *token, char *condition, t_sh *p)
{
	while (token)
	{
		if (ft_match(condition, token->content))
		{
			ft_exec_script(p, token->sub, NULL);
			break ;
		}
		token = token->next;
	}
}

void	ft_compound_case(t_token *token, t_sh *p)
{
	while (token->sub)
	{
		ft_match(token->sub, token->content, p);
		token->sub = token->sub->next;
	}
}
