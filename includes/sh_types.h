/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:28:29 by ede-ram          #+#    #+#             */
/*   Updated: 2020/01/21 15:07:30 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TYPES_H
# define SH_TYPES_H

# include <termios.h>

typedef struct	s_toktool
{
	const char	*input;
	int			i;
	int			word_nb;
}				t_toktool;

typedef struct	s_redirect_lst
{
	int						in;
	int						out;
	struct s_redirect_lst	*next;
}				t_redirect_lst;

typedef struct	s_pipe_lst
{
	int					pipe[2];
	struct s_pipe_lst	*next;
}				t_pipe_lst;

typedef struct	s_ln
{
	char			*line;
	char			*tok;
	struct s_ln		*prev;
	struct s_ln		*next;
}				t_ln;

typedef struct	s_env
{
	char			*key;
	char			*value;
	int				exported;
	int				readonly;
	struct s_env	*next;
}				t_env;

typedef enum	e_toktype
{
	SH_NULL = 0,
	SH_WORD,
	SH_ASSIGN,
	SH_LESS,
	SH_GREAT,
	SH_AND,
	SH_OR,
	SH_SEMI,
	SH_AND_IF,
	SH_OR_IF,
	SH_DSEMI,
	SH_DLESS,
	SH_DGREAT,
	SH_LESSAND,
	SH_GREATAND,
	SH_LESSGREAT,
	SH_DLESSDASH,
	SH_CLOBBER,
	SH_IF,
	SH_THEN,
	SH_ELSE,
	SH_ELIF,
	SH_FI,
	SH_DO,
	SH_DONE,
	SH_CASE,
	SH_ESAC,
	SH_WHILE,
	SH_UNTIL,
	SH_FOR,
	SH_BRACES,
	SH_BANG,
	SH_IN,
	SH_FUNC,
	SH_SUBSH,
	SH_SUBSH_END,
	SH_SUBSH_EXP,
	SH_PARAM_EXP,
	SH_ARITH_EXP,
	SH_NEWLINE,
	SH_GROUP,
	SH_QUOTE,
	SH_DQUOTE,
	SH_BQUOTE,
	SH_SYNTAX_ERROR
}				t_toktype;

typedef struct	s_token
{
	t_toktype		type;
	unsigned int	index;
	char			*content;
	struct s_token	*sub;
	struct s_token	*next;
}				t_token;

typedef struct	s_open_file
{
	char				*name;
	int					fd;
	struct s_open_file	*next;
}				t_open_file;

typedef struct	s_pos
{
	int rows;
	int col;
}				t_pos;

typedef struct	s_cursors
{
	t_pos cursor;
	t_pos term;
}				t_cursors;

typedef struct	s_exp
{
	t_token		*tok;
	int			i;
	int			first_i;
	t_env		**env;
	t_env		*find;
	char		*value;
	char		*name;
	char		*content;
	short		opt;
	short		special_params;
	t_toktype	quote;
}				t_exp;

typedef struct	s_split
{
	int			i;
	t_token		*tok;
	t_token		*sub;
	const char	*split;
}				t_split;

typedef struct	s_job
{
	char			*name;
	pid_t			pid;
	pid_t			pgid;
	const char		*status;
	int				t_mode_setted;
	struct termios	t_mode;
	struct s_job	*next;
	short			reported;
}				t_job;

typedef enum	e_arthtype
{
	INIT = 0,
	NUMBER,
	PLUS,
	MINUS,
	MULTI,
	DIV,
	MODULO,
	MORE,
	LESS,
	MORE_EQUAL,
	LESS_EQUAL,
	AND,
	OR,
	AND_AND,
	OR_OR,
	DIFFERENT,
	EQUAL,
	NOP
}				t_arthtype;

typedef struct	s_arith
{
	t_arthtype		next_op;
	long int		nb;
	struct s_arith	*next;
	struct s_arith	*sub;
}				t_arith;

#endif
