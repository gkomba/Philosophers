int	ft_init_philo(t_monitor *monitor, t_philo *philo, &forks,
		pthread_mutex_t *message_mutex)
{
	int	i;

	i = 0;
	while (i < monitor->nbr_of_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].fork_l = &forks[i];
		philo[i].fork_r = &forks[(i + 1) % params->nbr_of_philo];
		philo[i].message = message_mutex;
		philo[i].times_ate = 0;
		philo[i].last_time_ate = ft_set_time();
		philo[i].monitor = monitor;
		if (pthread_create(&philo[i].thread_nbr, NULL,
			&ft_routine, &philo[i]) != 0)
		{
			ft_putstr_fd("failed create philo", 2);
			exit(1);
		}
		i++;
	}
}

void	ft_init_mutexes(pthread_mutex_t	*forks, int nbr_of_philo,
		pthread_mutex_t *message_mutex)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_putstr_fd("failed to initialize a mutex", 2);
			exit(1);
		}
		i++;
	}
	if (pthread_mutex_init(message_mutex, NULL) != 0)
	{
		ft_putstr_fd("failed to initialize a mutex", 2);
		exit(1);
	}
}

void	ft_destroy_mutexes(pthread_mutex_t *forks, int nbr_of_philo,
		pthread_mutex_t *message_mutex)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(message_mutex);
}
