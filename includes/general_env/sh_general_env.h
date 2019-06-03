#ifndef		SH_GENERAL_ENV_H
# define	SH_GENERAL_ENV_H

# include	"includes/env/sh_env.h"

typedef struct	s_general_env
{
	char			**argv;
	t_env			*env;
	int/*redirect_lst*/	*redirections;

}				t_general_env;

#endif
