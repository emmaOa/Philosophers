#include "philosophers.h"

int     print_msg(char *str, t_philo *philo, int id_philo)
{
    struct timeval	cur_time;
    char *di;

    di = "is die";
    gettimeofday(&cur_time, NULL);
    if (str == di)
    {
        pthread_mutex_lock(&philo->mu_msg);
        printf("%ld %d %s\n",
 	    	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->first_time), id_philo, str);
    }
    else
    {
        pthread_mutex_lock(&philo->mu_msg);
        printf("%ld %d %s\n",
 	    	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->first_time), id_philo, str);
        pthread_mutex_unlock(&philo->mu_msg);
    }
    return 0;
}

void ft_eat(t_philo *philo)
{
    struct timeval	cur_time;

    gettimeofday(&cur_time, NULL);
    pthread_mutex_lock(&philo->forks[(philo->id_philo + 1) % philo->nb_philo]);
    pthread_mutex_lock(&philo->forks[philo->id_philo]);
    print_msg("has taken a fork", philo, philo->id_philo);
    print_msg("is eating", philo, philo->id_philo);
    philo->last_eat[philo->id_philo] = ((cur_time.tv_sec * 1000) + cur_time.tv_usec / 1000);
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->forks[(philo->id_philo + 1) % philo->nb_philo]);
    pthread_mutex_unlock(&philo->forks[philo->id_philo]);
    print_msg("is sleeping", philo, philo->id_philo);
    usleep(philo->time_to_sleep * 1000);
}
