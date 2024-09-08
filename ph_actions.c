/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:00:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/08 05:58:52 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(char *sms, t_philo *philo)
{
	if (pthread_mutex_lock(philo->message) == 0)
	{
		if (!ft_check_dead(philo->monitor))
			printf("[%ld] %d %s\n",
				ft_time_diff(philo->curr_time), philo->id_philo, sms);
		pthread_mutex_unlock(philo->message);
	}
}

void	ft_get_fork(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		ft_print_message("Filosofo Pegou O Garfo Direito", philo);
		pthread_mutex_lock(philo->fork_l);
		ft_print_message("Filosofo Pegou O Garfo Esquerdo", philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		ft_print_message("Filosofo Pegou O Garfo Esquerdo", philo);
		pthread_mutex_lock(philo->fork_r);
		ft_print_message("Filosofo Pegou O Garfo Direito", philo);
	}
}

void	ft_philo_eat_and_sleep(t_philo *philo)
{
	ft_get_fork(philo);
	ft_print_message("Filosofo Esta Comendo", philo);
	philo->times_ate++;
	philo->last_time_ate = ft_set_time();
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	ft_print_message("Filosofo Esta Dormindo", philo);
	usleep(philo->time_to_sleep * 1000);
}
