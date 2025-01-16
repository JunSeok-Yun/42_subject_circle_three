/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:48:52 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/29 14:30:51 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe(t_token *token)
{
	int		i;
	char	*tmp;
	t_token	*next;

	tmp = (char *)malloc(sizeof(char) * 2);
	if (token->data == NULL)
		return (1);
	tmp[0] = '|';
	tmp[1] = '\0';
	i = 1;
	while (token->data[i] == 32 && token->data[i] != '\0')
		i++;
	next = make_new_token(token, i);
	token->data = tmp;
	token->next = next;
	return (0);
}
