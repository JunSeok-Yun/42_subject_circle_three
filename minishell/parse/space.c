/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:44:45 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/23 03:07:30 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(t_token *token)
{
	int		i;
	char	*tmp;
	t_token	*next;

	tmp = (char *)malloc(sizeof(char) * 2);
	if (tmp == NULL)
		return (1);
	tmp[0] = 32;
	tmp[1] = '\0';
	i = 0;
	while (token->data[i] == 32)
		++i;
	next = make_new_token(token, i);
	token->data = tmp;
	token->next = next;
	return (0);
}
