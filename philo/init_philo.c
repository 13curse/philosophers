/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:44:34 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/24 16:44:34 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// gettimeofday donne le temps en secondes et microsecondes
// on convertis donc le tout en millisecondes
long int	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// affiche les actions des philosophes protégées par un mutex
void	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->stop
		|| (philo->data->stop && !ft_strcmp(action, "died")))
		printf("%ld %d %s\n",
			get_timestamp() - philo->data->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

// tant que la durée demandée n'est pas écoulée on dort par petits intervalles
// ici 100 microsecondes
void	precise_sleep(long int duration_ms, t_data *data)
{
	long int	start;
	int			stop;

	start = get_timestamp();
	while ((get_timestamp() - start) < duration_ms)
	{
		pthread_mutex_lock(&data->write_mutex);
		stop = data->stop;
		pthread_mutex_unlock(&data->write_mutex);
		if (stop)
			break ;
		usleep(100);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (solo_philo(philo));
	usleep((philo->id - 1) * 2000);
	philo_routine_loop(philo);
	return (NULL);
}

int	create_philosopher_threads(t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	while (i < env->data.nb_philo)
	{
		ret = pthread_create(&env->philos[i].thread_id, NULL,
				philosopher_routine, &env->philos[i]);
		if (ret != 0)
			return (printf("Error: thread creation for philosopher %d failed\n",
					i + 1), 1);
		i++;
	}
	return (0);
}
