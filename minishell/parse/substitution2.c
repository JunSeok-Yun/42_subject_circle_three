/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:24:12 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 04:40:56 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_current_value(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	check_env_var(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '$' && check_current_value(data[i + 1]))
			return (1);
		++i;
	}
	return (0);
}

int	jump_current(char *param, int *i)
{
	int	size;

	size = 0;
	while (check_current_value(param[*i]))
	{
		++*i;
		++size;
	}
	return (size);
}

int	tail_size(char *data, int *i)
{
	int	size;

	size = 0;
	while (data[*i] != '\0')
	{
		++*i;
		++size;
	}
	return (size);
}
