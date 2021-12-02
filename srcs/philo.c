#include "../includes/philo.h"

static int take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	// pthread_mutex_lock(philo->print);
	gettimeofday(&philo->c_time, NULL);
	printf("%ld %d has taken a fork\n", philo->c_time.tv_sec * 1000 + (philo->c_time.tv_usec / 1000), philo->id);
	// pthread_mutex_unlock(philo->print);
	return (0);
}

static int take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[1]);
	// pthread_mutex_lock(philo->print);
	gettimeofday(&philo->c_time, NULL);
	printf("%ld %d has taken a fork\n", philo->c_time.tv_sec * 1000 + (philo->c_time.tv_usec / 1000), philo->id);
	// pthread_mutex_unlock(philo->print);
	return (0);
}

static int	eating(t_philo *philo)
{
	
	if (philo->id % 2)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);	
		take_left_fork(philo);
	}
	pthread_mutex_lock(philo->time);
	gettimeofday(&philo->start_eat, NULL);
	// pthread_mutex_lock(philo->print);
	printf("%ld %d is eating\n", philo->start_eat.tv_sec * 1000 + (philo->start_eat.tv_usec / 1000), philo->id);
	if (philo->start_eat.tv_usec + philo->time_eat * 1000 > 1000000)
	{
		philo->start_eat.tv_sec += philo->start_eat.tv_usec + philo->time_eat / 1000000;
		philo->start_eat.tv_usec = philo->start_eat.tv_usec + philo->time_eat % 1000000;
	}
	else
		philo->start_eat.tv_usec += philo->time_eat * 1000;

	// printf("%d time == %ld sec, %d usec\n", philo->id, philo->start_eat.tv_sec, philo->start_eat.tv_usec);
	// pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(philo->time);
	usleep(philo->time_eat * 1000);
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	// pthread_mutex_lock(philo->print);
	gettimeofday(&philo->c_time, NULL);
	printf("%ld %d is sleeping\n", philo->c_time.tv_sec * 1000 + (philo->c_time.tv_usec / 1000), philo->id);
	// pthread_mutex_unlock(philo->print);
	usleep(philo->time_sleep * 1000);
	return (0);
}

static int	thinking(t_philo *philo)
{
	// pthread_mutex_lock(philo->print);
	gettimeofday(&philo->c_time, NULL);
	printf("%ld %d is thinking\n", philo->c_time.tv_sec * 1000 + (philo->c_time.tv_usec / 1000), philo->id);
	// pthread_mutex_unlock(philo->print);
	return (0);
}

void	*philo(void *arg)
{
	int	i;

	i = 0;
	t_philo *philo = (t_philo *)arg;
	gettimeofday(&philo->start_eat, NULL);
	while (!*philo->end)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->max_eat != -1)
			philo->max_eat--;
	}
	return (NULL);
}
