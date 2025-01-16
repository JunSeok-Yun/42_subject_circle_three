/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:33:40 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 02:38:42 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_exit_code(t_info *info)
{
	t_env_token	*tmp;

	tmp = info->exp;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->env_key, "?") == 0)
		{
			free(tmp->env_value);
			tmp->env_value = ft_itoa(g_dj);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

int	ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sol;
	int	sign;

	i = 0;
	sol = 0;
	sign = 1;
	while (str[i] != '\0' && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		++i;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		sol = (sol * 10) + (str[i] - 48);
		++i;
	}
	return (sol * sign);
}

char	*ft_itoa(int num)
{
	int		size;
	int		num_tmp;
	char	*tmp;

	size = 0;
	num_tmp = num;
	while (num_tmp / 10 > 0)
	{
		num_tmp = num_tmp / 10;
		size = size + 1;
	}
	size = size + 1;
	tmp = (char *)malloc(sizeof(char) * size + 1);
	if (tmp == NULL)
		return (NULL);
	tmp[size] = '\0';
	size = size - 1;
	while (size >= 0)
	{
		tmp[size] = num % 10 + 48;
		num = num / 10;
		--size;
	}
	return (tmp);
}
