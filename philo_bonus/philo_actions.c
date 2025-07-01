/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:26:12 by sbehar            #+#    #+#             */
/*   Updated: 2025/07/01 16:29:06 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	sem_wait(&philo->meal_lock);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	sem_post(&philo->meal_lock);
	sem_wait(philo->data->sem_print);
	printf("%ld %d is eating\n", get_timestamp()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
	precise_sleep(philo->data->eat, philo);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d is sleeping\n", get_timestamp()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
	precise_sleep(philo->data->sleep, philo);
}

void	philo_think(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d is thinking\n", get_timestamp()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
}
