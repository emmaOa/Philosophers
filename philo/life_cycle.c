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
        return 0;
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

long    gettime()
{
    struct timeval	cur_time;
    long    time ;

    gettimeofday(&cur_time, NULL);
    time = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    return time;
}

void    ft_usleep(t_philo *philo, char *str)
{
    // struct timeval	cur_time;
    long            time;

    if (ft_strcmp(str, "is eating") == 0) 
        time = philo->data->time_to_eat;
    else
        time = philo->data->time_to_sleep;
    // gettimeofday(&cur_time, NULL);
    usleep(time * 800);
    while (gettime() < (philo->data->time_usleep + time))
    {
        // usleep(5);
        usleep(100);
        gettime();
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
    // printf("///////last eat %ld %d\n", philo->last_eat, philo->id);
    philo->data->time_usleep = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    // usleep(philo->data->time_to_eat * 1000);
    ft_usleep(philo, "is eating");
    pthread_mutex_unlock(&philo->data->forks[philo->id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->nb_philo]);
    print_msg("is sleeping", philo);
    gettimeofday(&cur_time, NULL);
    philo->data->time_usleep = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    ft_usleep(philo, "is sleeping");
    // printf("finaaaaaaaal\n");
    // usleep(philo->data->time_to_sleep * 1000);
}
