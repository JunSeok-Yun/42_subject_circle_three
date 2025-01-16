/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:55:32 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 07:06:04 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_type	check_oper(t_token *token, int i)
{
	if (token->data[i] == '<')
	{
		if (token->data[i + 1] == '<')
			return (E_TYPE_HERE_DOC);
		return (E_TYPE_IN);
	}
	if (token->data[i] == '>')
	{
		if (token->data[i + 1] == '>')
			return (E_TYPE_GREAT);
		return (E_TYPE_OUT);
	}
	return (E_TYPE_PARAM);
}
