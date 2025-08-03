/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:40:16 by joudafke          #+#    #+#             */
/*   Updated: 2025/08/03 16:22:53 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_death(t_data *data, int i)
{
	long	current_time;

	current_time = get_time();
	if ((current_time - data->philo[i].last_meal_time) > data->time_to_die)
	{
		pthread_mutex_lock(&data->print);
		if (!data->stop_simulation)
		{
			printf("%ld %d died\n", timestamp(data), data->philo[i].id);
			data->stop_simulation = 1;
		}
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		death_detected;

	data = (t_data *)arg;
	while (!checkdead(data))
	{
		i = 0;
		while (i < data->number_of_philo && !checkdead(data))
		{
			pthread_mutex_lock(&data->meals_mutex);
			death_detected = check_philo_death(data, i);
			pthread_mutex_unlock(&data->meals_mutex);
			if (death_detected)
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_actions(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_actions(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_actions(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_actions(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
