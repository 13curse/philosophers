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
	int		i;
	t_philo	philo;

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
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
		sem_wait(philo->data->sem_forks);
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
		sem_wait(philo->data->sem_print);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->data->start_time, philo->id);
		sem_post(philo->data->sem_print);
		sem_wait(philo->data->sem_forks);
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
		sem_wait(philo->data->sem_print);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->data->start_time, philo->id);
		sem_post(philo->data->sem_print);
		philo_eat(philo);
		if (philo->data->nb_meals > 0 && philo->meals_eaten >= philo->data->nb_meals)
		{
			sem_post(philo->data->sem_forks);
			sem_post(philo->data->sem_forks);
			exit(0);
		}
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
		philo_sleep(philo);
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
		philo_think(philo);
		if (get_timestamp() - philo->last_meal > philo->data->die)
			philo_check_death(philo);
	}
}

void	philo_check_death(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d died\n", get_timestamp() - philo->data->start_time, philo->id);
	sem_post(philo->data->sem_dead);
	exit(1);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d is eating\n", get_timestamp() - philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
	philo->last_meal = get_timestamp();
	precise_sleep(philo->data->eat, philo);
	philo->meals_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d is sleeping\n", get_timestamp() - philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
	precise_sleep(philo->data->sleep, philo);
}

void	philo_think(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d is thinking\n", get_timestamp() - philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
}
