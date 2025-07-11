/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:24:05 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/26 21:21:18 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include <sys/time.h>
# include "pthread.h"
# include "unistd.h"
# include "limits.h"

// valgrind --tool=helgrind ./philo

typedef struct s_data
{
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				nb_meals;
	long int		start_time;
	pthread_mutex_t	write_mutex;
	int				nb_p_finish_eat;
	int				stop;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
	long int		last_meal_time;
	int				meals_eaten;
	int				finished;
}	t_philo;

typedef struct s_env
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_data			data;
}	t_env;

//-----INITIALIZE STRUCTURES AND THREADS-----
// init.c
int			init_forks(t_env *env);
int			init_philosophers(t_env *env);
int			init_env(t_env *env);
void		join_philosopher_threads(t_env *env);

//-----PARSING-----
// parsing.c
int			parse_args(int argc, char **argv, t_data *data);

//-----CLEANING-----
// main.c
void		destroy_env(t_env *env);

//-----MONITOR THREADS--
// monitoring.c
void		*monitor_routine(void *arg);
int			ft_strcmp(const char *s1, const char *s2);

//-----CREATE PHILOSOPHER ROUTINE-----
// init_philo.c
long int	get_timestamp(void);
void		print_action(t_philo *philo, const char *action);
void		precise_sleep(long int duration_ms, t_data *data);
void		*philosopher_routine(void *arg);
int			create_philosopher_threads(t_env *env);
// philo_routine.c
void		philo_routine_loop(t_philo *philo);
void		*solo_philo(t_philo *philo);
int			philo_check_stop(t_philo *philo);
int			philo_check_if_full(t_philo *philo,
				int left_locked, int right_locked);
void		philo_check_meals(t_philo *philo, int *done);
// philo_actions.c
void		philo_take_forks(t_philo *philo,
				int *left_locked, int *right_locked);
void		philo_release_forks(t_philo *philo,
				int left_locked, int right_locked);
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);

#endif