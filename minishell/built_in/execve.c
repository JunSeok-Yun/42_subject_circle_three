/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:09:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 05:29:54 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_list_size(t_env_token *env_list)
{
	int			cnt;
	t_env_token	*temp;

	temp = env_list;
	cnt = 0;
	while (temp)
	{
		cnt++;
		temp = temp -> next;
	}
	return (cnt);
}

char	**create_envp(t_info *info)
{
	int			i;
	char		**envp;
	char		*str;
	t_env_token	*temp;

	temp = info->env;
	envp = (char **)malloc(sizeof(char *) * (env_list_size(temp) + 1));
	i = 0;
	while (temp)
	{
		str = ft_strdup(temp->env_data);
		envp[i] = ft_strdup(str);
		free(str);
		i++;
		temp = temp -> next;
	}
	envp[i] = 0;
	return (envp);
}

void	free_pipe_cmd(t_info *info)
{
	if (info->cmd_lines != NULL)
		free_execve(info->cmd_lines);
	free(info->cmd_lines);
	if (info->paths != NULL)
		free(info->paths);
	if (info->cmd_paths != NULL)
		free_execve(info->cmd_paths);
	free(info->cmd_paths);
	if (info->cmd != NULL)
		free(info->cmd);
}

char	*combine_cmd(char **path, char *cmd)
{
	char	*temp;
	char	*command;

	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

int	check_paths(t_info *info)
{
	if (!info->paths)
	{
		print_cd_error(info->cmd_lines[0], 1);
		return (1);
	}
	return (0);
}
