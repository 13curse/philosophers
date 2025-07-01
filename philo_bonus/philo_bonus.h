/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:55:10 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/27 13:55:10 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "stdio.h"
# include "stdlib.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include "unistd.h"
# include "semaphore.h"
# include "signal.h"
# include "limits.h"
# include "fcntl.h"
# include "pthread.h"

typedef struct s_data
{
	int			nb_philo;
	int			die;
	int			eat;
	int			sleep;
	int			nb_meals;
	pid_t		*pids;
	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_dead;
	long		start_time;
	int			stop;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	t_data		*data;
	pthread_t	monitor_thread;
	sem_t		meal_lock;
}	t_philo;

//-----INITIALIZE SEMAPHORES-----
// init.c
void		init_semaphores(t_data *data);

//-----CLEANING-----
// init.c
void		kill_all(t_data *data);
// main.c
void		clear_semaphores(t_data *data);

//-----INITIALIZE PHILOSOPHERS AND THEIR ROUTINE-----
// init_philo.c
void		launch_philos(t_data *data);
void		philo_routine(t_philo *philo);
void		philo_check_death(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
// init.c
long int	get_timestamp(void);
void		print_action(t_philo *philo, const char *action);
void		precise_sleep(long int duration_ms, t_philo *philo);
// philo_actions.c
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
// philo_routine.c
void		check_death_if_needed(t_philo *philo);
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

//-----PARSING-----
// parsing.c
int			parse_args(int argc, char **argv, t_data *data);

//-----MONITORING-----
// monitoring.c
int			ft_strcmp(const char *s1, const char *s2);
void		*monitor_routine(void *arg);

#endif