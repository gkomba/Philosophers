/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:51 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/03 16:32:43 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long      set_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
} 

long long       time_diff(long long start_time)
{
        return(set_time() - start_time);
}
void    *funtion(void *arg)
{
    t_teste *philo;
    int     stop;

    philo = (t_teste *)arg;
    stop = 0;
    while(!stop)
    {
        printf("[%lld] o %d filosofo esta pensando\n", time_diff(philo->curr_time), philo->id_piho);
        pthread_mutex_lock(philo->esquerdo);
        printf("[%lld] o %d filosofo pegou o garfo esquerdo\n", time_diff(philo->curr_time), philo->id_piho);
        pthread_mutex_lock(philo->direito);
        printf("[%lld] o %d filosofo pegou o garfo direito\n", time_diff(philo->curr_time), philo->id_piho);
        printf("[%lld] o %d filosofo esta comendo\n", time_diff(philo->curr_time), philo->id_piho);
        usleep(philo->comer * 1000);
        pthread_mutex_unlock(philo->esquerdo);
        pthread_mutex_unlock(philo->direito);
        printf("[%lld] o %d filosofo esta dormindo\n", time_diff(philo->curr_time), philo->id_piho);
        usleep(philo->dormir * 1000);
        stop = 1;
    }
    return NULL;
}

int main(int ac, char **av)
{
    t_teste *philo;
    int     nbr_philo;
    pthread_t   *th;
    pthread_mutex_t *forks;

    nbr_philo = atoi(av[1]);
    philo = (t_teste *)malloc(sizeof(t_teste) * nbr_philo);
    int     i;
    th = (pthread_t *)malloc(sizeof(pthread_t) * nbr_philo);
    forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr_philo);
    
    i = 0;
    while (i < nbr_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < nbr_philo)
    {
        philo[i].id_piho = i + 1;
        philo[i].morte = atoi(av[2]);
        philo[i].comer = atoi(av[3]);
        philo[i].dormir = atoi(av[4]);
        philo[i].esquerdo = &forks[i];
        philo[i].direito = &forks[(i + 1) % nbr_philo];
        philo[i].curr_time = set_time();
        if (pthread_create(&th[i], NULL, &funtion, &philo[i]) != 0 )
            perror("failed create philo");
        i++;
    }
    i = 0;
    while (i < nbr_philo)
    {
        pthread_join(th[i], NULL);
        i++;
    }
    while (i < nbr_philo)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    i = 0;
    free(philo);
    free(th);
    free(forks);
    return 0;
}
