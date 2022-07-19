/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:18:03 by iouazzan          #+#    #+#             */
/*   Updated: 2022/07/18 18:30:06 by iouazzan         ###   ########.fr       */
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
	
	t_philo *philo = (t_philo *)ph;
	

}

int main(int arc, char *arv[])
{
	// coming SEGV: to be discussed
	t_philo		philo;
	pthread_t	th;
	struct timeval current_time;

	philo.time_of_day = gettimeofday(&current_time, NULL);
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
	philo.i = 0;
	while (philo.i < philo.nb_forks)
	{
		if (pthread_create(&th, NULL, &thread, &philo) != 0)
			return 2;
		philo.i++;
	}
	philo.i = 0;
	while (philo.i < philo.nb_forks)
	{
		if (pthread_join(&th, NULL) != 0)
			return 3;
		philo.i++;
	}
	if (arc == 5)
	{
		philo.nb_philo_eat= atoi(arv[5]);

	}

}