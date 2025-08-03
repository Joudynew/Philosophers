/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:38:08 by joudafke          #+#    #+#             */
/*   Updated: 2025/08/03 16:19:23 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checkdead(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->print);
	is_dead = data->stop_simulation;
	pthread_mutex_unlock(&data->print);
	return (is_dead);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(int time_in_ms, t_data *data)
{
	long int	start;

	start = get_time();
	while (!checkdead(data) && (get_time() - start < time_in_ms))
		usleep(5000);
}

long int	timestamp(t_data *data)
{
	return (get_time() - data->start_time);
}

void	print_actions(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->stop_simulation)
		printf("%ld %d %s\n", timestamp(philo->data), philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}
