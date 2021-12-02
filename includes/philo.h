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
	long			time_eat;
	long			time_die;
	long			time_sleep;
	int				max_eat;
	int				philo_count;
	int				*end;
	struct timeval	start_eat;
	struct timeval	c_time;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*print;
	pthread_mutex_t	*time;
}				t_philo;


typedef struct s_table
{
	pthread_t 		*philo_th;
	t_philo			*philo;
	int				max_eat;
	int				end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	*time;
	int				philo_count;
}				t_table;

int     ft_atoi(const char *nptr);
void	ft_init_philo(t_philo *philo, t_table *table, char **argv, int id);
int		ft_init_table(int argc, char **argv, t_table *table);
void	*ft_monitoring(void *arg);
void	*philo(void *arg);

#endif