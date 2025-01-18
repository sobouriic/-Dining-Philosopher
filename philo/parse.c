/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouric <sobouric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 05:44:57 by sobouric          #+#    #+#             */
/*   Updated: 2023/07/05 15:44:53 by sobouric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_digits(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] == ' ' || (av[i][j] >= 9 && av[i][j] <= 13))
			j++;
		if (av[i][j] == '+' && !av[i][j])
			return (1);
		if (av[i][j] == '+' && av[i][j])
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
	}
	return (0);
}

int	check_args(int ac, char **av, t_arg *str)
{
	if ((ac != 5 && ac != 6) || check_digits(av, ac))
		return (1);
	str->number_of_philo = ft_atoi(av[1]);
	str->time_to_die = ft_atoi(av[2]);
	str->time_to_eat = ft_atoi(av[3]);
	str->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&(str->eat), NULL);
	pthread_mutex_init(&(str->meal), NULL);
	pthread_mutex_init(&(str->print), NULL);
	str->forks = malloc(sizeof(pthread_mutex_t) * str->number_of_philo);
	if (str->number_of_philo <= 0 || str->time_to_die < 0
		|| str->time_to_eat < 0 || str->time_to_sleep < 0)
		return (1);
	return (0);
}

int	ft_init_arguments(char **av, int ac, t_arg *str, t_philo *philo)
{
	int	i;

	if (check_args(ac, av, str))
		return (1);
	i = -1;
	while (++i < str->number_of_philo)
	{
		if (ac == 6)
		{
			philo[i].eat_num = ft_atoi(av[5]);
			if (philo->eat_num <= 0)
				return (1);
		}
		else
			philo[i].eat_num = -1;
		philo[i].id = i + 1;
		philo[i].last_time_eat = get_time();
		pthread_mutex_init(&str->forks[i], NULL);
		philo[i].arg = str;
		philo[i].end = 0;
	}
	str->start = get_time();
	return (0);
}
