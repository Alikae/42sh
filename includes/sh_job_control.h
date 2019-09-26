/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 06:47:14 by ede-ram           #+#    #+#             */
/*   Updated: 2019/09/26 07:21:35 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <termios.h>

typedef struct	s_job
{
	char			*name;
	pid_t			pid;
	pid_t			pgid;
	struct termios	t_mode;
	struct s_job	*next;
}				t_job;

void	delete_job(t_job *job);
void	delete_all_jobs(t_job *job);
t_job	*create_job(unsigned int pid, const char *name, int index_b, int index_e);
t_job	*add_job(unsigned int pid, const char *name, int indexb, int indexe);
void	check_jobs_status(t_sh *p);
void	signal_all_jobs(int sig);

#endif
