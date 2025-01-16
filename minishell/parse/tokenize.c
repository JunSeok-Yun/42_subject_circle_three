/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 07:11:12 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_info *info);
void	organize_token(t_token *token);
void	delete_token(t_token *token);
t_token	*make_head_token(char *param);

t_token	*tokenize(char *param, t_info *info)
{
	t_token	*token;

	if (check_param(param))
	{
		g_dj = 2;
		init_exit_code(info);
		return (NULL);
	}
	token = make_head_token(param);
	if (token == NULL)
		return (NULL);
	if (make_token(token, info))
	{
		print_error(1);
		return (NULL);
	}
	if (open_fd(token, info))
	{
		free_token(token);
		print_error(1);
		return (NULL);
	}
	organize_token(token);
	info->head = token;
	return (token);
}

t_token	*make_head_token(char *param)
{
	t_token	*head;

	head = (t_token *)malloc(sizeof(t_token) * 1);
	if (head == NULL)
		return (NULL);
	head->data = param;
	head->type = check_type(NULL, check_first(param[0]), 0, param);
	head->fd = -1;
	head->next = NULL;
	return (head);
}

int	make_token(t_token *token, t_info *info)
{
	int		check;
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (check_first(tmp->data[0]) == E_Q)
			check = is_quote(tmp);
		else if (check_first(tmp->data[0]) == E_DQ)
			check = is_dquote(tmp, info);
		else if (check_first(tmp->data[0]) == E_SP)
			check = is_space(tmp);
		else if (check_first(tmp->data[0]) == E_STR)
			check = is_str(tmp, info);
		else if (check_first(tmp->data[0]) == E_PIPE)
			check = is_pipe(tmp);
		else if (check_first(tmp->data[0]) == E_OPTION)
			check = is_option(tmp, info);
		else if (check_first(tmp->data[0]) == E_OPER)
			check = is_oper(tmp);
		if (check == -1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	organize_token(t_token *token)
{
	t_token	*tmp;
	t_token	*temp;
	char	*join;

	tmp = token;
	while (tmp != NULL)
	{
		join = NULL;
		temp = NULL;
		if (tmp->type == E_TYPE_PARAM || tmp->type == E_TYPE_OPTION)
		{
			while (tmp->next != NULL
				&& (tmp->next->type == E_TYPE_PARAM
					|| tmp->next->type == E_TYPE_OPTION))
			{
				join = ft_strjoin(tmp->data, tmp->next->data);
				temp = tmp->next->next;
				free(tmp->data);
				tmp->data = join;
				delete_token(tmp->next);
				tmp->next = temp;
			}
		}
		tmp = tmp->next;
	}
}

void	delete_token(t_token *token)
{
	free(token->data);
	free(token);
}
