/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:16:25 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_data_val(char *new_key, char *new_val, char *key, char *val)
{
	if (new_key != NULL)
		free(new_key);
	if (new_val != NULL)
		free(new_val);
	if (key != NULL)
		free(key);
	if (val != NULL)
		free(val);
}

void	change_match_exp(t_env_token *exp, char *key, char *val)
{
	char	*new_key;
	char	*new_value;

	new_key = ft_strdup(key);
	new_value = NULL;
	if (!new_key)
	{
		free_data_val(NULL, NULL, key, val);
		return ;
	}
	if (val != NULL)
	{
		new_value = ft_strdup(val);
		if (!new_value)
		{
			free_data_val(new_key, NULL, key, val);
			return ;
		}
	}
	update_exp_node(exp, new_key, new_value);
	free(key);
	free(val);
}

void	join_exp_data(t_env_token *exp, t_env_token *env, char *data)
{
	char		*key;
	char		*value;
	t_env_token	*node;

	node = exp;
	key = split_key(data);
	if (!key)
		return ;
	value = split_value(data);
	while (node)
	{
		if (ft_strcmp(node->env_key, key) == 0)
		{
			check_env_data(env, data, key, value);
			change_match_exp(exp, key, value);
			return ;
		}
		node = node -> next;
	}
	add_export(env, exp, data);
}

int	check_validation(char *data)
{
	int		i;
	char	*key;

	i = 0;
	if (!((data[i] >= 'A' && data[i] <= 'Z') \
	|| (data[i] >= 'a' && data[i] <= 'z') || data[i] == '_'))
		return (-1);
	key = get_key(data);
	if (check_key_validation(key) == -1)
	{
		free(key);
		return (-1);
	}
	free(key);
	return (0);
}

int	cnt_equal(char *data)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (data[i])
	{
		if (data[i] == '=')
			cnt++;
		i++;
	}
	return (cnt);
}
