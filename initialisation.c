/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:41:38 by joudafke          #+#    #+#             */
/*   Updated: 2025/08/02 17:21:27 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_data_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = get_time();
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		i++;
	}
	pthread_mutex_init(&data->meals_mutex, NULL);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (i == data->number_of_philo - 1)
			data->philo[i].left_fork = &data->philo[0].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i + 1].right_fork;
		i++;
	}
	data->stop_simulation = 0;
}

static void	init_philo(t_data *data)
{
	int			i;
	int			created;

	i = 0;
	data->start_time = get_time();
	init_data_philo(data);
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
	{
		write(2, "Failed to create monitor thread\n", 31);
		return ;
	}
	data->monitor_created = 1;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]) != 0)
			break ;
		i++;
	}
	created = i;
	usleep(200);
	i = 0;
	while (i < created)
		pthread_join(data->philo[i++].thread, NULL);
}

void	init_data(int ac, char **av, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_required = ft_atoi(av[5]);
	else
		data->meals_required = -1;
	pthread_mutex_init(&data->print, NULL);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		exit(1);
	init_philo(data);
}
