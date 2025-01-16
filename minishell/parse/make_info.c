/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:04:27 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/30 18:49:54 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_info(t_env_token *exp, char *type);
void	init_qustion_mark(t_info *info);

t_info	*make_info(char **envp)
{
	t_info		*info;

	info = (t_info *)malloc(sizeof(t_info) * 1);
	if (info == NULL)
		return (NULL);
	info->env = env_tokenize(envp);
	info->exp = exp_tokenize(envp);
	info->home = init_info(info->exp, "HOME");
	info->pwd = init_info(info->exp, "PWD");
	info->oldpwd = init_info(info->exp, "OLDPWD");
	if (!info->env || !info->exp || !info->home || !info->pwd || !info->oldpwd)
		return (NULL);
	info->paths = NULL;
	info->cmd = NULL;
	info->cmd_lines = NULL;
	info->cmd_paths = NULL;
	info->head = NULL;
	info->pipes = 0;
	info->pids = 0;
	info->pipe_cnt = 0;
	init_qustion_mark(info);
	return (info);
}

char	*init_info(t_env_token *exp, char *type)
{
	t_env_token	*tmp;
	char		*sol;

	tmp = exp;
	while (tmp != NULL)
	{
		if (ft_strcmp(type, tmp->env_key) == 0)
		{
			sol = ft_strdup(tmp->env_value);
			return (sol);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	init_qustion_mark(t_info *info)
{
	t_env_token	*temp;
	t_env_token	*tmp;

	temp = info->exp;
	tmp = (t_env_token *)malloc(sizeof(t_env_token) * 1);
	tmp->env_data = NULL;
	tmp->env_key = (char *)malloc(sizeof(char) * 2);
	tmp->env_key[0] = '?';
	tmp->env_key[1] = '\0';
	tmp->env_value = (char *)malloc(sizeof(char) * 2);
	tmp->env_value[0] = 48;
	tmp->env_value[1] = '\0';
	tmp->next = NULL;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = tmp;
	return ;
}
