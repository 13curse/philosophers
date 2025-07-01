/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:09:44 by sbehar            #+#    #+#             */
/*   Updated: 2025/07/01 15:19:55 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death_if_needed(t_philo *philo)
{
	if (get_timestamp() - philo->last_meal > philo->data->die)
		philo_check_death(philo);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	check_death_if_needed(philo);
	sem_wait(philo->data->sem_print);
	printf("%ld %d has taken a fork\n", get_timestamp()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
	sem_wait(philo->data->sem_forks);
	check_death_if_needed(philo);
	sem_wait(philo->data->sem_print);
	printf("%ld %d has taken a fork\n", get_timestamp()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_print);
}

void	release_forks(t_philo *philo)
{
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
}
