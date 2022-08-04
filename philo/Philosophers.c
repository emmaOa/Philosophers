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
		// time to thinking :(
		ft_eat(philo);
		printf("*****is thimking*****\n");
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
		data->philos[i].id = i;
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
			if ((((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000)) -
				data->philos->last_eat) >= data->time_to_die)
			{
				print_msg("died", data->philos);
				// printf("++++++++++++%ld\n", (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000) - data->philos->last_eat);
				// // printf("++++////++++%ld\n", data->philos->last_eat);
				// printf("++++\\\\+++%ld\n", data->time_to_die);
				// printf("id philo %d\n", data->philos->id);

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
	
	data.nb_philo = atoi(arv[1]);
	data.nb_forks = data.nb_philo;
	data.time_to_die = atoi(arv[2]);
	data.time_to_eat = atoi(arv[3]);
	data.time_to_sleep = atoi(arv[4]);
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	data.philos = (t_philo *)malloc(sizeof(t_philo) * data.nb_philo);
	while(1)
	{
		if (ft_philo(&data) == 1)
		{
			printf("---teest philo--main--\n");
			return 3;
		}
		
	}
	return (0);
}