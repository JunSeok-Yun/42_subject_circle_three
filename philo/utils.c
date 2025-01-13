/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:26:44 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 16:11:01 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo_vals(t_philo_vals *vals, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_exception("input argument count is wrong!!\n"));
	vals->num_of_philo = ft_atoi(argv[1]);
	vals->time_to_die = ft_atoi(argv[2]);
	vals->time_to_eat = ft_atoi(argv[3]);
	vals->time_to_sleep = ft_atoi(argv[4]);
	if (vals->num_of_philo < 1 || vals->time_to_die < 1 || \
			vals->time_to_eat < 1 || vals->time_to_sleep < 1)
		return (error_exception("input value is wrong!!\n"));
	if (argc == 6)
	{
		vals->num_of_must_eat = ft_atoi(argv[5]);
		if (vals->num_of_must_eat < 1)
			return (error_exception("input value is wrong!!\n"));
	}
	else
		vals->num_of_must_eat = -1;
	vals->end_flag = 0;
	vals->check_eat_cnt = 0;
	return (0);
}

int	set_philo_info(t_philo_vals *vals)
{
	int	i;

	i = 0;
	vals->philosopers = malloc(sizeof(t_philo_info) * vals->num_of_philo);
	vals->forks = malloc(sizeof(pthread_mutex_t) * vals->num_of_philo);
	vals->start = get_curtime();
	if (!(vals->philosopers) || !(vals->forks))
		return (error_exception("create_philo_info function is fail !!\n"));
	while (i < vals->num_of_philo)
	{
		vals->philosopers[i].tid = i + 1;
		vals->philosopers[i].left_f = i;
		vals->philosopers[i].right_f = (i + 1) % vals->num_of_philo;
		vals->philosopers[i].cnt_eat = 0;
		vals->philosopers[i].eat_time = vals->start;
		vals->philosopers[i].philo_vals = vals;
		i++;
	}
	return (0);
}

int	set_philo_mutex(t_philo_vals *vals)
{
	int	i;

	i = 0;
	while (i < vals->num_of_philo)
	{
		if (pthread_mutex_init(&vals->forks[i], NULL))
			return (error_exception("forks mutex init fail !!\n"));
		i++;
	}
	if (pthread_mutex_init(&vals->print_status, NULL))
		return (error_exception("print_status mutex init fail !!\n"));
	if (pthread_mutex_init(&vals->eat, NULL))
		return (error_exception("eat mutex init fail !!\n"));
	if (pthread_mutex_init(&vals->died, NULL))
		return (error_exception("died mutex init fail !!\n"));
	return (0);
}

int	create_philosophers(t_philo_vals *vals)
{
	int	i;

	i = 0;
	if (vals->num_of_philo == 1)
	{
		print_philo_status(&vals->philosopers[i], "has taken a fork");
		pass_time(&vals->philosopers[i], vals->time_to_die);
		print_philo_status(&vals->philosopers[i], "died");
		check_flag(&vals->philosopers[i], 1);
		return (0);
	}
	while (i < vals->num_of_philo)
	{
		if (pthread_create(&vals->philosopers[i].pthread, NULL, func_philo, \
					&(vals->philosopers[i])))
			return (error_exception("create functions is wrong!!\n"));
		i++;
	}
	return (0);
}
