/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:36:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 13:03:19 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	*ft_monitor(void *arg)
{
	t_philo		*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].nbr_of_philo)
		{
			pthread_mutex_lock(philos[i].check_last_meal);
			if (ft_time_diff(philos[i].last_time_ate) >
					philos[i].time_to_die)
			{
				printf("[%ld] O %d filosofo MORREU\n",
					ft_time_diff(philos[i].curr_time),
					philos[i].id_philo);
				*(philos[i].dead) = 1;
				pthread_mutex_unlock(philos[i].check_last_meal);
				return (NULL);
			}
			pthread_mutex_unlock(philos[i].check_last_meal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}*/

void	*ft_monitor(void *arg)
{
	t_philo		*philos;
	int			i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].nbr_of_philo)
		{
			pthread_mutex_lock(philos[i].check_last_meal);
			if (ft_set_time() - philos[i].last_time_ate
				>= philos[i].time_to_die / 2)
			{
				printf("[%ld] O %d filosofo MORREU\n",
					ft_time_diff(philos[i].curr_time),
					philos[i].id_philo);
				*(philos[i].dead) = 1;
				pthread_mutex_unlock(philos[i].check_last_meal);
				return (NULL);
			}
			pthread_mutex_unlock(philos[i].check_last_meal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

/*void	*ft_monitor(void *arg)
{
	t_philo	*philos;
	int		n_philos;
	int		all_done;
	int		i;

	philos = (t_philo *)arg;
	n_philos = philos[0].thread_id;
	while (!*(philos[0].simulation_stop))
	{
		all_done = 1;
		i = 0;
		while (i < n_philos)
		{
			pthread_mutex_lock(philos[i].eaten_lock);
			if (philos[i].n_times_to_eat != -1
				&& philos[i].times_eaten < 
				philos[i].n_times_to_eat)
				all_done = 0;
			pthread_mutex_unlock(philos[i].eaten_lock);
			pthread_mutex_lock(philos[i].last_meal_lock);
			if (current_timestamp() - philos[i].last_meal_time
				> philos[i].time_to_die)
			{
				pthread_mutex_unlock(philos[i].last_meal_lock);
				print_status(&philos[i], "morreu");
				*(philos[0].simulation_stop) = 1;
				return (NULL);
			}
			pthread_mutex_unlock(philos[i].last_meal_lock);
			i++;
		}
		if (all_done)
		{
			*(philos[0].simulation_stop) = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}*/
