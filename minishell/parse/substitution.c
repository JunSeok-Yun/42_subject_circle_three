/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 04:41:23 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value_parse(char *key, t_info *info);
char	*make_head(char *data);
char	*make_key(char *data);
char	*make_tail(char *data);

void	substitution(t_token *token, t_info *info, char *tmp)
{
	char	*head;
	char	*tail;
	char	*value;

	while (check_env_var(token->data))
	{
		head = make_head(token->data);
		value = find_value_parse(make_key(token->data), info);
		tail = make_tail(token->data);
		if (head == NULL && value == NULL && tail == NULL)
		{
			free(token->data);
			token->data = (char *)malloc(sizeof(char) * 1);
			token->data[0] = '\0';
			return ;
		}
		tmp = ft_strjoin(head, value);
		free(token->data);
		free(value);
		token->data = ft_strjoin(tmp, tail);
		free(tmp);
		free(tail);
	}
	return ;
}

char	*make_head(char *data)
{
	int		i;
	char	*head;

	i = 0;
	if (data[0] == '$')
		return (NULL);
	while (data[i] != '$' && data[i] != '\0')
		++i;
	if (data[i] == '$')
	{
		head = (char *)malloc(sizeof(char) * (i + 1));
		if (head == NULL)
			return (NULL);
		i = 0;
		while (data[i] != '$')
		{
			head[i] = data[i];
			++i;
		}
		head[i] = '\0';
		return (head);
	}
	return (NULL);
}

char	*make_key(char *data)
{
	int		i;
	int		size;
	char	*key;

	i = 0;
	while (data[i] != '$' && data[i] != '\0')
		++i;
	++i;
	size = jump_current(data, &i);
	key = (char *)malloc(sizeof(char) * (size + 1));
	if (key == NULL)
		return (NULL);
	i = i - size;
	size = 0;
	while (check_current_value(data[i]))
	{
		key[size] = data[i];
		++i;
		++size;
	}
	key[size] = '\0';
	return (key);
}

char	*make_tail(char *data)
{
	int		i;
	int		size;
	char	*tail;

	i = 0;
	while (data[i] != '$')
		++i;
	++i;
	jump_current(data, &i);
	size = tail_size(data, &i);
	if (size == 0)
		return (NULL);
	tail = (char *)malloc(sizeof(char) * (size + 1));
	if (tail == NULL)
		return (NULL);
	i = i - size;
	size = 0;
	while (data[i] != '\0')
	{
		tail[size] = data[i];
		++i;
		++size;
	}
	tail[size] = '\0';
	return (tail);
}

char	*find_value_parse(char *key, t_info *info)
{
	char		*value;
	t_env_token	*tmp;

	if (key == NULL)
		return (NULL);
	tmp = info->exp;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->env_key, key) == 0)
		{
			free(key);
			value = ft_strdup(tmp->env_value);
			return (value);
		}
		tmp = tmp->next;
	}
	free(key);
	return (NULL);
}
