/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:41:32 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 20:33:45 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_philo(t_philo *philo, t_table *table, char **argv, int id)
{
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->max_eat = table->max_eat;
	philo->philo_count = table->philo_count;
	philo->id = id + 1;
	philo->print = table->print;
	philo->time = table->time;
	philo->forks[0] = &table->forks[id];
	philo->forks[1] = &table->forks[(id + 1) % table->philo_count];
}

static int	ft_init_mut(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return (1);
	table->print = malloc(sizeof(pthread_mutex_t));
	if (!table->print)
		return (1);
	table->time = malloc(sizeof(pthread_mutex_t));
	if (!table->time)
		return (1);
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(table->print, NULL);
	pthread_mutex_init(table->time, NULL);
	return (0);
}

int	ft_init_table(int argc, char **argv, t_table *table)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	table->philo_count = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philo)
		return (1);
	if (argc == 6)
		table->max_eat = ft_atoi(argv[5]);
	else
		table->max_eat = -1;
	if (ft_init_mut(table))
		return (1);
	while (i < table->philo_count)
	{
		ft_init_philo(&table->philo[i], table, argv, i);
		i++;
	}
	table->philo_th = malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->philo_th)
		return (1);
	return (0);
}
