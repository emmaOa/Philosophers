/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:23 by iouazzan          #+#    #+#             */
/*   Updated: 2022/08/08 17:33:30 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_msg(char *str, t_philo *philo)
{
	struct timeval	cur_time;

	if (ft_strcmp("died", str) == 0)
	{
		pthread_mutex_lock(&philo->data->mu_msg);
		gettimeofday(&cur_time, NULL);
		printf("%ld %d %s\n", (gettime() - philo->data->first_time),
			philo->id, str);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mu_msg);
		gettimeofday(&cur_time, NULL);
		printf("%ld %d %s\n", (gettime() - philo->data->first_time),
			philo->id, str);
		pthread_mutex_unlock(&philo->data->mu_msg);
	}
	return (0);
}

int	check_arg(char *arv[], int arc)
{
	int	i;
	int	j;

	i = 1;
	while (i < arc)
	{
		j = 0;
		while (arv[i][j])
		{
			if (arv[i][j] > '9' || arv[i][j] < '0')
				return (1);
			j++;
		}
		if (ft_atoi(arv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

long	gettime(void)
{
	struct timeval	cur_time;
	long			time;

	gettimeofday(&cur_time, NULL);
	time = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(t_philo *philo, char *str, long now)
{
	long	time;

	if (ft_strcmp(str, "is eating") == 0)
		time = philo->data->time_to_eat;
	else
		time = philo->data->time_to_sleep;
	usleep(time * 800);
	while (gettime() < (now + time))
		usleep(10);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id] - 1);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->data->forks
	[(philo->id % philo->data->nb_philo)]);
	print_msg("has taken a fork", philo);
	print_msg("is eating", philo);
	philo->nb_eat++;
	if (philo->nb_eat >= philo->data->arg_5)
	{
		pthread_mutex_lock(&philo->data->mu_min_eat);
		philo->data->min_eat--;
		pthread_mutex_unlock(&philo->data->mu_min_eat);
	}
	pthread_mutex_lock(&philo->data->mu_last_est);
	philo->last_eat = gettime();
	pthread_mutex_unlock(&philo->data->mu_last_est);
	ft_usleep(philo, "is eating", gettime());
	print_msg("is sleeping", philo);
	pthread_mutex_unlock(&philo->data->forks[philo->id] - 1);
	pthread_mutex_unlock(&philo->data->forks
	[(philo->id % philo->data->nb_philo)]);
	ft_usleep(philo, "is sleeping", gettime());
}
