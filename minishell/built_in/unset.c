/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:35:03 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/27 12:42:59 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_unset(t_token *token, t_info *info)
{
	t_token	*temp;
	t_token	*next_temp;

	temp = token;
	while (temp)
	{
		next_temp = temp->next;
		if (temp->type == E_TYPE_PARAM && temp->data)
		{
			delete_node_exp(&(info->exp), temp->data);
			delete_node_env(&(info->env), temp->data);
		}
		temp = next_temp;
	}
}

void	delete_node_exp(t_env_token **list, char *find)
{
	t_env_token	*temp;
	t_env_token	*cur;

	if (!list || !*list || !find)
		return ;
	if (delete_first_node(list, find))
		return ;
	cur = (*list);
	while (cur && cur->next != NULL)
	{
		if (cur->next->env_key && find && \
		ft_strncmp(cur->next->env_key, find, ft_strlen(find)) == 0)
		{
			temp = cur->next;
			cur->next = temp->next;
			free_node_data(temp);
			free(temp);
			return ;
		}
		cur = cur -> next;
	}
}

void	delete_node_env(t_env_token **list, char *find)
{
	t_env_token	*temp;
	t_env_token	*cur;
	int			len;

	if (!list || !*list || !find)
		return ;
	if (delete_first_node(list, find))
		return ;
	cur = (*list);
	len = ft_strlen(find);
	while (cur && cur->next != NULL)
	{
		if (cur->next->env_data && find && \
		ft_strncmp(cur->next->env_data, find, len) == 0)
		{
			temp = cur->next;
			cur->next = temp->next;
			free_node_data(temp);
			free(temp);
			return ;
		}
		cur = cur -> next;
	}
}

int	delete_first_node(t_env_token **list, char *find)
{
	t_env_token	*temp;

	if (!list || !*list || !find || !(*list)->env_key)
		return (0);
	temp = (*list);
	if (ft_strcmp(temp->env_key, find) == 0)
	{
		(*list) = (*list)->next;
		free_node_data(temp);
		free(temp);
		return (1);
	}
	return (0);
}
