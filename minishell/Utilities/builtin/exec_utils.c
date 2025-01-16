/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:25:04 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:53:44 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_single_child(t_info *info, t_token *token, char **envp)
{
	info->cmd = combine_cmd(info->cmd_paths, info->cmd_lines[0]);
	if (!info->cmd)
	{
		print_err_free(info->cmd_lines[0], info, token, envp);
		exit (127);
	}
}

void	execute_single_signal(t_info *info, pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	g_dj = WEXITSTATUS(*status);
	init_exit_code(info);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_pa);
}
