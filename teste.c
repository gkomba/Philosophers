void	*check_death(void *arg)
{
	t_philo	*philos;
	int		n_philos;
	int		all_done;
	int		i;
	
	philos = (t_philo *)arg;
	n_philos = philos[0].thread_id;
	while (!*(philos[0].simulation_stop))
	{
		all_done = 1;
		i = 0;
		while (i < n_philos)
		{
			pthread_mutex_lock(philos[i].eaten_lock);
			if (philos[i].n_times_to_eat != -1
				&& philos[i].times_eaten < philos[i].n_times_to_eat)
				all_done = 0;
			pthread_mutex_unlock(philos[i].eaten_lock);
			pthread_mutex_lock(philos[i].last_meal_lock);
			if (current_timestamp() - philos[i].last_meal_time
				> philos[i].time_to_die)
			{
				pthread_mutex_unlock(philos[i].last_meal_lock);
				print_status(&philos[i], "morreu");
				*(philos[0].simulation_stop) = 1;
				return (NULL);
			}
			pthread_mutex_unlock(philos[i].last_meal_lock);
			i++;
		}
		if (all_done)
		{
			*(philos[0].simulation_stop) = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
