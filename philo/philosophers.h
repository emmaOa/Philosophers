/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:17:55 by iouazzan          #+#    #+#             */
/*   Updated: 2022/07/19 13:03:01 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PILOSOPHERS_H
# define PILOSOPHERS_H
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct t_philo
{
	int		nb_philo;
	int		nb_forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_philo_eat;
	int		i;
	int		time_of_day;
	int		*forks;
	int		id_philo;
	int		time_to_live;
	pthread_mutex_t mutex;
}	t_philo;

// static	int	check(size_t sign);
int		ft_atoi(const char *str);
void	ft_eat(t_philo *philo);
void	ft_thenck(t_philo *philo);
#endif