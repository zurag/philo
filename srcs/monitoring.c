#include "../includes/philo.h"

static int	check_end(t_philo *philo, struct timeval *time)
{
	pthread_mutex_lock(philo->time);
	gettimeofday(time, NULL);
	pthread_mutex_unlock(philo->time);
	// printf("TIME == %ld\n", ((time->tv_sec - philo->start_eat.tv_sec) * 1000000 + time->tv_usec - philo->start_eat.tv_usec) / 1000);
	if (((time->tv_sec - philo->start_eat.tv_sec) * 1000000 + time->tv_usec - philo->start_eat.tv_usec) / 1000 > philo->time_die)
	{
		return (1);
	}
	if (philo->max_eat == 0)
		return (1);
	return (0);
}

// static void kill_philo(t_table *table)
// {
// 	int i;

// 	i = 0;
// 	while (i < table->philo_count)
// 	{
// 		pthread_detach(table->philo_th[i]);
// 		i++;
// 	}
// }

// static void destroy_mt(t_table *table)
// {
// 	int i;

// 	i = 0;
// 	while (i < table->philo_count)
// 	{
// 		pthread_mutex_destroy(&table->forks[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&table->print);
// 	pthread_mutex_destroy(&table->take_fork);
// }

void		*ft_monitoring(void *arg)
{
	int				i;
	struct timeval	time;

	i = 0;
	t_table *table = (t_table *)arg;
	usleep(1000);
	while (1)
	{
		if (check_end(&table->philo[i], &time))
		{
			table->end = 1;
			pthread_mutex_lock(&table->print);
			printf("%ld %d died\n", time.tv_sec * 1000 + (time.tv_usec / 1000), table->philo[i].id);
			// kill_philo(table);
			// pthread_mutex_unlock(&table->print);
			// destroy_mt(table);
			break ;
		}
		i++;
		if (i == table->philo_count)
			i = 0;
	}
	return (NULL);
}
