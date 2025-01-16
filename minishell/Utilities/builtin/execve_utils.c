/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:17:29 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:32:29 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes_parent(t_info *info, int pipe_cnt)
{
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		close(info->pipes[i][0]);
		close(info->pipes[i][1]);
		i++;
	}
}

int	wait_command(t_info *info, int cmd_cnt)
{
	int	cmd_idx;
	int	status;

	cmd_idx = 0;
	while (cmd_idx < cmd_cnt)
	{
		if (waitpid(info->pids[cmd_idx], &status, 0) == -1)
			break ;
		cmd_idx++;
	}
	g_dj = WEXITSTATUS(status);
	init_exit_code(info);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_pa);
	return (0);
}

void	finish_execution(t_info *info, int pipe_cnt)
{
	int	i;

	i = 0;
	if (info->pipes != NULL)
	{
		while (i < pipe_cnt)
		{
			free(info->pipes[i]);
			i++;
		}
		free(info->pipes);
		info->pipes = NULL;
	}
	if (info->pids != NULL)
	{
		free(info->pids);
		info->pids = NULL;
	}
}

t_token	*exec_command(t_token *token, t_info *info, int cnt, char **envp)
{
	int		cmd_idx;
	t_token	*cur;

	cmd_idx = 0;
	cur = token;
	while (cur && cmd_idx < cnt)
	{
		cur = skip_non_command_tokens(cur);
		if (!cur)
			break ;
		info->pids[cmd_idx] = fork();
		if (info->pids[cmd_idx] < 0)
			finish_execution(info, cnt - 1);
		if (info->pids[cmd_idx] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, sig_handler_child);
			exec_child(info, cur, cmd_idx, envp);
			exit (0);
		}
		signal(SIGINT, SIG_IGN);
		cur = move_next_cmd(cur);
		cmd_idx++;
	}
	return (cur);
}
