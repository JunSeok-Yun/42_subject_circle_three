/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:18:24 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 06:16:26 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->data);
		if (temp->fd != -1)
			close(temp->fd);
		free(temp);
	}
	return ;
}

void	free_info(t_info *info)
{
	free(info->pwd);
	info->pwd = NULL;
	free_env_token(info->env);
	free_env_token(info->exp);
	free(info->oldpwd);
	info->oldpwd = NULL;
	free(info->home);
	if (info->paths != NULL)
		free(info->paths);
	if (info->cmd != NULL)
		free(info->cmd);
	free_execve(info->cmd_paths);
	free_execve(info->cmd_lines);
	free_pipe_info(info->pipes, info->pipe_cnt);
	if (info->pids != NULL)
		free(info->pids);
	free(info);
	return ;
}

char	*free_env_token(t_env_token *token)
{
	t_env_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		if (tmp->env_data != NULL)
			free(tmp->env_data);
		if (tmp->env_key != NULL)
			free(tmp->env_key);
		if (tmp->env_value != NULL)
			free(tmp->env_value);
		free(tmp);
	}
	return (NULL);
}

void	free_execve(char **data)
{
	int	i;

	if (data != NULL)
	{
		i = 0;
		while (data[i])
		{
			free(data[i]);
			i++;
		}
		free(data);
	}
}

void	free_all(t_token *token, t_info *info)
{
	if (token != NULL)
		free_token(token);
	if (info != NULL)
		free_info(info);
	return ;
}
