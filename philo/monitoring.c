/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:34:30 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/24 17:34:30 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_env		*env;
	int			i;
	long int	time_since_meal;

	env = (t_env *)arg;
	while (1)
	{
		pthread_mutex_lock(&env->data.write_mutex);
		if (env->data.stop)
		{
			pthread_mutex_unlock(&env->data.write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&env->data.write_mutex);
		i = 0;
		while (i < env->data.nb_philo)
		{
			pthread_mutex_lock(&env->data.write_mutex);
			time_since_meal = get_timestamp() - env->philos[i].last_meal_time;
			if (time_since_meal > env->data.die && !env->data.stop)
			{
				printf("%ld %d died\n", get_timestamp() - env->data.start_time, env->philos[i].id);
				env->data.stop = 1;
				pthread_mutex_unlock(&env->data.write_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&env->data.write_mutex);
			i++;
		}
		if (env->data.nb_meals > 0)
		{
			pthread_mutex_lock(&env->data.write_mutex);
			if (env->data.nb_p_finish_eat >= env->data.nb_philo)
			{
				env->data.stop = 1;
				pthread_mutex_unlock(&env->data.write_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&env->data.write_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
