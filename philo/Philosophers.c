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

void	*thread(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		ft_eat(philo);
		print_msg("is thinking", philo);
	}
}

void	ft_philo(t_global *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->mu_msg, NULL);
	pthread_mutex_init(&data->mu_last_est, NULL);
	pthread_mutex_init(&data->mu_min_eat, NULL);
	i = 0;
	data->first_time = gettime();
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		data->philos[i].data = data;
		if (pthread_create
			(&data->philos[i].th, NULL, &thread, &data->philos[i]) != 0)
			return ;
		pthread_mutex_lock(&data->mu_last_est);
		data->philos->last_eat = gettime();
		pthread_mutex_unlock(&data->mu_last_est);
		usleep(100);
		i++;
	}
	whait_thraeds(data);
}

int	stop_threads(t_global *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->mu_last_est);
		if (data->arg_5 > 0)
		{
			pthread_mutex_lock(&data->mu_min_eat);
			if (((gettime() - data->philos->last_eat) > data->time_to_die)
				|| data->min_eat == 0)
				return (1);
			pthread_mutex_unlock(&data->mu_min_eat);
		}
		else
		{
			if (((gettime() - data->philos->last_eat) > data->time_to_die))
			{
				print_msg("died", data->philos);
				return (1);
			}
		}
		pthread_mutex_unlock(&data->mu_last_est);
	}
	return (0);
}

void	whait_thraeds(t_global *data)
{
	while (1)
	{
		if (stop_threads(data) == 1)
			return ;
	}
}

int	main(int arc, char *arv[])
{
	t_global		*data;

	data = malloc(sizeof(t_global));
	if (check_arg(arv, arc) == 0)
	{
		if (atoi(arv[1]) == 0)
			return (0);
		if (arc == 6)
		{
			arg_6(arc, arv, data);
			return (0);
		}
		else if (arc == 5)
			arg_5(arv, data);
		else
			printf("NB arguments not valide\n");
	}
	else
		printf("arguments not valide\n");
	return (0);
}
