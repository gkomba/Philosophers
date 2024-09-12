/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:58:12 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/12 12:05:46 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_monitor(int argc, char **argv, t_monitor *monitor)
{
	if ((argc == 5) || (argc == 6))
	{
		if (ft_atoi(argv[1]) == MAX)
			return (printf("To exceded number of philos\n"), 1);
		monitor->nbr_of_philo = ft_atoi(argv[1]);
		monitor->time_to_die = ft_atoi(argv[2]);
		monitor->time_to_eat = ft_atoi(argv[3]);
		monitor->time_to_sleep = ft_atoi(argv[4]);
		monitor->check_if_dead = 0;
		if (argv[5])
			monitor->must_eat = ft_atoi(argv[5]);
		else
			monitor->must_eat = 0;
	}
	else if (argc < 6)
		return (printf("To few arguments\n"), 1);
	else
		return (printf("To Many arguments\n"), 1);
	return (0);
}

int	ft_init_monitor_mutexes(t_monitor *monitor)
{
	if (pthread_mutex_init(&monitor->check_dead, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	if (pthread_mutex_init(&monitor->check_last_meal, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	if (pthread_mutex_init(&monitor->times_eat, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	if (pthread_mutex_init(&monitor->message_mutex, NULL) != 0)
		return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
	return (0);
}

void	ft_init_philos(t_monitor *monitor, t_philo *philo,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < monitor->nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % monitor->nbr_of_philo];
		philo[i].message = &monitor->message_mutex;
		philo[i].check_dead = &monitor->check_dead;
		philo[i].check_last_meal = &monitor->check_last_meal;
		philo[i].times_ate_mutex = &monitor->times_eat;
		philo[i].times_ate = 0;
		philo[i].last_time_ate = ft_set_time();
		philo[i].start_time = ft_set_time();
		philo[i].monitor = monitor;
		i++;
	}
}

int	ft_init_mutexes(pthread_mutex_t	*forks, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (ft_putstr_fd("failed to initialize a mutex", 2), 1);
		i++;
	}
	return (0);
}
