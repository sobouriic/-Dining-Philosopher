/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouric <sobouric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 06:09:35 by sobouric          #+#    #+#             */
/*   Updated: 2023/07/04 01:09:10 by sobouric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	main(int ac, char **av)
{
	t_arg	*arg;
	t_philo	*philo;

	arg = malloc(sizeof(t_arg));
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (ft_init_arguments(av, ac, arg, philo) != 0)
		return (ft_exit("check_argumets!\n"));
	create_threads(philo);
	while (1)
	{
		if (check_death(philo))
			break ;
	}
	return (0);
}
