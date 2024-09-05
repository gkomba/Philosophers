/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/05 19:21:53 by gkomba           ###   ########.fr       */
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

void	ft_get_fork(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		printf("[%ld] O %d filosofo pegou o garfo direito\n", 
				ft_time_diff(philo->curr_time),
				philo->id_philo);
		pthread_mutex_lock(philo->fork_l);
		printf("[%ld] O %d filosofo pegou o garfo esquerdo\n", 
				ft_time_diff(philo->curr_time),
				philo->id_philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		printf("[%ld] O %d filosofo pegou o garfo direito\n", 
				ft_time_diff(philo->curr_time),
				philo->id_philo);
		pthread_mutex_lock(philo->fork_r);
		printf("[%ld] O %d filosofo pegou o garfo esquerdo\n", 
				ft_time_diff(philo->curr_time),
				philo->id_philo);
	}
}

void	ft_philo_eat_and_sleep(t_philo *philo)
{
	ft_get_fork(philo);
	printf("[%ld] O %d filosofo esta comendo\n", 
			ft_time_diff(philo->curr_time),
			philo->id_philo);
	philo->times_eaten++;
	philo->last_time_ate = philo->curr_time;
	usleep(philo->time_to_eat * 1000);	
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	printf("[%ld] O %d filosofo esta dormindo\n", 
			ft_time_diff(philo->curr_time),
			philo->id_philo);
	usleep(philo->time_to_sleep * 1000);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int	stop;

	philo = (t_philo *)arg;
	if (philo->must_eat == 0)
	{
		philo->must_eat = 1;
		stop = 0;
	}
	while(philo->must_eat)
	{
		ft_philo_eat_and_sleep(philo);
		printf("[%ld] O %d filosofo esta pensando\n", 
				ft_time_diff(philo->curr_time),
				philo->id_philo);
		if (stop != 0)
			philo->must_eat--;
	}
	printf("philo nbr [%d] ete %d times\n", 
			philo->id_philo, philo->times_eaten);
	return NULL;
}

void	ft_create_philo(int nbr_of_philo, t_philo *philo,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % nbr_of_philo];
		philo[i].curr_time = ft_set_time();
		if (pthread_create(&philo[i].thread_nbr, NULL, 
					&ft_routine, &philo[i]) != 0)
			perror("failed create philo");
		i++;
	}
}

int	ft_init_philo(t_philo *philo)
{
	pthread_mutex_t *forks;
	int		i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 
			philo->nbr_of_philo);
	i = 0;
	while (i < philo->nbr_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	ft_create_philo(philo->nbr_of_philo, philo, forks);
	i = 0;
	if (philo->nbr_of_philo == 1)
		pthread_join(philo[i].thread_nbr, NULL);
	else
	{
		i = 0;
		while (i < philo->nbr_of_philo)
		{
			pthread_join(philo[i].thread_nbr, NULL);
			i++;
		}
	}
	i = 0;
	while (i < philo->nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philo);
	free(forks);
}

void	ft_init_params(char **argv)
{
	t_philo	*philo;

	philo->nbr_of_philo = ft_atoi(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * philo->nbr_of_philo);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->must_eat = ft_atoi(argv[5]);
	else
		philo->must_eat = 0;
	ft_init_philo(philo);
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
	return 0;
}
