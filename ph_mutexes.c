/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:56:04 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/08 04:52:47 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(pthread_mutex_t *forks, int nbr_of_philo,
		pthread_mutex_t *message_mutex)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(message_mutex);
}

void	ft_destroy_monitor(t_monitor *monitor)
{
	pthread_mutex_destroy(&monitor->monitor_mutex);
	pthread_mutex_destroy(&monitor->check_dead);
	pthread_mutex_destroy(&monitor->check_last_meal);
	pthread_mutex_destroy(&monitor->times_eat);
}
