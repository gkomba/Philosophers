/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:00:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 13:40:27 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(char fork, t_philo *philo)
{
	if (pthread_mutex_lock(philo->message) == 0)
	{
		if (fork == 'r')
			printf("[%ld] O %d filosofo pegou o garfo direito\n",
				ft_time_diff(philo->curr_time), philo->id_philo);
		else if (fork == 'l')
			printf("[%ld] O %d filosofo pegou o garfo esquerdo\n",
				ft_time_diff(philo->curr_time), philo->id_philo);
		pthread_mutex_unlock(philo->message);
	}
	else
		return ;
}

void	ft_get_fork(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		ft_print_message('r', philo);
		pthread_mutex_lock(philo->fork_l);
		ft_print_message('l', philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		ft_print_message('l', philo);
		pthread_mutex_lock(philo->fork_r);
		ft_print_message('r', philo);
	}
}

void	ft_philo_eat_and_sleep(t_philo *philo)
{
	ft_get_fork(philo);
	printf("[%ld] O %d filosofo esta comendo\n",
		ft_time_diff(philo->curr_time), philo->id_philo);
	philo->times_eaten++;
	philo->last_time_ate = philo->curr_time;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	printf("[%ld] O %d filosofo esta dormindo\n",
		ft_time_diff(philo->curr_time), philo->id_philo);
	usleep(philo->time_to_sleep * 1000);
}
