/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_opt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:47:48 by thdelmas          #+#    #+#             */
/*   Updated: 2019/07/17 14:49:02 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_OPT_H
# define SH_OPT_H

typedef struct		s_opt
{
	char			name;
	char			*arg;
	struct s_opt	*next;
}					t_opt;

t_opt	*sh_create_opt(char name, char *content);
t_opt	*sh_getopt(int *ac, char ***av, char *optstr);

#endif
