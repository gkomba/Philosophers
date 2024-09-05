/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/05 16:55:09 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_set_time(void)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
} 

size_t	ft_time_diff(size_t start_time)
{
	return(ft_set_time() - start_time);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int	stop;

	philo = (t_philo *)arg;
	if (philo->inumber_of_times_each_philosopher_must_eat == 0)
	{
		philo->number_of_times_each_philosopher_must_eat = 1;
		stop = 0;
	}
	while(philo->number_of_times_each_philosopher_must_eat)
	{	
		printf("[%ld] O %d filosofo esta pensando\n", ft_time_diff(philo->curr_time), philo->id_philo);
		if (philo->id_philo % 2 == 0)
		{
			pthread_mutex_lock(philo->fork_r);
			printf("[%ld] O %d filosofo pegou o garfo direito\n", ft_time_diff(philo->curr_time), philo->id_philo);
			pthread_mutex_lock(philo->fork_l);
			printf("[%ld] O %d filosofo pegou o garfo esquerdo\n", ft_time_diff(philo->curr_time), philo->id_philo);
		}
		else
		{
			pthread_mutex_lock(philo->fork_l);
			printf("[%ld] O %d filosofo pegou o garfo direito\n", ft_time_diff(philo->curr_time), philo->id_philo);
			pthread_mutex_lock(philo->fork_r);
			printf("[%ld] O %d filosofo pegou o garfo esquerdo\n", ft_time_diff(philo->curr_time), philo->id_philo);
		}
		printf("[%ld] O %d filosofo esta comendo\n", ft_time_diff(philo->curr_time), philo->id_philo);
		philo->times_eaten++;
		philo->last_time_ate = philo->curr_time;
		usleep(philo->time_to_eat * 1000);
		if ((philo->curr_time - philo->last_time_ate) >= philo->time_to_die)
		{
			printf("die %ld\n", philo->time_to_die);
			printf("last %ld\n", philo->last_time_ate);
			printf("[%ld] O %d filosofo morreu\n", ft_time_diff(philo->curr_time), philo->id_philo);
			return NULL;
		}
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		printf("[%ld] O %d filosofo esta dormindo\n", ft_time_diff(philo->curr_time), philo->id_philo);
		usleep(philo->time_to_sleep * 1000);
		if (stop != 0)
			philo->number_of_times_each_philosopher_must_eat--;
	}
	printf("philo nbr [%d] ete %d times\n", philo->id_philo, philo->times_eaten);
	return NULL;
}

int	init_philo(int nbr_of_philo, size_t time_to_die, size_t time_to_eat, size_t time_to_sleep, int must_eat)
{
	t_philo		*philo;
	pthread_mutex_t *forks;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * nbr_of_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr_of_philo);
	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].time_to_die = time_to_die;
		philo[i].time_to_eat = time_to_eat;
		philo[i].time_to_sleep = time_to_sleep;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % nbr_of_philo];
		philo[i].curr_time = ft_set_time();
		philo[i].number_of_times_each_philosopher_must_eat = must_eat;
		if (pthread_create(&philo[i].thread_nbr, NULL, &ft_routine, &philo[i]) != 0 )
			perror("failed create philo");
		i++;
	}
	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_join(philo[i].thread_nbr, NULL);
		i++;
	}
	while (i < nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	i = 0;
	free(philo);
	free(forks);
}

int	main(int argc, char **argv)
{
	t_philo vars;

	if ((argc == 5) || (argc == 6))
	{
		if (argv[5] && ft_atoi(argv[5]) >= 1)
		{
			init_philo(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), ft_atoi(argv[5]));
		}
		else
			init_philo(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), 0);
	}
	else if (argc < 6)
	{
		printf("To few arguments\n");        
	}
	else
		printf("To Many arguments\n"); 
	return 0;
}
