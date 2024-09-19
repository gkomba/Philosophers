/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:34:25 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/19 16:58:41 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_dead(t_monitor *monitor)
{
	int	res;

	pthread_mutex_lock(&monitor->check_dead);
	res = monitor->check_if_dead;
	pthread_mutex_unlock(&monitor->check_dead);
	return (res);
}

size_t	ft_check_last_time_ate(t_philo *philo)
{
	size_t	res;

	pthread_mutex_lock(&philo->monitor->check_last_meal);
	res = philo->last_time_ate;
	pthread_mutex_unlock(&philo->monitor->check_last_meal);
	return (res);
}

int	ft_check_times_ate(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->monitor->times_eat);
	res = philo->times_ate;
	pthread_mutex_unlock(&philo->monitor->times_eat);
	return (res);
}
