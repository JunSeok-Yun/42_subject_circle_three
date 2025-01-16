/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:46:01 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 04:53:32 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_env_node(t_env_token *env, char *key, char *data)
{
	t_env_token	*temp;
	char		*new_data;
	int			len;

	if (!env || !key || !data)
		return ;
	temp = env;
	len = ft_strlen(key);
	while (temp != NULL)
	{
		if (temp->env_data && ft_strncmp(temp->env_data, key, len) == 0)
		{
			new_data = ft_strdup(data);
			if (!new_data)
				return ;
			free(temp->env_data);
			temp->env_data = new_data;
			return ;
		}
		temp = temp -> next;
	}
}

void	split_key_val(t_env_token *li)
{
	int		i;
	int		j;
	int		id;
	char	*key_str;
	char	*val_str;

	i = -1;
	id = check_equal_idx(li->env_data);
	free_exp_key_value(li);
	key_str = (char *)malloc(sizeof(char) * (id + 1));
	val_str = (char *)malloc(sizeof(char) * (ft_strlen(li->env_data) - id) + 1);
	while (++i < id)
		key_str[i] = li->env_data[i];
	key_str[i] = 0;
	i = id + 1;
	j = 0;
	while (i < ft_strlen(li->env_data))
		val_str[j++] = li->env_data[i++];
	val_str[j] = 0;
	li->env_key = key_str;
	li->env_value = val_str;
}

void	set_split_exp_list(t_env_token *exp_list)
{
	t_env_token	*node;

	node = exp_list;
	while (node)
	{
		split_key_val(node);
		node = node->next;
	}
}

int	check_key_validation(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '+' && (key[i + 1] != 0))
			return (-1);
		else if (key[i] == '+' && (key[i + 1] == 0))
			return (0);
		else if (!((key[i] >= 'A' && key[i] <= 'Z') \
		|| (key[i] >= 'a' && key[i] <= 'z') || key[i] == '_' \
		|| (key[i] >= '0' && key[i] <= '9')))
			return (-1);
		i++;
	}
	return (0);
}

void	change_exp_node(t_env_token *exp, char *key, char *data)
{
	t_env_token	*temp;
	char		*new_data;
	int			len;

	if (!exp || !key || !data)
		return ;
	temp = exp;
	len = ft_strlen(key);
	while (temp)
	{
		if (temp->env_data && ft_strncmp(temp->env_data, key, len) == 0)
		{
			new_data = ft_strdup(data);
			if (!new_data)
				return ;
			free(temp->env_data);
			temp->env_data = new_data;
			split_key_val(temp);
			return ;
		}
		temp = temp -> next;
	}
}
