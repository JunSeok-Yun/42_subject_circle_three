/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:05:16 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/24 23:49:19 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(t_token *token)
{
	int		i;
	int		j;
	char	*tmp;
	t_token	*next;

	i = 1;
	while (token->data[i] != 39 && token->data[i] != '\0')
		++i;
	tmp = (char *)malloc(sizeof(char) * i);
	if (tmp == NULL)
		return (-1);
	i = 1;
	j = 0;
	while (token->data[i] != 39 && token->data[i] != '\0')
	{
		tmp[j] = token->data[i];
		++i;
		++j;
	}
	tmp[j] = '\0';
	next = make_new_token(token, i + 1);
	token->data = tmp;
	token->next = next;
	return (0);
}
