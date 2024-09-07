/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:17 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/07 16:38:31 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h> 
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*message;
	pthread_mutex_t		*check_dead;
	pthread_mutex_t		*check_last_meal;
	pthread_mutex_t		*fork_l;
	size_t				last_time_ate;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				curr_time;
	int					id_philo;
	int					times_ate;
	int					*dead;
	int				nbr_of_philo;
	int					must_eat;
	pthread_t			thread_nbr;
}				t_philo;

typedef struct s_monitor
{
	pthread_mutex_t		*monitor_mutex;
	pthread_mutex_t		*check_dead;
	pthread_mutex_t		*check_last_meal;
	int				is_dead;
	int				check_if_dead;
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	t_philo				*philo;
}		t_monitor;

void	*ft_monitor(void *arg);
void	ft_putstr_fd(char *s, int fd);
void	ft_create_philo(t_philo *philo,
			pthread_mutex_t *forks, t_params *params);
void	ft_join_philo(t_philo *philo, t_params *params);
void	ft_destroy_mutexes(pthread_mutex_t *forks, t_params *params);
void	ft_init_mutexes(pthread_mutex_t	*forks, t_params *params);
void	ft_get_fork(t_philo *philo);
void	ft_philo_eat_and_sleep(t_philo *philo);
void	*ft_routine(void *arg);
size_t	ft_set_time(void);
size_t	ft_time_diff(size_t start_time);
int		ft_atoi(const char *nptr);
#endif
