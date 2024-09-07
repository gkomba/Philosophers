/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 13:26:11 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	int				stop;
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (*(philo->dead))
			return (NULL);
		ft_philo_eat_and_sleep(philo);
		if (*(philo->dead))
			return (NULL);
		printf("[%ld] O %d filosofo esta pensando\n",
			ft_time_diff(philo->curr_time), philo->id_philo);
		if (*(philo->dead))
			return (NULL);
	}
	return (NULL);
}

void	ft_destroy_monitor(t_monitor *monitor)
{
	pthread_mutex_destroy(monitor->monitor_mutex);
}

void	ft_init_monitor(int argc, char **argv, t_params *monitor)
{
	if ((argc == 5) || (argc == 6))
	{
		monitor->nbr_of_philo = ft_atoi(argv[1]);
		monitor->time_to_die = ft_atoi(argv[2]);
		monitor->time_to_eat = ft_atoi(argv[3]);
		monitor->time_to_sleep = ft_atoi(argv[4]);
		monitor->curr_time = ft_set_time();
		monitor->is_dead = 0;
		if (pthread_mutex_int(monitor->monitor_mutex, NULL) != 0)
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

int	main(int argc, char **argv)
{
	t_monitor		monitor;
	t_philo			*philo;
	pthread_t		*monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		message_mutex;

	ft_init_monitor(argc, argv, &monitor);
	philo = (philo_t *)malloc(sizeof(t_philo) * monitor.nbr_of_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 
		monitor.nbr_of_philo);
	ft_init_philos(&monitor, &philo, &forks, &message_mutex)
	ft_init_mutexes(&forks, &message_mutex, monitor.nbr_of_philo);
	if (phtread_create(&monitro_thread, NULL, &ft_monitor, philo) != 0)
		ft_putstr_fd("failed to create  a tread", 2);
	ft_join_thread(philo, monitor.nbr_of_philo);
	if (pthread_join(monitor_thread, NULL) != 0)
		ft_putstr_fd("failde to join a thread", 2);
	ft_destroy_mutexes(&forks, &message_mutex, monitor.nbr_of_philo);
	ft_destroy_monitor(&monitor);
	free(philo);
	free(forks);
	return (0);
}
