#include "philosophers.h"

int ft_eat(t_philo *philo)
{
    struct timeval	cur_time;

    gettimeofday(&cur_time, NULL);
    pthread_mutex_lock(&philo->forks[philo->id_philo]);
    printf("%ld %d has taken a fork  %d\n",
     		((cur_time.tv_sec / 1000) + (cur_time.tv_usec * 1000)), philo->id_philo, philo->id_philo);
    pthread_mutex_lock(&philo->forks[(philo->id_philo + 1) % philo->nb_philo]);
    printf("%ld %d has taken a fork  %d\n",
     		((cur_time.tv_sec / 1000) + (cur_time.tv_usec * 1000)), philo->id_philo, ((philo->id_philo + 1) % philo->nb_philo));
    printf("%ld %d is eating\n",
     		((cur_time.tv_sec / 1000) + (cur_time.tv_usec * 1000)), philo->id_philo);
    philo->last_eat[philo->id_philo] = (cur_time.tv_sec / 1000) + (cur_time.tv_usec * 1000);
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->forks[(philo->id_philo + 1) % philo->nb_philo]);
    pthread_mutex_unlock(&philo->forks[philo->id_philo]);
    printf("%ld %d is sleeping\n",
			((cur_time.tv_sec / 1000) + (cur_time.tv_usec * 1000)), philo->id_philo);
    usleep(philo->time_to_sleep * 1000);
    return 1;
}
