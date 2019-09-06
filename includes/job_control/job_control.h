/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 06:47:14 by ede-ram           #+#    #+#             */
/*   Updated: 2019/09/03 07:25:35 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

typedef struct	s_job
{
	char			*name;
	unsigned int	pid;
	struct s_job	*next;
}				t_job;

void	delete_job(t_job *job);
void	delete_all_jobs(t_job *job);
t_job	*create_job(unsigned int pid, const char *name, int index_b, int index_e);
t_job	*add_job(unsigned int pid, const char *name, int indexb, int indexe);

#endif
