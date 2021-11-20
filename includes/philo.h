#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_philo{
	int				id;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				max_eat;
	int				philo_count;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*print;
	pthread_mutex_t	*take_fork;
}				t_philo;


typedef struct s_table
{
	t_philo			*philo;
	int				max_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	take_fork;
	int				philo_count;
}				t_table;



int     ft_atoi(const char *nptr);

#endif