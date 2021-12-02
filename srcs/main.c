#include "../includes/philo.h"

int main(int argc, char **argv)
{
	// struct timeval	time;
	// struct timeval	time_2;
	// (void)argv;
	// (void)argc;




	int		i;
	pthread_t monitoring;
	t_table	table;

	i = 0;
	monitoring = NULL;
	// printf("HERE");
	if (!ft_init_table(argc, argv, &table))
	{
		write(2, "invalid value\n", 15);
		return (1);
	}
	while (i < table.philo_count)
	{
		pthread_create(&table.philo_th[i], NULL, philo, &table.philo[i]);
		i++;
	}
	pthread_create(&monitoring, NULL, ft_monitoring, &table);
	pthread_join(monitoring, NULL);
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_th[i], NULL);
		i++;
	}
	
	// gettimeofday(&time, NULL);
	// printf("time == %ld sec, %d usec\n", time.tv_sec, time.tv_usec);
	// usleep(200);
	// // gettimeofday(&time, NULL);
	// // printf("time == %ld sec, %d usec\n", time.tv_sec, time.tv_usec);
	// gettimeofday(&time_2, NULL);
	// // printf("time in ms =  %ld\n", time.tv_sec * 1000 + (time.tv_usec / 1000));
	// printf("time == %ld sec, %d usec d == %ld\n", time_2.tv_sec, time_2.tv_usec, (time_2.tv_sec - time.tv_sec) * 1000000 + time_2.tv_usec -  time.tv_usec);
	// printf("time in ms =  %ld\n", time_2.tv_sec * 1000 + (time_2.tv_usec / 1000));
	return (0);
}
