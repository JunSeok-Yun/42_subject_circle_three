/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:38:38 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/23 04:08:41 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(t_token *token)
{
	int	i;

	i = 1;
	if (token->data[0] == '-')
	{
		while (token->data[i] == 'n')
			i++;
		if (ft_strlen(token->data) == i)
			return (1);
	}
	return (0);
}

void	print_param(t_token *node)
{
	if (node->next != NULL)
		printf("%s ", node->data);
	else
		printf("%s", node->data);
}

void	print_echo(t_token *node, int flag, int check)
{
	t_token	*temp;

	temp = node;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_OPTION && flag == 0 && check_option(temp))
		{
			check = 1;
			flag = 1;
		}
		else if (temp->type == E_TYPE_OPTION && flag == 1 && check_option(temp))
			flag = 1;
		else if (((temp->type == E_TYPE_OPTION && flag == 1) \
		|| (temp->type == E_TYPE_OPTION && flag == 0)) && !check_option(temp))
		{
			print_param(temp);
			flag = 2;
		}
		else if (temp->type == E_TYPE_PARAM \
		|| (flag != 1 && temp->type == E_TYPE_OPTION))
			print_param(temp);
		temp = temp->next;
	}
	if (check != 1)
		printf("\n");
}

int	check_echo_option(t_token *node)
{
	t_token	*temp;

	temp = node;
	if (temp->next->next->type != E_TYPE_OPTION)
		return (-1);
	else if (temp->next->next->type == E_TYPE_OPTION)
		return (0);
	return (0);
}

void	cmd_echo(t_token *node)
{
	t_token	*temp;
	int		flag;

	temp = node;
	if (check_token_size(temp) == 1)
	{
		printf("\n");
		return ;
	}
	flag = check_echo_option(node);
	print_echo(node, flag, 0);
}
