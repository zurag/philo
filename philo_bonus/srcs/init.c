/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:55:34 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 20:31:54 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_init_philo(int argc, char **argv, t_philo *philo)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	philo->philo_count = ft_atoi(argv[1]);
	if (argc == 6)
		philo->max_eat = ft_atoi(argv[5]);
	else
		philo->max_eat = -1;
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->philo_count);
	sem_unlink("forks");
	philo->print = sem_open("print", O_CREAT, 0644, 1u);
	sem_unlink("print");
	philo->end = sem_open("end", O_CREAT, 0644, 1u);
	sem_unlink("end");
	sem_wait(philo->end);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	return (0);
}
