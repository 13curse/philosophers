/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:00:47 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/24 16:00:47 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}

static int	is_positive_int(const char *str)
{
	int		i;
	long	val;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	val = ft_atol(str);
	if (val <= 0 || val > INT_MAX)
		return (0);
	return (1);
}

static void	init_data(t_data *data, char **argv)
{
	data->nb_philo = atoi(argv[1]);
	data->die = atoi(argv[2]);
	data->eat = atoi(argv[3]);
	data->sleep = atoi(argv[4]);
	data->nb_p_finish_eat = 0;
	data->stop = 0;
	data->nb_meals = -1;
	if (argv[5])
		data->nb_meals = atoi(argv[5]);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: 4 or 5 arguments required\n");
		printf("Usage: ./philo nb_philo time_to_die");
		printf(" time_to_eat time_to_sleep [nb_meals]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive_int(argv[i]))
		{
			printf("Error: Argument %d ('%s')", i, argv[i]);
			printf(" is not a strictly positive integer\n");
			return (1);
		}
		i++;
	}
	init_data(data, argv);
	return (0);
}
