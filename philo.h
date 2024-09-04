/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:17 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/04 16:08:35 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <sys/time.h>
#include "libft/libft.h"

typedef struct s_philo
{
    pthread_mutex_t *fork_r;
    pthread_mutex_t *fork_l;
    pthread_t           thread_nbr;
    int                 id_philo;
    int                 times_eaten;
    int                 *dead;
    size_t              last_time_eaten;
    size_t              time_to_die;
    size_t              time_to_eat;
    size_t              time_to_sleep;
    size_t              curr_time;
}                       t_philo;


typedef struct s_monitor
{
    int                 number_of_times_each_philosopher_must_eat;
}                       t_monitor;

#endif