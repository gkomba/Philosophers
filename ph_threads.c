/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:52:55 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 13:41:19 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_times(t_philo *philo, t_params *params)
{
	philo->time_to_die = params->time_to_die;
	philo->time_to_eat = params->time_to_eat;
	philo->time_to_sleep = params->time_to_sleep;
	philo->curr_time = ft_set_time();
	philo->must_eat = params->must_eat;
}

void	ft_create_philo(t_philo *philo, pthread_mutex_t *forks,
		t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_philo)
	{
		philo[i].nbr_of_philo = params->nbr_of_philo;
		philo[i].id_philo = i + 1;
		ft_set_times(&philo[i], params);
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % params->nbr_of_philo];
		philo[i].message = params->message;
		if (pthread_create(&philo[i].thread_nbr, NULL,
				&ft_routine, &philo[i]) != 0)
		{
			ft_putstr_fd("failed create philo", 2);
			exit(1);
		}
		i++;
	}
}

void	ft_join_philo(t_philo *philo, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_join(philo[i].thread_nbr, NULL) != 0)
		{
			ft_putstr_fd("failed to join thread", 2);
			exit(1);
		}
		i++;
	}
}
