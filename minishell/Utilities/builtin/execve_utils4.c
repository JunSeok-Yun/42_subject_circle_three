/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:03:36 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:58:34 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_pipes(t_info *info, int pipe_cnt)
{
	int	i;

	info->pipes = malloc(sizeof(int *) * pipe_cnt);
	i = 0;
	while (i < pipe_cnt)
	{
		info->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(info->pipes[i]) < 0)
			pipe_error();
		i++;
	}
}

void	init_pipe_line(t_info *info, int cnt)
{
	info->pids = malloc(sizeof(pid_t) * cnt);
	if (!info->pids)
		malloc_error();
	if (cnt > 1)
		create_pipes(info, cnt - 1);
}

void	malloc_error(void)
{
	ft_putendl_fd("minishell: malloc error", 2);
	return ;
}

void	pipe_error(void)
{
	ft_putendl_fd("minishell: pipe error", 2);
	return ;
}

t_token	*skip_non_command_tokens(t_token *token)
{
	while (token && !is_argv_token(token->type))
		token = token->next;
	return (token);
}
