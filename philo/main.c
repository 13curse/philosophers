/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:06:03 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/24 17:06:03 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->data.nb_philo)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->data.write_mutex);
	free(env->philos);
	free(env->forks);
}

int	main(int argc, char **argv)
{
	t_env		env;
	pthread_t	monitor_thread;

	if (parse_args(argc, argv, &env.data))
		return (1);
	if (init_env(&env))
		return (destroy_env(&env), 1);
	if (create_philosopher_threads(&env))
		return (destroy_env(&env), 1);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &env) != 0)
		return (destroy_env(&env), 1);
	pthread_join(monitor_thread, NULL);
	join_philosopher_threads(&env);
	destroy_env(&env);
	return (0);
}
