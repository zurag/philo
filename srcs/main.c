#include "../includes/philo.h"


void	ft_init_philo(t_philo *philo, t_table *table, char **argv, int id)
{

	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->max_eat = table->max_eat;
	philo->philo_count = table->philo_count;
	philo->id = id + 1;
	philo->print = &table->print;
	philo->take_fork = &table->take_fork;
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
	{	
		table->max_eat = ft_atoi(argv[5]);
		if (table->max_eat == 0)
			return (0);
	}
	else
		table->max_eat = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->take_fork, NULL);
	while (i < table->philo_count)
	{
		ft_init_philo(&table->philo[i], table, argv, i);
		i++;
	}
	return (1);
}

// 1 2 3 4 5 6   lock 1 2 4 6
// 1 2 3 4 5 6 7 lock 1 2 4 5 7

void	*print_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	if (philo->id == 1 || philo->id % 2 == 0 || philo->id == philo->philo_count)
		pthread_mutex_lock(philo->take_fork);

	pthread_mutex_lock(philo->forks[0]);
	printf("Philo %d take left fork\n", philo->id);
	pthread_mutex_lock(philo->forks[1]);
	printf("Philo %d take right fork\n", philo->id);
	
	usleep(philo->time_eat * 1000);
	printf("Philo %d sleep\n", philo->id);

	if (philo->id == 1 || philo->id % 2 == 0 || philo->id == philo->philo_count)
		pthread_mutex_unlock(philo->take_fork);
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	return (NULL);
}

int main(int argc, char **argv)
{
	int		i;
	pthread_t *philo_th;
	t_table	table;

	i = 0;
	if (!ft_init_table(argc, argv, &table))
	{
		write(2, "invalid value\n", 15);
		return (1);
	}
	philo_th = malloc(sizeof(pthread_t) * table.philo_count);
	while (i < table.philo_count)
	{
		pthread_create(&philo_th[i], NULL, print_philo, &table.philo[i]);
		i++;
	}
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(philo_th[i], NULL);
		i++;
	}
	return (0);
}