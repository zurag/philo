#include "../includes/philo.h"


int main(int argc, char **argv)
{

	int		i;
	pthread_t monitoring;
	t_table	table;

	i = 0;
	monitoring = NULL;
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
	return (0);
}
