/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:28:54 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/26 20:28:54 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine_loop(t_philo *philo)
{
	int	left_locked;
	int	right_locked;
	int	done;

	done = 0;
	left_locked = 0;
	right_locked = 0;
	while (1)
	{
		if (philo_check_stop(philo))
			break ;
		philo_think(philo);
		philo_take_forks(philo, &left_locked, &right_locked);
		if (philo_check_if_full(philo, left_locked, right_locked))
			break ;
		philo_eat(philo);
		philo_check_meals(philo, &done);
		philo_release_forks(philo, left_locked, right_locked);
		usleep(500);
		if (philo_check_stop(philo))
			break ;
		philo_sleep(philo);
	}
}

void	*solo_philo(t_philo *philo)
{
	philo_think(philo);
	print_action(philo, "has taken a fork");
	precise_sleep(philo->data->die, philo->data);
	return (NULL);
}

int	philo_check_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->write_mutex);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->write_mutex);
	return (stop);
}

int	philo_check_if_full(t_philo *philo, int left_locked, int right_locked)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&philo->data->write_mutex);
	if (philo->data->stop || (philo->data->nb_meals > 0
			&& philo->meals_eaten >= philo->data->nb_meals))
		stop = 1;
	pthread_mutex_unlock(&philo->data->write_mutex);
	if (stop)
		philo_release_forks(philo, left_locked, right_locked);
	return (stop);
}

void	philo_check_meals(t_philo *philo, int *done)
{
	if (!(*done) && philo->data->nb_meals > 0
		&& philo->meals_eaten >= philo->data->nb_meals)
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		philo->data->nb_p_finish_eat++;
		pthread_mutex_unlock(&philo->data->write_mutex);
		*done = 1;
	}
}
