/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:23:45 by zurag             #+#    #+#             */
/*   Updated: 2021/12/30 18:24:56 by zurag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_time(void)
{
	struct timeval	cur_time;
	long			res;

	gettimeofday(&cur_time, NULL);
	res = (long)cur_time.tv_sec * 1000 + (long)(cur_time.tv_usec / 1000);
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
