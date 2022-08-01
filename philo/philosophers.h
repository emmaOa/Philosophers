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
	pthread_mutex_t *forks;
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*time_creat;
	int				id_philo;
	int				*last_eat;
	long int		first_time;
	int				i;
	pthread_mutex_t	mu_msg;
}	t_philo;

// static	int	check(size_t sign);
int		ft_atoi(const char *str);
void	ft_eat(t_philo *philo);
int		ft_think(t_philo *philo);
void	ft_philo(t_philo *philo);
void	ft_sleep(t_philo *philo);
int     print_msg(char *str, t_philo *philo, int id_philo);
#endif