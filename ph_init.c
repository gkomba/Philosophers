/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:58:12 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/08 05:58:57 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_monitor(int argc, char **argv, t_monitor *monitor)
{
	if ((argc == 5) || (argc == 6))
	{
		monitor->nbr_of_philo = ft_atoi(argv[1]);
		monitor->time_to_die = ft_atoi(argv[2]);
		monitor->time_to_eat = ft_atoi(argv[3]);
		monitor->time_to_sleep = ft_atoi(argv[4]);
		monitor->curr_time = ft_set_time();
		monitor->is_dead = 0;
		monitor->check_if_dead = 0;
		if (pthread_mutex_init(&monitor->monitor_mutex, NULL) != 0)
		{
			ft_putstr_fd("failed to initialize a mutex", 2);
			exit(1);
		}
		if (argv[5])
			monitor->must_eat = ft_atoi(argv[5]);
		else
			monitor->must_eat = 0;
	}
	else if (argc < 6)
	{
		printf("To few arguments\n");
	}
	else
		printf("To Many arguments\n");
}

void	ft_init_monitor_mutexes(t_monitor *monitor)
{
	if (pthread_mutex_init(&monitor->monitor_mutex, NULL) != 0)
	{
		ft_putstr_fd("failed to initialize a mutex", 2);
		exit(1);
	}
	if (pthread_mutex_init(&monitor->check_dead, NULL) != 0)
	{
		ft_putstr_fd("failed to initialize a mutex", 2);
		exit(1);
	}
	if (pthread_mutex_init(&monitor->check_last_meal, NULL) != 0)
	{
		ft_putstr_fd("failed to initialize a mutex", 2);
		exit(1);
	}
	if (pthread_mutex_init(&monitor->times_eat, NULL) != 0)
	{
		ft_putstr_fd("failed to initialize a mutex", 2);
		exit(1);
	}
	
}

void	ft_init_philos(t_monitor *monitor, t_philo *philo,
		pthread_mutex_t *forks, pthread_mutex_t *message_mutex)
{
	int	i;

	i = 0;
	while (i < monitor->nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].time_to_die = monitor->time_to_die;
		philo[i].time_to_eat = monitor->time_to_eat;
		philo[i].time_to_sleep = monitor->time_to_sleep;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % monitor->nbr_of_philo];
		philo[i].message = message_mutex;
		philo[i].check_dead = &monitor->check_dead;
		philo[i].check_last_meal = &monitor->check_last_meal;
		philo[i].times_ate_mutex = &monitor->times_eat;
		philo[i].times_ate = 0;
		philo[i].last_time_ate = ft_set_time();
		philo[i].curr_time = ft_set_time();
		philo[i].monitor = monitor;
		if (pthread_create(&philo[i].thread_nbr, NULL,
			&ft_routine, &philo[i]) != 0)
		{
			ft_putstr_fd("failed create philo", 2);
			exit(1);
		}
		i++;
	}
}

void	ft_init_mutexes(pthread_mutex_t	*forks, int nbr_of_philo,
		pthread_mutex_t *message_mutex)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_putstr_fd("failed to initialize a mutex", 2);
			exit(1);
		}
		i++;
	}
	if (pthread_mutex_init(message_mutex, NULL) != 0)
	{
		ft_putstr_fd("failed to initialize a mutex", 2);
		exit(1);
	}
}
