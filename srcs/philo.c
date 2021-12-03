#include "../includes/philo.h"

static int take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	pthread_mutex_lock(philo->print);
	printf("%ld %d has taken a fork\n", ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	return (0);
}

static int take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[1]);
	pthread_mutex_lock(philo->print);
	printf("%ld %d has taken a fork\n", ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
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
	philo->start_eat = ft_time();
	pthread_mutex_unlock(philo->time);
	pthread_mutex_lock(philo->print);
	printf("%ld %d is eating\n", philo->start_eat - philo->start_time, philo->id);

	pthread_mutex_unlock(philo->print);
	
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%ld %d is sleeping\n", ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_sleep);
	return (0);
}

static int	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%ld %d is thinking\n", ft_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print);
	return (0);
}

void	*philo(void *arg)
{
	int	i;

	i = 0;
	t_philo *philo = (t_philo *)arg;
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
	return (NULL);
}
