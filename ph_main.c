/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/19 16:50:44 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_routine_case_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	ft_print_message("has taken a fork", philo);
	usleep(philo->monitor->time_to_die * 1000);
	pthread_mutex_unlock(philo->fork_r);
}

void	*ft_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->monitor->nbr_of_philo == 1)
	{
		ft_routine_case_one_philo(philo);
		return (NULL);
	}
	while (!ft_check_dead(philo->monitor))
	{
		ft_print_message("thinking", philo);
		ft_philo_eat_and_sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_monitor			monitor;
	t_philo				*philo;
	pthread_mutex_t		*forks;

	if (ft_init_monitor(argc, argv, &monitor) == 1)
		return (0);
	ft_init_monitor_mutexes(&monitor);
	philo = (t_philo *)malloc(sizeof(t_philo) * monitor.nbr_of_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* monitor.nbr_of_philo);
	ft_init_mutexes(forks, monitor.nbr_of_philo);
	ft_init_philos(&monitor, philo, forks);
	if (pthread_create(&monitor.monitor_thread, NULL, ft_monitor, philo) != 0)
		return (ft_putstr_fd("failed to create  a tread", 2), 1);
	ft_create_and_join_philo(philo, monitor.nbr_of_philo);
	if (pthread_join(monitor.monitor_thread, NULL) != 0)
		return (ft_putstr_fd("failde to join a thread", 2), 1);
	ft_destroy_mutexes(forks, monitor.nbr_of_philo);
	ft_destroy_monitor(&monitor);
	free(philo);
	free(forks);
	return (0);
}
