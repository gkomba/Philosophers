/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 13:26:11 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	int				stop;
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->must_eat == 0)
	{
		philo->must_eat = 1;
		stop = 0;
	}
	while (philo->must_eat)
	{
		ft_philo_eat_and_sleep(philo);
		printf("[%ld] O %d filosofo esta pensando\n",
			ft_time_diff(philo->curr_time), philo->id_philo);
		if (stop != 0)
			philo->must_eat--;
	}
	printf("philo nbr [%d] ete %d times\n",
		philo->id_philo, philo->times_eaten);
	return (NULL);
}

void	ft_create_forks(pthread_mutex_t	*forks, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	ft_init_philo(t_params *params)
{
	t_philo					*philo;
	pthread_mutex_t			*forks;

	philo = (t_philo *)malloc(sizeof(t_philo) * params->nbr_of_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* params->nbr_of_philo);
	ft_init_mutexes(forks, params);
	ft_create_philo(philo, forks, params);
	ft_join_philo(philo, params);
	ft_destroy_mutexes(forks, params);
	free(philo);
	free(forks);
}

void	ft_init_params(char **argv)
{
	t_params	params;

	params.nbr_of_philo = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params.must_eat = ft_atoi(argv[5]);
	else
		params.must_eat = 0;
	ft_init_philo(&params);
}

int	main(int argc, char **argv)
{
	if ((argc == 5) || (argc == 6))
		ft_init_params(argv);
	else if (argc < 6)
	{
		printf("To few arguments\n");
	}
	else
		printf("To Many arguments\n");
	return (0);
}
