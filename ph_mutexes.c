/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:56:04 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 12:59:34 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(pthread_mutex_t *forks, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	ft_init_mutexes(pthread_mutex_t	*forks, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
