/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:28:03 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/27 14:28:03 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(500);
		sem_wait(&philo->meal_lock);
		if (philo->data->nb_meals > 0
			&& philo->meals_eaten >= philo->data->nb_meals)
		{
			sem_post(&philo->meal_lock);
			return (NULL);
		}
		if (get_timestamp() - philo->last_meal > philo->data->die)
		{
			sem_post(&philo->meal_lock);
			philo_check_death(philo);
		}
		sem_post(&philo->meal_lock);
	}
	return (NULL);
}
