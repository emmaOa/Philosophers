#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	struct	timeval tv;
	pthread_mutex_lock(&philo->mutex);
	printf("%ld %d has taken a fork",
		((tv.tv_sec / 1000) + (tv.tv_usec * 1000)), philo->id_philo);
	philo->forks[philo->id_philo] = 1;
	philo->forks[philo->id_philo + 1] = 1;
	printf("%ld %d is eating",
		((tv.tv_sec / 1000) + (tv.tv_usec * 1000)), philo->id_philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
	philo->time_to_die -= philo->time_to_eat;
	philo->forks[philo->id_philo] = 0;
	philo->forks[philo->id_philo + 1] = 0;
}

void	ft_thenck(t_philo *philo)
{
	struct	timeval tv;
	printf("%ld %d is thinking",
	((tv.tv_sec / 1000) + (tv.tv_usec * 1000)), philo->id_philo);
	while (1)
	{
		philo->time_to_live = ((tv.tv_sec / 1000) + tv.tv_usec) - philo->time_of_day;
		if (philo->time_to_live == philo->time_to_die
			|| (philo->forks[philo->id_philo] == 0
			&& philo->forks[philo->id_philo + 1] == 0))
			break;
	}
}