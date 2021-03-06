/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:58:20 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 18:58:59 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static long	check_end(t_philo *philo)
{
	long	time;

	time = ft_time();
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

void	*ft_monitoring(void *arg)
{
	int				i;
	long			time;
	t_philo			*philo;

	i = 0;
	philo = (t_philo *)arg;
	usleep(3000);
	while (1)
	{
		time = check_end(philo);
		if (time > 0)
		{
			sem_wait(philo->print);
			printf("%ld %d died\n", time - philo->start_time, philo->id);
			sem_post(philo->end);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}
