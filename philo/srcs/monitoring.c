/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:21:39 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 20:34:59 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long	check_end(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->time);
	time = ft_time();
	pthread_mutex_unlock(philo->time);
	if (time - philo->start_eat > philo->time_die)
	{
		if (philo->start_eat == 0 && time % 1000 < philo->time_die)
			return (0);
		return (time);
	}
	if (philo->max_eat == 0)
		return (time);
	return (0);
}

static void	kill_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_detach(table->philo_th[i]);
		i++;
	}
}

static void	destroy_mt(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(table->print);
	pthread_mutex_destroy(table->time);
	free(table->philo);
	free(table->forks);
	free(table->time);
	free(table->print);
	free(table->philo_th);
}

void	*ft_monitoring(void *arg)
{
	int				i;
	long			time;
	t_table			*table;

	i = 0;
	table = (t_table *)arg;
	usleep(3000);
	while (1)
	{
		time = check_end(&table->philo[i]);
		if (time > 0)
		{
			pthread_mutex_lock(table->print);
			printf("%ld %d died\n", \
			time - table->philo[i].start_time, table->philo[i].id);
			kill_philo(table);
			destroy_mt(table);
			break ;
		}
		i++;
		if (i == table->philo_count)
			i = 0;
	}
	return (NULL);
}
