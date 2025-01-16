/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:49:07 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:59:13 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_equal_idx(char *exp_data)
{
	int	i;

	if (!exp_data)
		return (0);
	i = 0;
	while (exp_data[i] != '=' && exp_data[i])
		i++;
	return (i);
}

char	*create_env_data(char *data)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen(data);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '+')
			i++;
		else
			new_str[j++] = data[i++];
	}
	new_str[j] = 0;
	return (new_str);
}

int	check_plus_operator(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '+' && data[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_plus_operator_idx(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '+')
		i++;
	return (i);
}
