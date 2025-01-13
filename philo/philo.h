/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:53:17 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 16:04:34 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo_info
{
	int						tid;
	int						cnt_eat;
	int						right_f;
	int						left_f;
	long long				eat_time;
	struct s_philo_vals		*philo_vals;
	pthread_t				pthread;
}	t_philo_info;

typedef struct s_philo_vals
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				check_eat_cnt;
	int				end_flag;
	long long		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_status;
	pthread_mutex_t	eat;
	pthread_mutex_t	died;
	t_philo_info	*philosopers;
}	t_philo_vals;

int			error_exception(char *str);

int			free_philo_info(t_philo_vals *vals);
int			free_mutex(t_philo_vals *vals);
void		monitoring_philos(t_philo_vals *vals);

int			set_philo_vals(t_philo_vals *vals, int argc, char **argv);
int			set_philo_info(t_philo_vals *vals);
int			set_philo_mutex(t_philo_vals *vals);
int			create_philosophers(t_philo_vals *vals);

int			check_input_val(int argc, char **argv);
int			ft_atoi(char *str);
void		philo_eating(t_philo_info *info);
void		take_right_left_fork(t_philo_info *info);
void		take_left_right_fork(t_philo_info *info);
int			check_flag(t_philo_info *info, int flag);
void		*func_philo(void *arg);

long long	get_curtime(void);
void		pass_time(t_philo_info *info, long long pass_time);
void		print_philo_status(t_philo_info *info, char *status_str);
int			check_died_flag(t_philo_info *info);
#endif
