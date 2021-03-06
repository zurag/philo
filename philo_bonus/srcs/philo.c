/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:59:11 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 18:59:53 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h" 

static int	eating(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%ld %d has taken a fork\n", \
	ft_time() - philo->start_time, philo->id);
	sem_post(philo->print);
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%ld %d has taken a fork\n", \
	ft_time() - philo->start_time, philo->id);
	sem_post(philo->print);
	philo->start_eat = ft_time();
	sem_wait(philo->print);
	printf("%ld %d is eating\n", \
	philo->start_eat - philo->start_time, philo->id);
	sem_post(philo->print);
	ft_usleep(philo->time_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is sleeping\n", ft_time() - philo->start_time, philo->id);
	sem_post(philo->print);
	ft_usleep(philo->time_sleep);
	return (0);
}

static int	thinking(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is thinking\n", ft_time() - philo->start_time, philo->id);
	sem_post(philo->print);
	return (0);
}

void	ft_philo(t_philo *philo)
{
	int	i;

	i = 0;
	philo->start_time = ft_time();
	philo->start_eat = philo->start_time;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->max_eat != -1)
			philo->max_eat--;
	}
}
