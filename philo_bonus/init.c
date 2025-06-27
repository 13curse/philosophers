/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:04:39 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/27 14:04:39 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	data->sem_forks = sem_open("/sem_forks", O_CREAT, 0644, data->nb_philo);
	data->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	data->sem_dead = sem_open("/sem_dead", O_CREAT, 0644, 0);
}

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

long int	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, const char *action)
{
	sem_wait(philo->data->sem_print);
	if (!philo->data->stop
		|| (philo->data->stop && !ft_strcmp(action, "died")))
		printf("%ld %d %s\n",
			get_timestamp() - philo->data->start_time, philo->id, action);
	sem_post(philo->data->sem_print);
}

void	precise_sleep(long int duration_ms, t_philo *philo)
{
	long int	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < duration_ms)
	{
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
		usleep(500);
	}
}
