/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:52:55 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/11 18:53:03 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_and_join_philo(t_philo *philo, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_create(&philo[i].thread_nbr, NULL, &ft_routine,
				&philo[i]) != 0)
			return (ft_putstr_fd("failed create philo", 2), 1);
		i++;
	}
	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_join(philo[i].thread_nbr, NULL) != 0)
			return (ft_putstr_fd("failed to join thread", 2), 1);
		i++;
	}
	return (0);
}
