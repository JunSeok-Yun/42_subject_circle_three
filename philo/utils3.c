/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:47:06 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 16:17:07 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo_info *info)
{
	if (info->tid % 2 == 0)
		take_left_right_fork(info);
	else
		take_right_left_fork(info);
}

int	check_flag(t_philo_info *info, int flag)
{
	pthread_mutex_lock(&info->philo_vals->died);
	if (flag)
	{
		info->philo_vals->end_flag = 1;
		pthread_mutex_unlock(&info->philo_vals->died);
		return (1);
	}
	if (info->philo_vals->end_flag)
	{
		pthread_mutex_unlock(&info->philo_vals->died);
		return (1);
	}
	pthread_mutex_unlock(&info->philo_vals->died);
	return (0);
}

void	*func_philo(void *arg)
{
	t_philo_info	*info;

	info = (t_philo_info *)arg;
	if (info->tid % 2 == 0)
		usleep(300);
	while (1)
	{
		usleep(200);
		if (check_flag(info, 0))
			return (0);
		philo_eating(info);
		print_philo_status(info, "is sleeping");
		pass_time(info, info->philo_vals->time_to_sleep);
		print_philo_status(info, "is thinking");
	}
}
