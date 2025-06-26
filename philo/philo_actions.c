/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:38:58 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/26 20:38:58 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo, int *left_locked, int *right_locked)
{
	*left_locked = 0;
	*right_locked = 0;
	if (philo->id == philo->data->nb_philo || philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		*right_locked = 1;
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		*left_locked = 1;
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		*left_locked = 1;
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		*right_locked = 1;
		print_action(philo, "has taken a fork");
	}
}

void	philo_release_forks(t_philo *philo, int left_locked, int right_locked)
{
	if (right_locked)
		pthread_mutex_unlock(philo->right_fork);
	if (left_locked)
		pthread_mutex_unlock(philo->left_fork);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
	usleep((philo->id % philo->data->nb_philo) * 100);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->data->write_mutex);
	print_action(philo, "is eating");
	precise_sleep(philo->data->eat, philo->data);
	philo->meals_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	precise_sleep(philo->data->sleep, philo->data);
}
