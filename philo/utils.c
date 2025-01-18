/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouric <sobouric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:26:18 by sobouric          #+#    #+#             */
/*   Updated: 2023/07/04 00:29:06 by sobouric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	timer(time_t time)
{
	time_t	t;

	t = get_time();
	usleep(time * 1000 * 0.9);
	while ((get_time() - t) < time)
		usleep(100);
}

void	print_msg(t_philo *philo, char *str, unsigned long t)
{
	pthread_mutex_lock(&philo->arg->print);
	printf("%ld %d %s", t, philo->id, str);
	pthread_mutex_unlock(&philo->arg->print);
}
