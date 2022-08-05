/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:18:03 by iouazzan          #+#    #+#             */
/*   Updated: 2022/07/19 13:15:01 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *thread(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		ft_eat(philo);
		print_msg("is thinking", philo);
	}
}

int	ft_philo(t_global *data)
{
	struct timeval	cur_time;
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mu_msg, NULL);
	i = 0;
	gettimeofday(&cur_time, NULL);
	data->first_time = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].th, NULL, &thread, &data->philos[i]) != 0)
			return 0;
		gettimeofday(&cur_time, NULL);
		data->philos->last_eat = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
		usleep(100);
		i++;
	}
	while (1)
	{
		while (i < data->nb_philo)
		{
			gettimeofday(&cur_time, NULL);
			if (data->arg_5 > 0)
			{
				if ((((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) -
				data->philos->last_eat) > data->time_to_die) || data->min_eat == 0)
				{
					printf(" /////min eat : %d\n", data->min_eat);
					return 1;
				}
			}
			else
				if ((((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) -
					data->philos->last_eat) > data->time_to_die))
				{
					print_msg("died", data->philos);
					return 1;
				}
			i++;
		}
		i = 0;
	}
}

int main(int arc, char *arv[])
{
	(void)arc;
	// red flag: SEGV
	t_global		data;
	
	if (arc == 6)
	{

		data.arg_5 = atoi(arv[arc-1]);
		data.nb_philo = atoi(arv[1]);
		data.nb_forks = data.nb_philo;
		data.min_eat = data.nb_philo;
		data.time_to_die = atoi(arv[2]);
		data.time_to_eat = atoi(arv[3]);
		data.time_to_sleep = atoi(arv[4]);
		data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nb_philo);
		data.philos = (t_philo *)malloc(sizeof(t_philo) * data.nb_philo);
		ft_philo(&data);
		printf("---teest philo--main--\n");
		int i = 0;
    	while (i < data.nb_philo)
    	{
    	        if(pthread_detach(data.philos[i].th) != 0)
    	            return 1;
			i++;
    	}
	}
	else if (arc == 5)
	{
		data.arg_5 = -1;
		data.min_eat = -1;
		data.nb_philo = atoi(arv[1]);
		data.nb_forks = data.nb_philo;
		data.time_to_die = atoi(arv[2]);
		data.time_to_eat = atoi(arv[3]);
		data.time_to_sleep = atoi(arv[4]);
		data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nb_philo);
		data.philos = (t_philo *)malloc(sizeof(t_philo) * data.nb_philo);
		ft_philo(&data);
		printf("---teest philo--main--\n");
		int i = 0;
    	while (i < data.nb_philo)
    	{
    	        if(pthread_detach(data.philos[i].th) != 0)
    	            return 1;
			i++;
    	}
	}
	else
		printf("NB argumentsnot valide\n");
	return (0);
}