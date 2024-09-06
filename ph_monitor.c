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

void	ft_vefify_if_died(t_philo *philo)
{
	if ((philo->curr_time - philo->last_time_ate) 
			>= philo->time_to_die)
	{
		printf("die %ld\n", philo->time_to_die);
		printf("last %ld\n", philo->last_time_ate);
		printf("[%ld] O %d filosofo morreu\n", 
				ft_time_diff(philo->curr_time),
				philo->id_philo);
		return ;
	}
}
