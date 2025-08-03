/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:59:26 by joudafke          #+#    #+#             */
/*   Updated: 2025/08/03 16:50:41 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_and_think(t_philo *philo, t_data *data)
{
	long	current_time;
	long	time_since_meal;
	int		should_wait;

	print_actions(philo, "is sleeping");
	ft_sleep(data->time_to_sleep, data);
	print_actions(philo, "is thinking");
	pthread_mutex_lock(&data->meals_mutex);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal_time;
	should_wait = (data->time_to_die - time_since_meal > data->time_to_eat);
	pthread_mutex_unlock(&data->meals_mutex);
	while (should_wait && !checkdead(data))
	{
		ft_sleep(100, data);
		pthread_mutex_lock(&data->meals_mutex);
		current_time = get_time();
		time_since_meal = current_time - philo->last_meal_time;
		should_wait = (data->time_to_die - time_since_meal > data->time_to_eat);
		pthread_mutex_unlock(&data->meals_mutex);
	}	
}

void	eat(t_philo *philo, t_data *data)
{
	take_forks(philo);
	pthread_mutex_lock(&data->meals_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meals_mutex);
	print_actions(philo, "is eating");
	ft_sleep(data->time_to_eat, data);
	release_forks(philo);
	pthread_mutex_lock(&data->meals_mutex);
	if (philo->meals_eaten == data->meals_required && data->meals_required > 0)
	{
		data->finished_eating++;
		if (data->finished_eating == data->number_of_philo)
		{
			pthread_mutex_lock(&data->print);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->print);
		}
	}
	pthread_mutex_unlock(&data->meals_mutex);
}

void	*routine(void *phi)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	if ((philo->id % 2) == 0)
		usleep(500);
	if (data->number_of_philo == 1)
	{
		print_actions(philo, "has taken a fork");
		ft_sleep(data->time_to_die, data);
		return (NULL);
	}
	while (1)
	{
		eat(philo, data);
		sleep_and_think(philo, data);
		if (checkdead(data))
			break ;
	}
	return (NULL);
}
