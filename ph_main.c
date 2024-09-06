/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/06 12:27:10 by gkomba           ###   ########.fr       */
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

void	ft_create_philo(t_philo *philo,
		pthread_mutex_t *forks, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].time_to_die = params->time_to_die;
		philo[i].time_to_eat = params->time_to_eat;
		philo[i].time_to_sleep = params->time_to_sleep;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % params->nbr_of_philo];
		philo[i].curr_time = ft_set_time();
		philo[i].must_eat = params->must_eat;
		if (pthread_create(&philo[i].thread_nbr, NULL,
					&ft_routine, &philo[i]) != 0 )
			ft_putstr_fd("failed create philo", 2);
		i++;
	}
}

void	ft_join_philo(t_philo *philo, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_philo)
	{
		if (pthread_join(philo[i].thread_nbr, NULL) != 0)
			ft_putstr_fd("failed to join thread", 2);
		i++;
	}
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

int	ft_init_philo(t_params *params)
{
	t_philo	*philo;
	pthread_mutex_t *forks;

	philo = (t_philo *)malloc(sizeof(t_philo) * params->nbr_of_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 
			params->nbr_of_philo);
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
	return 0;
}
