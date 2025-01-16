/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:21:05 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 04:33:44 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_open(t_token *token);
int	out_open(t_token *token);
int	great_open(t_token *token);
int	open_parse(t_token *token);

int	open_fd(t_token *token, t_info *info)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (open_parse(tmp))
			return (1);
		else if (tmp->type == E_TYPE_HERE_DOC)
			if (here_doc(token, tmp->next, info))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	open_parse(t_token *token)
{
	if (token->type == E_TYPE_IN)
	{
		if (in_open(token->next))
			return (1);
	}
	else if (token->type == E_TYPE_GREAT)
	{
		if (great_open(token->next))
			return (1);
	}
	else if (token->type == E_TYPE_OUT)
	{
		if (out_open(token->next))
			return (1);
	}
	return (0);
}

int	in_open(t_token *token)
{
	token->fd = open(token->data, O_RDONLY);
	if (token->fd == -1)
		return (1);
	return (0);
}

int	out_open(t_token *token)
{
	token->fd = open(token->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (token->fd == -1)
		return (1);
	return (0);
}

int	great_open(t_token *token)
{
	token->fd = open(token->data, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (token->fd == -1)
		return (1);
	return (0);
}
