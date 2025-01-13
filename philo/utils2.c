/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:42:57 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 16:14:42 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input_val(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((i > 0 && j > 0) && (argv[i][j] == '-' || argv[i][j] == '+'))
			{
				error_exception("input value is worng !! only numbers\n");
				return (1);
			}
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
			{
				error_exception("input value is worng !! only numbers\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	long long int	res;
	int				sign;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != 0 || res > 2147483647 || res < -2147483648)
	{
		printf("integer value overflow or underflow");
		exit(1);
	}
	return ((int)(res * sign));
}

void	take_left_right_fork(t_philo_info *info)
{
	usleep(300);
	pthread_mutex_lock(&info->philo_vals->forks[info->left_f]);
	print_philo_status(info, "has taken a fork");
	pthread_mutex_lock(&info->philo_vals->forks[info->right_f]);
	print_philo_status(info, "has taken a fork");
	pthread_mutex_lock(&info->philo_vals->eat);
	print_philo_status(info, "is eating");
	info->eat_time = get_curtime();
	info->cnt_eat += 1;
	pthread_mutex_unlock(&info->philo_vals->eat);
	pass_time(info, info->philo_vals->time_to_eat);
	pthread_mutex_unlock(&info->philo_vals->forks[info->right_f]);
	pthread_mutex_unlock(&info->philo_vals->forks[info->left_f]);
}

void	take_right_left_fork(t_philo_info *info)
{
	pthread_mutex_lock(&info->philo_vals->forks[info->right_f]);
	print_philo_status(info, "has taken a fork");
	pthread_mutex_lock(&info->philo_vals->forks[info->left_f]);
	print_philo_status(info, "has taken a fork");
	pthread_mutex_lock(&info->philo_vals->eat);
	print_philo_status(info, "is eating");
	info->eat_time = get_curtime();
	info->cnt_eat += 1;
	pthread_mutex_unlock(&info->philo_vals->eat);
	pass_time(info, info->philo_vals->time_to_eat);
	pthread_mutex_unlock(&info->philo_vals->forks[info->left_f]);
	pthread_mutex_unlock(&info->philo_vals->forks[info->right_f]);
}
