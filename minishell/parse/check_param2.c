/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:11:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/29 20:39:54 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	jump_sp(char *param, int *i)
{
	while (param[*i] == 32 && param[*i] != '\0')
		++*i;
	if (param[*i] == '\0')
		--*i;
	return ;
}

void	jump_quote(char *param, int *i)
{
	if (param[*i] == 34)
	{
		*i = *i + 1;
		while (param[*i] != 34 && param[*i] != '\0')
			++*i;
		if (param[*i] == '\0')
			--*i;
		return ;
	}
	if (param[*i] == 39)
	{
		*i = *i + 1;
		while (param[*i] != 39 && param[*i] != '\0')
			++*i;
		if (param[*i] == '\0')
			--*i;
		return ;
	}
	return ;
}
