#include "../includes/philo.h"

long	ft_time()
{
	struct timeval	current_time;
	long		 	res;
	
	gettimeofday(&current_time, NULL);
	res = (long)current_time.tv_sec * 1000 + (long)(current_time.tv_usec / 1000);
	return (res);
}


void	ft_usleep(int time_ms)
{
	long	time;

	time = ft_time();
	usleep(time_ms * 900);
	while (ft_time() < time + time_ms)
		usleep(time_ms * 3);
}
