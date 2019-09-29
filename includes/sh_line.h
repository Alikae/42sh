/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_line.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:48:28 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/21 23:46:36 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LINE_H
# define SH_LINE_H

# include "sh_types.h"

void	sh_free_all_ln(t_ln **ln);
void	sh_free_one_ln(t_ln **ln);

#endif
