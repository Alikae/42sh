/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_control.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:36:08 by tmeyer            #+#    #+#             */
/*   Updated: 2020/01/26 20:36:11 by tmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_JOB_CONTROL_H
# define SH_JOB_CONTROL_H

# include "sh.h"
# include <termios.h>

void	delete_job(t_job *job);
void	delete_all_jobs(t_job *job);
t_job	*create_job(unsigned int pid, const char *name,
		int index_b, int index_e);
t_job	*add_job(unsigned int pid, int indexb, int indexe, const char *status);
void	check_jobs_status(t_sh *p);
void	signal_all_jobs(int sig);
void	update_job_termios(int child_pid);

#endif
