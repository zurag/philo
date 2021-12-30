/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:46:12 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 18:48:21 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	pthread_mutex_lock(philo->print);
	printf("%ld %d has taken a fork\n", \
	ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	return (0);
}

static int	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[1]);
	pthread_mutex_lock(philo->print);
	printf("%ld %d has taken a fork\n", \
	ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	return (0);
}

static int	eating(t_philo *philo)
{
	if (philo->id % 2)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	pthread_mutex_lock(philo->time);
	philo->start_eat = ft_time();
	pthread_mutex_unlock(philo->time);
	pthread_mutex_lock(philo->print);
	printf("%ld %d is eating\n", \
	philo->start_eat - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	return (0);
}

static int	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%ld %d is sleeping\n", ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_sleep);
	pthread_mutex_lock(philo->print);
	printf("%ld %d is thinking\n", ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	return (0);
}

void	*philo(void *arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
	philo->start_time = ft_time();
	philo->start_eat = philo->start_time;
	while (1)
	{
		eating(philo);
		sleep_think(philo);
		if (philo->max_eat != -1)
			philo->max_eat--;
	}
	return (NULL);
}
