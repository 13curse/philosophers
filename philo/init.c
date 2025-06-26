/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:25:41 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/24 16:25:41 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_env *env)
{
	int	i;

	env->forks = malloc(sizeof(pthread_mutex_t) * env->data.nb_philo);
	if (!env->forks)
		return (printf("Error: forks allocation failed\n"), 1);
	i = 0;
	while (i < env->data.nb_philo)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (printf("Error: fork mutex initialization failed\n"), 1);
		i++;
	}
	return (0);
}

int	init_philosophers(t_env *env)
{
	int	i;

	env->philos = malloc(sizeof(t_philo) * env->data.nb_philo);
	if (!env->philos)
		return (printf("Error: philosophers allocation failed\n"), 1);
	i = 0;
	while (i < env->data.nb_philo)
	{
		env->philos[i].id = i + 1;
		env->philos[i].data = &env->data;
		env->philos[i].meals_eaten = 0;
		env->philos[i].finished = 0;
		env->philos[i].left_fork = &env->forks[i];
		env->philos[i].right_fork = &env->forks[(i + 1) % env->data.nb_philo];
		i++;
	}
	return (0);
}

int	init_env(t_env *env)
{
	int	i;

	if (init_forks(env))
		return (1);
	if (init_philosophers(env))
		return (1);
	if (pthread_mutex_init(&env->data.write_mutex, NULL) != 0)
		return (printf("Error: initialization of print mutex failed\n"), 1);
	env->data.start_time = get_timestamp();
	i = 0;
	while (i < env->data.nb_philo)
	{
		env->philos[i].last_meal_time = env->data.start_time;
		i++;
	}
	i = 0;
	while (i < env->data.nb_philo)
	{
		env->philos[i].meals_eaten = 0;
		i++;
	}
	return (0);
}

void	join_philosopher_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->data.nb_philo)
	{
		pthread_join(env->philos[i].thread_id, NULL);
		i++;
	}
}
