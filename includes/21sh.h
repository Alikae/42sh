/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:48:58 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/11 19:24:13 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include <curses.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# include "libft.h"

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define TUR		"\033[36m"
# define X			"\033[0m"

typedef struct		s_ln
{
	char			*line;
	char			*tok;
	struct s_ln		*prev;
	struct s_ln		*next;
}					t_ln;

typedef struct		s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct		s_sh
{
	t_envp			*envp;
	char			**local;
	t_ln			*ln;
	t_ln			*ln_history;
}					t_sh;

t_sh				*g_sh;

char				**arguments(void);

void				sh_entrypoint(t_sh *sh);
void				sh_free_one_ln(t_ln **ln);
void				sh_free_all_ln(t_ln **ln);
t_ln				*sh_init_ln(const char	*line, t_ln *previous);

void				sh_free(t_sh **sh);
t_envp				*sh_init_envp(const char **env);
t_sh				*sh_init(const char **env);
int					sh_loop(void);

void        		ft_prompt(void);
int         		my_putchar(int c);
int					ft_strclen(const char *str, char c);
void				signal_handler(int sig);

t_envp				*get_envp_value(t_envp *list, char *str);

t_envp		    	*lst_addelem(t_envp *next);
t_envp          	*lst_chr(t_envp *list, char *str);
void		    	lst_del(t_envp **list);
t_envp				*lst_last(t_envp *list);
size_t				lst_size(t_envp *list);

#endif
