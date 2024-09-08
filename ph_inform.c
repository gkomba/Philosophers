/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_inform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:35:11 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/08 08:55:06 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_inform_is_dead(t_monitor *monitor, size_t value)
{
	pthread_mutex_lock(&monitor->check_dead);
	monitor->check_if_dead = value;
	pthread_mutex_unlock(&monitor->check_dead);
}

void	ft_inform_last_snack(t_philo *philo, size_t value)
{
	pthread_mutex_lock(philo->check_last_meal);
	philo->last_time_ate = value;
	pthread_mutex_unlock(philo->check_last_meal);
}

void	ft_inform_time_ate(t_philo *philo, int value)
{
	pthread_mutex_lock(philo->times_ate_mutex);
	philo->times_ate += value;
	pthread_mutex_unlock(philo->times_ate_mutex);
}
