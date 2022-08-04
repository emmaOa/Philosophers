#include "philosophers.h"

int     print_msg(char *str, t_philo *philo)
{
    struct timeval	cur_time;
    char *di;

    di = "is die";
    if (ft_strcmp(di, str) == 0)
    {
        pthread_mutex_lock(&philo->data->mu_msg);
        gettimeofday(&cur_time, NULL);
        printf("%ld %d %s\n",
 	    	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->data->first_time), philo->id, str);
        pthread_mutex_lock(&philo->data->mu_msg);
    }
    else
    {
        pthread_mutex_lock(&philo->data->mu_msg);
        gettimeofday(&cur_time, NULL);
        printf("%ld %d %s\n",
 	    	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->data->first_time), philo->id, str);
        pthread_mutex_unlock(&philo->data->mu_msg);
    }
    return 0;
}

void    ft_usleep(t_philo *philo, char *str)
{
    struct timeval	cur_time;
    long            time;

    if (ft_strcmp(str, "is eating") == 0)
        time = philo->data->time_to_eat;
    else
        time = philo->data->time_to_sleep;
    gettimeofday(&cur_time, NULL);
    usleep((time - 50) * 1000 );
    while ((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) <= (philo->data->time_usleep + time))
    {
        // usleep(5);
        gettimeofday(&cur_time, NULL);
    }
}

void ft_eat(t_philo *philo)
{
    struct timeval	cur_time;

    pthread_mutex_lock(&philo->data->forks[philo->id]);
    print_msg("has taken a fork", philo);
    pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->nb_philo]);
    print_msg("has taken a fork", philo);
    print_msg("is eating", philo);
    gettimeofday(&cur_time, NULL);
    philo->last_eat = ((cur_time.tv_sec * 1000) + cur_time.tv_usec / 1000);
    philo->data->time_usleep = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    // usleep(philo->data->time_to_eat * 1000);
    ft_usleep(philo, "is eating");
    pthread_mutex_unlock(&philo->data->forks[philo->id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->nb_philo]);
    print_msg("is sleeping", philo);
    gettimeofday(&cur_time, NULL);
    philo->data->time_usleep = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    ft_usleep(philo, "is sleeping");
    // usleep(philo->data->time_to_sleep * 1000);
}
