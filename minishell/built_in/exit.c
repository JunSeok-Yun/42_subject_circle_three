/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 23:24:44 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:47:00 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] >= '0' && data[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*return_token_param(t_token *token)
{
	t_token	*temp;
	char	*tmp;

	tmp = NULL;
	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_PARAM)
		{
			tmp = ft_strdup(temp->data);
			return (tmp);
		}
		temp = temp -> next;
	}
	return (tmp);
}

void	free_all_exit(t_token *token, t_info *info, char *data)
{
	free_all(token, info);
	free(data);
}

int	cmd_exit(t_token *token, t_info *info)
{
	char	*data;
	int		exit_code;

	data = return_token_param(token);
	exit_code = 0;
	if (check_token_size(token) == 2 && !is_numeric(data))
	{
		print_exit_error(1);
		free_all_exit(info->head, info, data);
		exit (2);
	}
	else if (check_token_size(token) >= 3)
		print_error_cmd_exit(info, data);
	if (data != NULL)
	{
		exit_code = ft_atoi(data);
		printf("exit\n");
		free_all_exit(info->head, info, data);
		exit (exit_code);
	}
	printf("exit\n");
	free_all_exit(info->head, info, data);
	exit (0);
}

void	print_error_cmd_exit(t_info *info, char *data)
{
	if (!is_numeric(data))
		print_exit_error(1);
	else
		print_exit_error(0);
	free_all_exit(info->head, info, data);
	exit(1);
}
