/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:54 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 04:49:56 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_export(t_token *node, t_info *info)
{
	t_token		*temp;

	temp = node;
	if (check_token_size(temp) == 1 && temp->type == E_TYPE_CMD)
	{
		exp_bubble_sort(info->exp);
		print_exp_list(info->exp);
	}
	else if (check_token_size(temp) != 1)
	{
		while (temp != NULL)
		{
			if (temp->type == E_TYPE_PARAM)
				execute_export_cmd(info, temp->data);
			temp = temp -> next;
		}
	}
	change_pwd_oldpwd(info);
}

void	change_pwd_oldpwd(t_info *info)
{
	char	*find;

	find = find_value(info, "PWD");
	if (find_key(info->exp, "PWD") == 1)
	{
		if (ft_strcmp(find, info->pwd) != 0)
		{
			if (info->pwd != NULL)
				free(info->pwd);
			info->pwd = ft_strdup(find_value(info, "PWD"));
		}
	}
	free(find);
	find = find_value(info, "OLDPWD");
	if (find_key(info->exp, "OLDPWD") == 1)
	{
		if (ft_strcmp(find, info->oldpwd) != 0)
		{
			if (info->oldpwd != NULL)
				free(info->oldpwd);
			info->oldpwd = ft_strdup(find_value(info, "OLDPWD"));
		}
	}
	free(find);
}

void	execute_export_cmd(t_info *info, char *data)
{
	if (check_validation(data) == -1)
	{
		print_export_error(data);
		return ;
	}
	if (cnt_equal(data) == 0)
		add_exp_data(info->exp, data);
	else if (check_plus_operator(data))
		join_exp_data(info->exp, info->env, data);
	else if (cnt_equal(data) == 1)
		add_exp_env_data(info->exp, info->env, data);
}

int	find_exp_list(t_env_token *exp, char *data)
{
	t_env_token	*temp;

	temp = exp;
	while (temp)
	{
		if (temp->env_data != NULL \
		&& ft_strncmp(temp->env_data, data, ft_strlen(data)) == 0)
		{
			if (temp->env_key != NULL \
			&& ft_strncmp(temp->env_key, data, ft_strlen(data)) == 0)
				return (1);
			else
			{
				if (temp->env_key != NULL)
					free(temp->env_key);
				temp->env_key = ft_strdup(data);
				return (1);
			}
		}
		temp = temp -> next;
	}
	return (0);
}

void	add_exp_data(t_env_token *exp_list, char *data)
{
	t_env_token	*new_node;
	t_env_token	*temp;

	temp = exp_list;
	if (find_exp_list(temp, data))
		return ;
	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(exp_list, new_node);
	while (temp)
	{
		if (temp->env_data != NULL \
		&& ft_strncmp(temp->env_data, data, ft_strlen(data)) == 0)
		{
			temp->env_key = ft_strdup(data);
			break ;
		}
		temp = temp -> next;
	}
}
