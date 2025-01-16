/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:24:10 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 07:13:19 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_type	check_type(t_token *token, t_check check, int i, char *param);
t_check	check_first(char c);
t_type	first_type(char *param);

t_token	*make_new_token(t_token *token, int i)
{
	t_token	*new;

	if (token->data[i] == '\0')
	{
		free(token->data);
		return (NULL);
	}
	new = (t_token *)malloc(sizeof(t_token) * 1);
	if (new == NULL)
		return (NULL);
	new->type = check_type(token, check_first(token->data[i]), i, NULL);
	new->fd = -1;
	new->next = NULL;
	new->data = init_new_token_data(token, i);
	if (new->data == NULL)
		return (NULL);
	free(token->data);
	return (new);
}

char	*init_new_token_data(t_token *token, int i)
{
	char	*new_data;
	int		j;

	new_data = (char *)malloc(sizeof(char) * (ft_strlen(token->data) - i + 1));
	if (new_data == NULL)
		return (NULL);
	j = 0;
	while (token->data[i] != '\0')
	{
		new_data[j] = token->data[i];
		++i;
		++j;
	}
	new_data[j] = '\0';
	return (new_data);
}

t_type	check_type(t_token *token, t_check check, int i, char *param)
{
	if (token == NULL)
		return (first_type(param));
	if (token->type == E_TYPE_PIPE && (check == E_Q || check == E_DQ
			|| check == E_STR))
		return (E_TYPE_CMD);
	if (token->type == E_TYPE_GREAT || token->type == E_TYPE_HERE_DOC
		|| token->type == E_TYPE_IN || token->type == E_TYPE_OUT)
		return (E_TYPE_FILE);
	if (check == E_PIPE)
		return (E_TYPE_PIPE);
	if (check == E_OPTION)
		return (E_TYPE_OPTION);
	if (check == E_SP)
		return (E_TYPE_SP);
	if (check == E_OPER)
		return (check_oper(token, i));
	return (E_TYPE_PARAM);
}

t_type	first_type(char *param)
{
	if (param[0] == 32)
		return (E_TYPE_SP);
	if (param[0] == 45)
		return (E_TYPE_OPTION);
	if (param[0] == '|')
		return (E_TYPE_PIPE);
	if (param[0] == '<')
	{
		if (param[1] == '<')
			return (E_TYPE_HERE_DOC);
		return (E_TYPE_IN);
	}
	if (param[0] == '>')
	{
		if (param[1] == '>')
			return (E_TYPE_GREAT);
		return (E_TYPE_OUT);
	}
	return (E_TYPE_CMD);
}

t_check	check_first(char c)
{
	if (c == '\0')
		return (E_NONE);
	if (c == 39)
		return (E_Q);
	if (c == 34)
		return (E_DQ);
	if (c == 32)
		return (E_SP);
	if (c == 45)
		return (E_OPTION);
	if (c == '|')
		return (E_PIPE);
	if (c == '<' || c == '>')
		return (E_OPER);
	return (E_STR);
}
