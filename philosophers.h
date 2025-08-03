/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:38:23 by joudafke          #+#    #+#             */
/*   Updated: 2025/08/03 16:47:44 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long int		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				finished_eating;
	int				stop_simulation;
	long int		start_time;
	int				monitor_created;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	print;
	t_philo			*philo;
	pthread_t		monitor;
}					t_data;

void		init_data(int ac, char **av, t_data *data);
int			check_numbers(char *str);
int			is_not_valid(int ac, char **av);
int			ft_atoi(char *str);
int			checkdead(t_data *data);
void		ft_sleep(int time, t_data *data);
long int	get_time(void);
void		print_actions(t_philo *philo, char *action);
long int	timestamp(t_data *data);
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		sleep_and_think(t_philo *philo, t_data *data);
void		eat(t_philo *philo, t_data *data);
void		*routine(void *phi);
int			check_philo_death(t_data *data, int i);
void		*monitor_routine(void *arg);

#endif