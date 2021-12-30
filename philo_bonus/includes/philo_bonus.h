/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:53:56 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 19:31:15 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define FORK_ERROR 2
# define MALLOC_ERROR 3
# define PTHREAD_ERROR 4

typedef struct s_philo{
	int				id;
	long			time_eat;
	long			time_die;
	long			time_sleep;
	int				max_eat;
	int				philo_count;
	long			start_time;
	long			start_eat;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*end;
}				t_philo;

int		ft_atoi(const char *nptr);
int		ft_init_philo(int argc, char **argv, t_philo *philo);
void	*ft_monitoring(void *arg);
void	ft_philo(t_philo *philo);
long	ft_time(void);
void	ft_usleep(int time_ms);

#endif