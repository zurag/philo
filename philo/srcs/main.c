/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:21:09 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 20:34:49 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	int			i;
	pthread_t	monitoring;
	t_table		table;

	i = 0;
	monitoring = NULL;
	if (ft_init_table(argc, argv, &table))
	{
		write(2, "invalid value\n", 15);
		return (1);
	}
	while (i < table.philo_count)
	{
		if (pthread_create(&table.philo_th[i], 0, philo, &table.philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitoring, NULL, ft_monitoring, &table) != 0)
		return (1);
	if (pthread_join(monitoring, NULL) != 0)
		return (1);
	return (0);
}
