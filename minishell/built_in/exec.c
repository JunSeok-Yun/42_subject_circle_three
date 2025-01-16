/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:41:30 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:29:20 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_token *token, t_info *info)
{
	t_token	*temp;
	char	**envp;

	if (token->type != E_TYPE_CMD)
		return ;
	temp = token;
	envp = create_envp(info);
	init_cmd_lines(token, info);
	if (check_pipe(temp) == 0)
		execute_single_cmd(info, token, envp);
	else
		execute_pipe_cmd(token, info, envp);
	free_envp(envp);
}

void	init_cmd_lines(t_token *token, t_info *info)
{
	int		i;
	int		size;
	t_token	*temp;

	i = 0;
	temp = token;
	size = check_pipe_token_size(temp);
	info->cmd_lines = (char **)malloc(sizeof(char *) * (size + 1));
	if (!info->cmd_lines)
		return ;
	info->paths = find_value(info, "PATH");
	if (info->paths != NULL)
		info->cmd_paths = ft_split(info->paths, ':');
	else
		info->cmd_paths = NULL;
	while (temp)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_OPTION \
		|| temp->type == E_TYPE_PARAM)
			info->cmd_lines[i++] = ft_strdup(temp->data);
		temp = temp -> next;
	}
	info->cmd_lines[i] = 0;
}

int	execute_pipe_cmd(t_token *token, t_info *info, char **envp)
{
	t_token	*cur;
	int		status;

	cur = 0;
	info->pipe_cnt = count_commands(token);
	init_pipe_line(info, info->pipe_cnt);
	cur = exec_command(token, info, info->pipe_cnt, envp);
	if (cur)
	{
		ft_putendl_fd("Warning: Unused tokens after pipeline: ", 2);
		while (cur)
		{
			ft_putendl_fd(cur->data, 2);
			ft_putendl_fd(" ", 2);
			cur = cur->next;
		}
		ft_putendl_fd("\n", 2);
	}
	close_pipes_parent(info, info->pipe_cnt - 1);
	cleanup_fds(token);
	status = wait_command(info, info->pipe_cnt);
	finish_execution(info, info->pipe_cnt - 1);
	return (status);
}

int	execute_single_cmd(t_info *info, t_token *token, char **envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (check_paths(info))
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sig_handler_child);
		if (access(info->cmd_lines[0], X_OK) != 0)
			execute_single_child(info, token, envp);
		else
			info->cmd = info->cmd_lines[0];
		execve(info->cmd, info->cmd_lines, envp);
		free_child_var(info, token, envp);
		exit(1);
	}
	else if (pid != 0)
		execute_single_signal(info, pid, &status);
	return (0);
}
