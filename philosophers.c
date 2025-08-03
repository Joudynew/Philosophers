/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:54:36 by joudafke          #+#    #+#             */
/*   Updated: 2025/08/02 17:20:46 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
		pthread_mutex_destroy(&data->philo[i++].right_fork);
	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->print);
	free(data->philo);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (is_not_valid(ac, av) || ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	init_data(ac, av, &data);
	if (data.monitor_created)
		pthread_join(data.monitor, NULL);
	free_data(&data);
	return (0);
}
