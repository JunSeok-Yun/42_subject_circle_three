/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:03:03 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:58:24 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_pipeline_cmd(t_info *info, t_token *token, char **envp)
{
	char	**argv;

	argv = make_argv(token);
	if (!argv)
		handle_argv_error();
	if (access(token->data, X_OK) == 0)
		execve(token->data, argv, envp);
	else if (check_builtin_argv(token->data, argv, envp))
		execute_cmd_pipe(token, info);
	else
		com_not_find(info, argv, envp);
	free_execve(argv);
}

void	com_not_find(t_info *info, char **argv, char **envp)
{
	info->cmd = combine_cmd(info->cmd_paths, argv[0]);
	if (!info->cmd)
	{
		if (isatty(STDERR_FILENO))
		{
			ft_putstr_fd("mini: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putendl_fd(": command not found\n", 2);
			g_dj = 127;
			init_exit_code(info);
		}
		free_token(info->head);
		free_info(info);
		free_envp(envp);
		free_execve(argv);
		exit (127);
	}
	execve(info->cmd, argv, envp);
}

void	handle_redirections(t_token *token, int *in_fd, int *out_fd)
{
	t_token	*temp;

	*out_fd = 1;
	*in_fd = 0;
	temp = token;
	while (temp && temp->type != E_TYPE_PIPE)
	{
		if (temp->type == E_TYPE_GREAT)
			*out_fd = temp->next->fd;
		else if (temp->type == E_TYPE_OUT)
			*out_fd = temp->next->fd;
		else if (temp->type == E_TYPE_IN)
			*in_fd = temp->next->fd;
		else if (temp->type == E_TYPE_HERE_DOC)
			*in_fd = temp->next->fd;
		temp = temp->next;
	}
}

void	close_pipes_child(t_info *info, int pipe_cnt, int idx)
{
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		if (i != idx - 1)
			close(info->pipes[i][0]);
		if (i != idx)
			close(info->pipes[i][1]);
		i++;
	}
}

void	set_pipe_io(t_info *info, int idx, int pipe_cnt)
{
	if (idx > 0 && info->pipes && info->pipes[idx - 1])
		dup2(info->pipes[idx - 1][0], STDIN_FILENO);
	if (idx < pipe_cnt && info->pipes && info->pipes[idx])
		dup2(info->pipes[idx][1], STDOUT_FILENO);
}
