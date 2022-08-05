#include "philosophers.h"

int     print_msg(char *str, t_philo *philo)
{
    struct timeval	cur_time;

    if (philo->data->arg_5 != -1)
    {
        if (ft_strcmp("is eating", str) != 0 && philo->data->min_eat == 0)
            {
                pthread_mutex_lock(&philo->data->mu_msg);
                gettimeofday(&cur_time, NULL);
                printf("%ld %d %s\n",
 	            	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->data->first_time), philo->id, str);
            }
        else
                pthread_mutex_lock(&philo->data->mu_msg);
                gettimeofday(&cur_time, NULL);
                printf("%ld %d %s\n",
 	            	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->data->first_time), philo->id, str);
                pthread_mutex_unlock(&philo->data->mu_msg);
    }
    else
        if (ft_strcmp("died", str) == 0)
        {
            pthread_mutex_lock(&philo->data->mu_msg);
            gettimeofday(&cur_time, NULL);
            printf("%ld %d %s\n",
 	        	((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - philo->data->first_time), philo->id, str);
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
    long            time;

    if (ft_strcmp(str, "is eating") == 0) 
        time = philo->data->time_to_eat;
    else
        time = philo->data->time_to_sleep;
    usleep(time * 900);
    while (gettime() < (philo->data->time_usleep + time))
        usleep(10);
}

void ft_eat(t_philo *philo)
{
    struct timeval	cur_time;

    pthread_mutex_lock(&philo->data->forks[philo->id] - 1);
    print_msg("has taken a fork", philo);
    pthread_mutex_lock(&philo->data->forks[(philo->id % philo->data->nb_philo)]);
    print_msg("has taken a fork", philo);
    print_msg("is eating", philo);
    gettimeofday(&cur_time, NULL);
    philo->last_eat = ((cur_time.tv_sec * 1000) + cur_time.tv_usec / 1000);
    philo->data->time_usleep = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    philo->nb_eat++;
    if (philo->nb_eat == philo->data->arg_5)
        philo->data->min_eat--;
    ft_usleep(philo, "is eating");
    print_msg("is sleeping", philo);
    pthread_mutex_unlock(&philo->data->forks[philo->id] - 1);
    pthread_mutex_unlock(&philo->data->forks[(philo->id % philo->data->nb_philo)]);
    gettimeofday(&cur_time, NULL);
    philo->data->time_usleep = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
    ft_usleep(philo, "is sleeping");
}
