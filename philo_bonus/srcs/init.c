#include "../includes/philo.h"

void	ft_init_philo(t_philo *philo, t_table *table, char **argv, int id)
{

	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->max_eat = table->max_eat;
	philo->philo_count = table->philo_count;
	philo->id = id + 1;
	philo->print = table->print;
	philo->time = table->time;
	philo->forks[0] = &table->forks[id];
	philo->forks[1] = &table->forks[(id + 1) % table->philo_count];
}

int	ft_init_table(int argc, char **argv, t_table *table)
{
	int i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (0);
	table->philo_count = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(t_philo) * table->philo_count);
	if (argc == 6)
		table->max_eat = ft_atoi(argv[5]);
	else
		table->max_eat = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	table->print = malloc (sizeof(pthread_mutex_t));
	table->time = malloc (sizeof(pthread_mutex_t));
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	pthread_mutex_init(table->print, NULL);
	pthread_mutex_init(table->time, NULL);
	while (i < table->philo_count)
	{
		ft_init_philo(&table->philo[i], table, argv, i);
		i++;
	}
	table->philo_th = malloc(sizeof(pthread_t) * table->philo_count);
	return (1);
}
