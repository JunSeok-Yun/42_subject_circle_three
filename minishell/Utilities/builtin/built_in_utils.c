/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:25:02 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 04:27:04 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_operator(t_token *token)
{
	int		i;
	int		cnt;
	t_token	*temp;

	temp = token;
	i = 0;
	cnt = 0;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_OPTION \
		|| temp->type == E_TYPE_PARAM || temp->type == E_TYPE_SP)
			cnt++;
		i++;
		temp = temp -> next;
	}
	if (i == cnt)
		return (1);
	return (0);
}

int	check_redirection(t_token *token)
{
	t_token	*temp;
	int		cnt;

	cnt = 0;
	temp = token;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_GREAT || temp->type == E_TYPE_HERE_DOC \
		|| temp->type == E_TYPE_IN || temp->type == E_TYPE_OUT)
			cnt++;
		temp = temp -> next;
	}
	return (cnt);
}

int	check_pipe(t_token *token)
{
	int		cnt;
	t_token	*temp;

	cnt = 0;
	temp = token;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_PIPE)
			cnt++;
		temp = temp -> next;
	}
	return (cnt);
}

int	check_pipe_cmd(t_info *info)
{
	if (info->cmd != NULL || info->cmd_lines != NULL \
	|| info->cmd_paths != NULL || info->paths != NULL)
		return (1);
	return (0);
}

void	cleanup_fds(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp && temp->fd > 2)
		{
			close(temp->fd);
			temp->fd = -1;
		}
		if (temp->type == E_TYPE_HERE_DOC && temp->next)
			unlink(temp->next->data);
		temp = temp->next;
	}
}
