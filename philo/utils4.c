/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:17:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 16:28:18 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_curtime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	pass_time(t_philo_info *info, long long pass_time)
{
	long long	time;

	time = get_curtime();
	while (!check_flag(info, 0) && (get_curtime() - time) < pass_time)
		usleep(100);
}

void	print_philo_status(t_philo_info *info, char *status_str)
{
	long long	time;

	pthread_mutex_lock(&info->philo_vals->died);
	if (info->philo_vals->end_flag == 1)
	{
		pthread_mutex_unlock(&info->philo_vals->died);
		return ;
	}
	pthread_mutex_unlock(&info->philo_vals->died);
	pthread_mutex_lock(&info->philo_vals->print_status);
	if (!check_flag(info, 0))
	{
		time = get_curtime() - info->philo_vals->start;
		printf("%lld %d %s\n", time, info->tid, status_str);
	}
	pthread_mutex_unlock(&info->philo_vals->print_status);
}

static int	check_must_eat_philo(t_philo_info *info)
{
	int	i;

	i = 0;
	info->philo_vals->check_eat_cnt = 0;
	while (i < info->philo_vals->num_of_philo)
	{
		if (info[i].cnt_eat >= info->philo_vals->num_of_must_eat)
			info->philo_vals->check_eat_cnt++;
		i++;
	}
	if (info->philo_vals->check_eat_cnt >= info->philo_vals->num_of_philo)
	{
		check_flag(info, 1);
		pthread_mutex_unlock(&info->philo_vals->eat);
		return (1);
	}
	return (0);
}

int	check_died_flag(t_philo_info *info)
{
	pthread_mutex_lock(&info->philo_vals->eat);
	if (info->eat_time == 0)
	{
		pthread_mutex_unlock(&info->philo_vals->eat);
		return (0);
	}
	if ((get_curtime() - info->eat_time) > (info->philo_vals->time_to_die))
	{
		print_philo_status(info, "died");
		check_flag(info, 1);
		pthread_mutex_unlock(&info->philo_vals->eat);
		return (1);
	}
	else if (info->philo_vals->num_of_must_eat > 0 && info->cnt_eat >= \
			info->philo_vals->num_of_must_eat)
		check_must_eat_philo(info);
	pthread_mutex_unlock(&info->philo_vals->eat);
	return (0);
}
