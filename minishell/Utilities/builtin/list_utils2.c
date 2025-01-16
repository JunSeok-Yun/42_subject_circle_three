/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:07:06 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 05:07:44 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_token_size(t_token *node)
{
	t_token	*temp;
	int		size;

	size = 0;
	temp = node;
	while (temp)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_PARAM \
		|| temp->type == E_TYPE_OPTION)
			size++;
		temp = temp -> next;
	}
	return (size);
}
