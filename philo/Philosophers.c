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

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit (1);
}

void *thread(void *ph)
{
	struct	timeval tv;
	t_philo	philo;

	philo = *(t_philo *)ph;
	gettimeofday(&tv, NULL);
	philo.time_of_day = (tv.tv_sec / 1000) + tv.tv_usec;
	while (1)
	{
		if (philo.forks[philo.id_philo] != 0 
			|| philo.forks[philo.id_philo + 1] != 0)
			ft_thenck(&philo);
		else if (philo.forks[philo.id_philo] == 0 
			&& philo.forks[philo.id_philo + 1] == 0)
		{
			ft_eat(&philo);
			printf("%ld %d is sleeping",
				((tv.tv_sec / 1000) + (tv.tv_usec * 1000)), philo.id_philo);
			usleep(philo.time_to_sleep * 1000);
			philo.time_to_die -= philo.time_to_sleep;
		}
		ft_thenck(&philo);
		if (philo.time_to_live == philo.time_to_die)
			break;
	}
	
}

int main(int arc, char *arv[])
{
	// coming SEGV: to be discussed
	t_philo		philo;
	pthread_t	th;
	 
	
	if (arc != 4 && arc != 5)
	{
		printf("nb argument not valide");
		return 1;
	}
	philo.nb_philo = atoi(arv[1]);
	philo.nb_forks = philo.nb_philo;
	philo.time_to_die = atoi(arv[2]);
	philo.time_to_eat = atoi(arv[3]);
	philo.time_to_sleep = atoi(arv[4]);
	pthread_mutex_init(&philo.mutex, NULL);
	philo.i = 0;
	while (philo.i < philo.nb_forks)
	{
		philo.forks[philo.i] = 0;
		philo.i++;
	}
	philo.i = 0;
	while (philo.i < philo.nb_forks)
	{
		philo.id_philo = philo.i;
		if (pthread_create(&th, NULL, &thread, &philo) != 0)
			return 2;
		philo.i++;
	}
	philo.i = 0;
	while (philo.i < philo.nb_forks)
	{
		if (pthread_join(th, NULL) != 0)
			return 3;
		philo.i++;
	}
	if (arc == 5)
	{
		// philo.nb_philo_eat= atoi(arv[5]);
		return 20;
	}
	pthread_mutex_destroy(&philo.mutex);
}