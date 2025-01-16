/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:04:44 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 05:58:13 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleanup_fds_child(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->type != E_TYPE_PIPE)
	{
		if (temp->next && temp->next->fd > 2)
			close(temp->next->fd);
		if (temp->type == E_TYPE_HERE_DOC && temp->next)
			unlink(temp->next->data);
		temp = temp->next;
	}
}

void	exec_child(t_info *info, t_token *token, int idx, char **envp)
{
	int	pipe_cnt;
	int	in_fd;
	int	out_fd;

	in_fd = 0;
	out_fd = 0;
	token = skip_non_command_tokens(token);
	if (!token)
		return ;
	pipe_cnt = info->pipe_cnt - 1;
	set_pipe_io(info, idx, pipe_cnt);
	close_pipes_child(info, pipe_cnt, idx);
	handle_redirections(token, &in_fd, &out_fd);
	if (in_fd > 0)
		dup2(in_fd, 0);
	if (out_fd > 1)
		dup2(out_fd, 1);
	execute_pipeline_cmd(info, token, envp);
	if (idx - 1 >= 0 && pipe_cnt > 1)
		close(info->pipes[idx - 1][0]);
	if (idx < info->pipe_cnt - 1)
		close(info->pipes[idx][1]);
	cleanup_fds_child(token);
	free_child_var(info, token, envp);
}

int	count_commands(t_token *token)
{
	int		count;
	t_token	*cur;

	count = 1;
	cur = token;
	while (cur)
	{
		if (cur->type == E_TYPE_PIPE)
		{
			count++;
			cur = cur->next;
			while (cur && cur->type == E_TYPE_SP)
				cur = cur->next;
			if (!cur)
				break ;
		}
		cur = cur->next;
	}
	return (count);
}

int	is_argv_token(t_type type)
{
	if (type == E_TYPE_CMD || type == E_TYPE_OPTION || type == E_TYPE_PARAM)
		return (1);
	return (0);
}
