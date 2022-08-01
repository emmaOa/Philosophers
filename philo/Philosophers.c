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
	struct timeval	cur_time;
	t_philo	*philo;

	philo = (t_philo *)ph;
    gettimeofday(&cur_time, NULL);
	while (1)
	{
		// time to thinking :(
		ft_eat(philo);
		print_msg("is thinking", philo, philo->id_philo);
	}
}

void ft_philo(t_philo *philo)
{
	struct timeval	cur_time;
	pthread_t		th[philo->nb_philo];
	int 			*rt;
	int i;

	rt = 0;
	philo->i = 0;
	i = 0;
	gettimeofday(&cur_time, NULL);
	while (philo->i < philo->nb_philo)
	{
		pthread_mutex_init(&philo->forks[philo->i], NULL);
		philo->i++;
	}
	pthread_mutex_init(&philo->mu_msg, NULL);
	philo->i = 0;
	philo->first_time = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
	while (philo->i < philo->nb_philo)
	{
		philo->id_philo = philo->i;
		if (pthread_create(&th[i], NULL, &thread, philo) != 0)
			return ;
		philo->time_creat[philo->id_philo] = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
		usleep(10);
		philo->i++;
	}
	while (1)
	{
		while (i < philo->nb_philo)
		{
			if (((((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000)) -
				philo->last_eat[philo->id_philo]) <= philo->time_to_die) ||
				((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000)) -
				philo->time_creat[philo->id_philo] <= philo->time_to_die)
			{
				print_msg("is die", philo, philo->id_philo);
				printf("----%ld\n", philo->first_time);
				printf("****%ld\n", (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
				printf("....%d\n", philo->time_to_die);
				philo->i = 0;
				while (philo->i < philo->nb_philo)
				{
					pthread_mutex_destroy(&philo->forks[philo->i]);
					philo->i++;
				}
				pthread_mutex_destroy(&philo->mu_msg);
				printf("---teest philo----\n");
				return ;
			}
			i++;
		}
		i = 0;
	}


}

int main(int arc, char *arv[])
{
	(void)arc;
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	
	philo->nb_philo = atoi(arv[1]);
	philo->nb_forks = philo->nb_philo;
	philo->time_to_die = atoi(arv[2]);
	philo->time_to_eat = atoi(arv[3]);
	philo->time_to_sleep = atoi(arv[4]);
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	philo->last_eat = (int *)malloc(sizeof(int) * philo->nb_philo);
	philo->time_creat = (int *)malloc(sizeof(int) * philo->nb_philo);
	ft_philo(philo);
	printf("---teest philo--main--\n");
	return (0);
}