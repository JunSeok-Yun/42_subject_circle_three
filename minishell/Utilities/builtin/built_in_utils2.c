/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:27:52 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:58:46 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_cmd_operator(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (!check_pipe(temp) && check_redirection(temp))
		redirection_cmd(temp, info);
	else
		exec_cmd(temp, info);
}
