/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:47 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/27 14:30:47 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clear_semaphores(t_data *data)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	sem_close(data->sem_dead);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	free(data->pids);
}

void	wait_for_philosophers(t_data *data)
{
	int		status;
	int		finished;
	pid_t	pid;

	finished = 0;
	while (finished < data->nb_philo)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			kill_all(data);
		finished++;
	}
	clear_semaphores(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data))
		return (1);
	init_semaphores(&data);
	data.pids = malloc(sizeof(pid_t) * data.nb_philo);
	data.start_time = get_timestamp();
	launch_philos(&data);
	wait_for_philosophers(&data);
	return (0);
}
