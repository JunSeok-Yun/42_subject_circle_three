/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tokenize2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:18:24 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/24 21:58:07 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_env_token(t_env_token *head, char *data);
void	input_env_data(t_env_token *new, char *data);

t_env_token	*env_tokenize(char **envp)
{
	t_env_token	*head;
	int			i;

	head = (t_env_token *)malloc(sizeof(t_env_token) * 1);
	head->env_data = (char *)malloc(sizeof(char) * ft_strlen(envp[0]) + 1);
	head->env_key = NULL;
	head->env_value = NULL;
	if (head == NULL || head->env_data == NULL)
		return (NULL);
	head->next = NULL;
	input_env_data(head, envp[0]);
	i = 1;
	while (envp[i] != NULL)
	{
		if (make_env_token(head, envp[i]))
			return (NULL);
		++i;
	}
	return (head);
}

int	make_env_token(t_env_token *head, char *data)
{
	t_env_token	*tmp;
	t_env_token	*new;

	new = (t_env_token *)malloc(sizeof(t_env_token) * 1);
	if (new == NULL)
		return (1);
	new->next = NULL;
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->env_key = NULL;
	new->env_value = NULL;
	new->env_data = (char *)malloc(sizeof(char) * (ft_strlen(data) + 1));
	if (new->env_data == NULL)
		return (1);
	input_env_data(new, data);
	tmp->next = new;
	return (0);
}

void	input_env_data(t_env_token *new, char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		new->env_data[i] = data[i];
		++i;
	}
	new->env_data[i] = '\0';
	return ;
}
