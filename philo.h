/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:17 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/12 12:05:14 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h> 
# include <sys/time.h>

# define MAX 200

typedef struct s_monitor
{
	pthread_mutex_t		check_dead;
	pthread_mutex_t		check_last_meal;
	pthread_mutex_t		times_eat;
	pthread_mutex_t		message_mutex;
	size_t				time_to_sleep;
	size_t				time_to_die;
	size_t				time_to_eat;
	int					nbr_of_philo;
	int					check_if_dead;
	int					must_eat;
	pthread_t			monitor_thread;
}		t_monitor;

typedef struct s_philo
{
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*message;
	pthread_mutex_t		*check_dead;
	pthread_mutex_t		*check_last_meal;
	pthread_mutex_t		*times_ate_mutex;
	size_t				last_time_ate;
	size_t				start_time;
	int					times_ate;
	int					id_philo;
	t_monitor			*monitor;
	pthread_t			thread_nbr;
}				t_philo;

void	*ft_routine(void *arg);
void	*ft_monitor(void *arg);
void	ft_putstr_fd(char *s, int fd);
void	ft_destroy_monitor(t_monitor *monitor);
void	ft_destroy_mutexes(pthread_mutex_t *forks, int nbr_of_philo);
void	ft_philo_eat_and_sleep(t_philo *philo);
void	ft_print_message(char *fork, t_philo *philo);
void	ft_init_philos(t_monitor *monitor, t_philo *philo,
			pthread_mutex_t *forks);
void	ft_inform_is_dead(t_monitor *monitor, size_t value);
void	ft_inform_last_time_ate(t_philo *philo, size_t value);
void	ft_inform_time_ate(t_philo *philo, int value);
size_t	ft_time_diff(size_t start_time);
size_t	ft_set_time(void);
size_t	ft_check_last_time_ate(t_philo *philo);
int		ft_create_and_join_philo(t_philo *philo, int nbr_of_philo);
int		ft_init_monitor(int argc, char **argv, t_monitor *monitor);
int		ft_init_mutexes(pthread_mutex_t	*forks, int nbr_of_philo);
int		ft_init_monitor_mutexes(t_monitor *monitor);
int		ft_atoi(const char *nptr);
int		ft_check_dead(t_monitor *monitor);
int		ft_check_times_ate(t_philo *philo);

#endif
