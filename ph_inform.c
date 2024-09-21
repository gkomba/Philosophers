/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_inform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:35:11 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/21 11:35:14 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_inform_stop_simulation(t_monitor *monitor, size_t value)
{
	pthread_mutex_lock(&monitor->check_dead);
	monitor->stop_simulation = value;
	pthread_mutex_unlock(&monitor->check_dead);
}

void	ft_inform_last_time_ate(t_philo *philo, size_t value)
{
	pthread_mutex_lock(&philo->monitor->check_last_meal);
	philo->last_time_ate = value;
	pthread_mutex_unlock(&philo->monitor->check_last_meal);
}

void	ft_inform_time_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->times_eat);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->monitor->times_eat);
}
