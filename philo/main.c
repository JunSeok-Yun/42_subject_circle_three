/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:37:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/10/20 15:57:21 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_vals	vals;

	if (check_input_val(argc, argv))
		return (0);
	if (set_philo_vals(&vals, argc, argv))
		return (0);
	if (set_philo_info(&vals))
		return (free_philo_info(&vals));
	if (set_philo_mutex(&vals))
		return (free_mutex(&vals));
	if (create_philosophers(&vals))
		return (0);
	monitoring_philos(&vals);
	free_mutex(&vals);
}
