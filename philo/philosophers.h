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

typedef struct s_philo
{
	pthread_t			th;
	long				last_eat;
	int					id;
	int					nb_eat;
	struct  s_global	*data;
	
}				t_philo;

typedef struct s_global
{
	t_philo 		*philos;
	int				nb_philo;
	int				nb_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_usleep;
	int				min_eat;
	int				arg_5;
	pthread_mutex_t	mu_msg;
	long 			first_time;
	pthread_mutex_t *forks;
}	t_global;

int		ft_atoi(const char *str);
void	ft_eat(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_philo(t_global *data);
void	ft_sleep(t_philo *philo);
int     print_msg(char *str, t_philo *philo);
int		ft_strcmp(char *str1, char *str2);
void	ft_usleep(t_philo *philo, char *str);
long    gettime();
#endif