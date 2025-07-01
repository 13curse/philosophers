/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:17:23 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/27 14:17:23 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	launch_philos(t_data *data)
{
	int			i;
	t_philo		philo;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->nb_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			philo.id = i + 1;
			philo.meals_eaten = 0;
			philo.last_meal = get_timestamp();
			philo.data = data;
			sem_init(&philo.meal_lock, 0, 1);
			pthread_create(&monitor_thread, NULL, monitor_routine, &philo);
			pthread_detach(monitor_thread);
			philo_routine(&philo);
			exit(0);
		}
		i++;
	}
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		check_death_if_needed(philo);
		take_forks(philo);
		philo_eat(philo);
		if (philo->data->nb_meals > 0)
		{
			sem_wait(&philo->meal_lock);
			if (philo->meals_eaten >= philo->data->nb_meals)
			{
				sem_post(&philo->meal_lock);
				release_forks(philo);
				exit(0);
			}
			sem_post(&philo->meal_lock);
		}
		release_forks(philo);
		check_death_if_needed(philo);
		philo_sleep(philo);
		check_death_if_needed(philo);
		philo_think(philo);
		check_death_if_needed(philo);
	}
}

void	philo_check_death(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d died\n", get_timestamp()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_dead);
	exit(1);
}
