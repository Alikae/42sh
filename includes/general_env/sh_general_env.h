#ifndef		SH_GENERAL_ENV_H
# define	SH_GENERAL_ENV_H

# include	"includes/env/sh_env.h"
# include	"includes/general_env/redirection_lst.h"

typedef struct	s_general_env
{
	char				**argv;
	t_env				*env;
	//local env changes?
	t_redirection_lst	*redirections;
}				t_general_env;

#endif
