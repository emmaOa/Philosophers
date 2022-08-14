/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:12:21 by iouazzan          #+#    #+#             */
/*   Updated: 2022/08/08 18:12:26 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	arg_6(int arc, char *arv[], t_global *data)
{
	data->arg_5 = ft_atoi(arv[arc - 1]);
	data->nb_philo = ft_atoi(arv[1]);
	data->nb_forks = data->nb_philo;
	data->min_eat = data->nb_philo;
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	data->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	ft_philo(data);
}

void	arg_5(char *arv[], t_global *data)
{
	data->arg_5 = -1;
	data->min_eat = -1;
	data->nb_philo = ft_atoi(arv[1]);
	data->nb_forks = data->nb_philo;
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	data->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	ft_philo(data);
}
