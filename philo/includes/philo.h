/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:16:29 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 18:17:57 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<pthread.h>
# include	<sys/time.h>
# include	<string.h>

typedef struct s_philo{
	int				id;
	long			time_eat;
	long			time_die;
	long			time_sleep;
	int				max_eat;
	int				philo_count;
	long			start_time;
	long			start_eat;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*print;
	pthread_mutex_t	*time;
}				t_philo;

typedef struct s_table
{
	pthread_t		*philo_th;
	t_philo			*philo;
	int				max_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*time;
	int				philo_count;
}				t_table;

int		ft_atoi(const char *nptr);
void	ft_init_philo(t_philo *philo, t_table *table, char **argv, int id);
int		ft_init_table(int argc, char **argv, t_table *table);
void	*ft_monitoring(void *arg);
void	*philo(void *arg);
long	ft_time(void);
void	ft_usleep(int time_ms);

#endif