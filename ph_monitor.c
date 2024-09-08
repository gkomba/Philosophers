/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:36:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/08 10:39:53 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_all_philos_have_ate(t_philo *philo, t_monitor *monitor)
{
	int		i;

	i = 0;
	while (i < monitor->nbr_of_philo)
	{
		if (ft_check_times_ate(philo) < monitor->must_eat)
			return (0);
		i++;
	}
	if (monitor->must_eat)
	{
		pthread_mutex_lock(philo->message);
		printf("ALL PHILOS HAVE TAKE THE FOOD\n");
		pthread_mutex_unlock(philo->message);
		return (1);
	}
	return (0);
}

static	int	ft_set_philo_dead(t_monitor *monitor, t_philo *philo)
{
	int	index;

	index = -1;
	while (++index < monitor->nbr_of_philo)
	{
		if ((ft_set_time() - ft_check_last_time_ate(&philo[index]))
			> monitor->time_to_die)
		{
			ft_print_message("Filosofo Esta Morto", &philo[index]);
			ft_inform_is_dead(monitor, 1);
			return (1);
		}
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	int				i;
	t_monitor		*monitor;
	t_philo			*philo;

	philo = (t_philo *)arg;
	monitor = philo[0].monitor;
	while (!ft_check_dead(monitor))
	{
		if (ft_set_philo_dead(monitor, philo))
			break ;
		if (ft_all_philos_have_ate(philo, monitor))
		{
			ft_inform_is_dead(monitor, 1);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
