/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:06:56 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 07:06:27 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_env_data(t_env_token *env, char *data, char *key, char *val)
{
	int			len;
	char		*temp;
	char		*add_data;
	t_env_token	*node;

	node = env;
	add_data = create_env_data(data);
	len = ft_strlen(key);
	while (node != NULL)
	{
		if (ft_strncmp(node->env_data, key, len) == 0)
		{
			temp = ft_strdup(node->env_data);
			if (node->env_data != NULL)
				free(node->env_data);
			node->env_data = ft_strjoin(temp, val);
			free(temp);
			free(add_data);
			return ;
		}
		node = node -> next;
	}
	add_new_exp_node(env, add_data);
}

char	*get_new_value(t_env_token *temp, char *value)
{
	if (temp->env_value && value)
		return (ft_strjoin(temp->env_value, value));
	if (value != NULL)
		return (ft_strdup(value));
	return (NULL);
}

char	*get_temp_data(char *data, char *key, char *value)
{
	char	*result;
	char	*temp;

	if (data != NULL && value != NULL)
		result = ft_strjoin(data, value);
	else if (data != NULL)
		result = ft_strdup(data);
	else if (value != NULL)
	{
		temp = ft_strjoin(key, "=");
		result = ft_strjoin(temp, value);
		free(temp);
	}
	else
		result = NULL;
	return (result);
}

void	update_exp_node(t_env_token *node, char *key, char *value)
{
	char		*new_value;
	char		*temp_data;
	t_env_token	*temp;

	if (!node || !key)
		return ;
	temp = node;
	while (temp)
	{
		if (temp->env_key && ft_strcmp(temp->env_key, key) == 0)
		{
			new_value = get_new_value(temp, value);
			temp_data = get_temp_data(temp->env_data, key, value);
			free_exp_key_value(temp);
			temp->env_key = key;
			temp->env_value = new_value;
			free(temp->env_data);
			temp->env_data = temp_data;
			return ;
		}
		temp = temp -> next;
	}
	free(key);
	if (value != NULL)
		free(value);
}

void	add_export(t_env_token *env, t_env_token *exp, char *data)
{
	add_new_exp_node(exp, data);
	add_new_exp_node(env, data);
	set_split_exp_list(exp);
}
