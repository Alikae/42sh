/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_params.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:07:07 by thdelmas          #+#    #+#             */
/*   Updated: 2019/05/12 20:11:38 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARAMS_H
# define SH_PARAMS_H

typedef struct		s_var
{
	char	*key;
	char	*value;
	t_var	*next;
}					t_var;

typedef struct		s_params
{
	t_var	*spe;
	t_var	*pos;
	t_var	*var;
}					t_params;

#endif
