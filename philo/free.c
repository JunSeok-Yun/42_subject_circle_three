/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:50:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 15:49:45 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_philo_info(t_philo_vals *vals)
{
	free(vals->forks);
	free(vals->philosopers);
	return (0);
}

int	free_mutex(t_philo_vals *vals)
{
	int	i;

	i = 0;
	while (i < vals->num_of_philo)
	{
		pthread_mutex_destroy(&vals->forks[i]);
		i++;
	}
	free_philo_info(vals);
	pthread_mutex_destroy(&vals->print_status);
	pthread_mutex_destroy(&vals->eat);
	pthread_mutex_destroy(&vals->died);
	return (0);
}

void	monitoring_philos(t_philo_vals *vals)
{
	int	i;
	int	flag;

	flag = 1;
	while (flag)
	{
		i = 0;
		while (i < vals->num_of_philo)
		{
			if (flag && check_died_flag(&vals->philosopers[i]))
				flag = 0;
			i++;
		}
	}
	i = 0;
	while (i < vals->num_of_philo)
	{
		pthread_join(vals->philosopers[i].pthread, NULL);
		i++;
	}
}
