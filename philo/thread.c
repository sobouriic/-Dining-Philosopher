/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouric <sobouric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:39 by sobouric          #+#    #+#             */
/*   Updated: 2023/07/06 21:11:07 by sobouric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks[philo->id - 1]);
	print_msg(philo, "has taken a fork\n", get_time() - philo->arg->start);
	pthread_mutex_lock(&philo->arg->forks[philo->id
		% philo->arg->number_of_philo]);
	print_msg(philo, "has taken a fork\n", get_time() - philo->arg->start);
	print_msg(philo, "is eating\n", get_time() - philo->arg->start);
	timer(philo->arg->time_to_eat);
	pthread_mutex_lock(&philo->arg->eat);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->arg->eat);
	pthread_mutex_lock(&philo->arg->meal);
	philo->eat_num--;
	pthread_mutex_unlock(&philo->arg->meal);
	pthread_mutex_unlock(&philo->arg->forks[philo->id
		% philo->arg->number_of_philo]);
	pthread_mutex_unlock(&philo->arg->forks[philo->id - 1]);
	print_msg(philo, "is sleeping\n", get_time() - philo->arg->start);
	timer(philo->arg->time_to_sleep);
	print_msg(philo, "is thinking\n", get_time() - philo->arg->start);
}

void	*routine(void *str)
{
	t_philo	*philo;

	philo = (t_philo *)str;
	while (1)
	{
		pthread_mutex_lock(&philo->arg->meal);
		if (philo->eat_num == 0)
		{
			philo->end = 1;
			pthread_mutex_unlock(&philo->arg->meal);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->meal);
		philosopher(philo);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	int				i;
	int				nb_meals;
	unsigned long	last;

	nb_meals = 0;
	i = -1;
	while (++i < philo[0].arg->number_of_philo)
	{
		pthread_mutex_lock(&philo->arg->meal);
		if (philo[i].end == 1)
				nb_meals++;
		pthread_mutex_unlock(&philo->arg->meal);
		pthread_mutex_lock(&philo->arg->eat);
		last = philo[i].last_time_eat;
		if (get_time() - last >= (unsigned long)philo[i].arg->time_to_die)
			return (pthread_mutex_lock(&philo->arg->print),
				printf("%ld %d %s", get_time() - philo[i].arg->start,
					philo->id, "is dead\n"));
		pthread_mutex_unlock(&philo->arg->eat);
	}
	if (nb_meals == philo->arg->number_of_philo)
		return (1);
	return (0);
}

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].arg->number_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&routine, (void *) &philo[i]) != 0)
		{
			ft_exit("failed to create thread\n");
			return ;
		}
		pthread_detach(philo[i].thread);
		i++;
		usleep(50);
	}
}
