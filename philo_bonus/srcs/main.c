/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:55:51 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 20:27:13 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_process(t_philo *philo)
{
	pthread_t	monitoring;

	if (pthread_create(&monitoring, NULL, ft_monitoring, philo) != 0)
	{
		sem_wait(philo->print);
		sem_post(philo->end);
		exit(PTHREAD_ERROR);
	}
	ft_philo(philo);
	if (pthread_join(monitoring, NULL) != 0)
	{
		sem_wait(philo->print);
		sem_post(philo->end);
		exit(PTHREAD_ERROR);
	}
	exit(EXIT_SUCCESS);
}

void	kill_philo(pid_t *id, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		kill(id[i], SIGKILL);
		i++;
	}
}

static void	start_philo(pid_t *id, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->philo_count)
	{
		philo->id = i + 1;
		id[i] = fork();
		if (id[i] == 0)
			ft_process(philo);
		else if (id[i] == -1)
		{
			while (i >= 0)
			{
				kill(id[i], SIGKILL);
				i--;
			}
			write(2, "Fork error\n", 12);
			exit(FORK_ERROR);
		}
		i++;
	}
}

static void	ft_close_sem(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->print);
	sem_close(philo->end);
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	*id;
	t_philo	philo;

	i = 0;
	if (ft_init_philo(argc, argv, &philo))
	{
		write(2, "invalid value\n", 15);
		return (1);
	}
	id = malloc(philo.philo_count);
	if (!id)
		exit (MALLOC_ERROR);
	start_philo(id, &philo);
	sem_wait(philo.end);
	kill_philo(id, &philo);
	ft_close_sem(&philo);
	free(id);
	return (0);
}
