/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouric <sobouric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:49:41 by sobouric          #+#    #+#             */
/*   Updated: 2023/07/04 00:36:23 by sobouric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 
# include <unistd.h>
# include <stdbool.h>
# include <time.h> 

typedef struct s_arg
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_philo;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	meal;
	pthread_mutex_t	*forks;
	unsigned long	start;
}	t_arg;

typedef struct s_philo
{
	t_arg		*arg;
	pthread_t	thread;
	int			id;
	int			end;
	int			eat_num;
	long long	last_time_eat;
}	t_philo;
int		ft_atoi(char *str);
int		check_digits(char **av, int ac);
int		check_args(int ac, char **av, t_arg *str);
int		ft_init_arguments(char **av, int ac, t_arg *str, t_philo *philo);
int		ft_exit(char *str);
void	ft_putstr_fd(char *s, int fd);
void	philosopher(t_philo *philo);
void	create_threads(t_philo *philo);
void	timer(time_t time);
time_t	get_time(void);
void	print_msg(t_philo *philo, char *str, unsigned long t);
int		check_death(t_philo *philo);
void	*routine(void *str);
#endif