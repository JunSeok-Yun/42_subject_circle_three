/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:53:35 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 04:29:54 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_env_token *list)
{
	t_env_token	*node;

	node = list;
	while (node != NULL)
	{
		printf("%s\n", node->env_data);
		node = node->next;
	}
}

void	print_exp_list(t_env_token *list)
{
	t_env_token	*node;

	node = list;
	while (node != NULL)
	{
		if (node->env_value != NULL)
			printf("declare -x %s=\"%s\"\n", node->env_key, node->env_value);
		else
			printf("declare -x %s\n", node->env_key);
		node = node->next;
	}
}
