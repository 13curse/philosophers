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

static int	monitor_check_stop(t_env *env)
{
	int	stop;

	pthread_mutex_lock(&env->data.write_mutex);
	stop = env->data.stop;
	pthread_mutex_unlock(&env->data.write_mutex);
	return (stop);
}

static int	monitor_check_death(t_env *env)
{
	int			i;
	long int	time_since_meal;

	i = 0;
	while (i < env->data.nb_philo)
	{
		pthread_mutex_lock(&env->data.write_mutex);
		time_since_meal = get_timestamp() - env->philos[i].last_meal_time;
		if (time_since_meal > env->data.die && !env->data.stop)
		{
			printf("%ld %d died\n",
				get_timestamp() - env->data.start_time, env->philos[i].id);
			env->data.stop = 1;
			pthread_mutex_unlock(&env->data.write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&env->data.write_mutex);
		i++;
	}
	return (0);
}

static int	monitor_check_full(t_env *env)
{
	int	full;

	full = 0;
	if (env->data.nb_meals > 0)
	{
		pthread_mutex_lock(&env->data.write_mutex);
		if (env->data.nb_p_finish_eat >= env->data.nb_philo)
		{
			env->data.stop = 1;
			full = 1;
		}
		pthread_mutex_unlock(&env->data.write_mutex);
	}
	return (full);
}

void	*monitor_routine(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		if (monitor_check_stop(env))
			return (NULL);
		if (monitor_check_death(env))
			return (NULL);
		if (monitor_check_full(env))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
