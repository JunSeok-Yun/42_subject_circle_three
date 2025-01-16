/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:02:43 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/24 21:57:47 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_exp_token(t_env_token *head, char *data);
int		keylen(char *data);
int		valuelen(char *data);
void	input_data(t_env_token *new, char *data);

t_env_token	*exp_tokenize(char **envp)
{
	t_env_token	*head;
	int			i;

	head = (t_env_token *)malloc(sizeof(t_env_token) * 1);
	head->env_data = (char *)malloc(sizeof(char) * (ft_strlen(envp[0]) + 1));
	head->env_key = (char *)malloc(sizeof(char) * keylen(envp[0]));
	head->env_value = (char *)malloc(sizeof(char) * valuelen(envp[0]));
	if (head == NULL || head->env_key == NULL || head->env_value == NULL
		|| head->env_data == NULL)
		return (NULL);
	head->next = NULL;
	input_data(head, envp[0]);
	input_env_data(head, envp[0]);
	i = 1;
	while (envp[i] != NULL)
	{
		if (make_exp_token(head, envp[i]))
			return (NULL);
		++i;
	}
	return (head);
}

int	make_exp_token(t_env_token *head, char *data)
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
	new->env_key = (char *)malloc(sizeof(char) * keylen(data));
	new->env_value = (char *)malloc(sizeof(char) * valuelen(data));
	new->env_data = (char *)malloc(sizeof(char) * (ft_strlen(data) + 1));
	if (new->env_key == NULL || new->env_value == NULL)
		return (1);
	input_env_data(new, data);
	input_data(new, data);
	tmp->next = new;
	return (0);
}

int	keylen(char *data)
{
	int	i;

	if (data == NULL)
		return (0);
	i = 0;
	while (data[i] != '=')
		++i;
	return (i + 1);
}

int	valuelen(char *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data == NULL)
		return (0);
	while (data[i] != '=')
		++i;
	while (data[i] != '\0')
	{
		++i;
		++j;
	}
	return (j + 1);
}

void	input_data(t_env_token *new, char *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i] != '=')
	{
		new->env_key[j] = data[i];
		++i;
		++j;
	}
	new->env_key[j] = '\0';
	i = i + 1;
	j = 0;
	while (data[i] != '\0')
	{
		new->env_value[j] = data[i];
		++i;
		++j;
	}
	new->env_value[j] = '\0';
	return ;
}
