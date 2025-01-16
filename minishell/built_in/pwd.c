/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:15:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/30 18:59:22 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	cmd_cd(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (check_token_size(temp) == 1 && temp->type == E_TYPE_CMD)
		execute_cd_cmd(info);
	else if (check_token_size(temp) == 3 && cd_validation(temp) == 0)
		execute_double_hypen(temp, info);
	else if (check_token_size(temp) == 3 && cd_validation(temp) == -1)
		print_cd_error(temp->next->next->data, 2);
	else if (check_token_size(temp) >= 3)
		print_cd_error("too many arguments", 4);
	else if (check_token_size(temp) == 2 \
	&& (cd_validation(temp) == 0 || (!(ft_strcmp(temp->next->next->data, "-")) \
	|| !(ft_strcmp(temp->next->next->data, "~")))))
		execute_size_two(temp, info);
	else if (check_token_size(temp) >= 2 \
	&& temp->next->next->type == E_TYPE_OPTION \
	&& cd_validation(temp) == -1)
		print_cd_error(temp->next->next->data, 2);
	else if (check_token_size(temp) == 2)
		execute_normal_cd(temp->next->next->data, info);
	return (0);
}

void	execute_cd_cmd(t_info *info)
{
	char	*find;

	find = find_value(info, "HOME");
	if (find_key(info->exp, "HOME") == 0)
		print_cd_error("HOME", 3);
	else if (find_key(info->exp, "HOME") == 1)
	{
		if (chdir(find) != 0)
			print_cd_error(find, 1);
		else
			update_pwd(info);
	}
	free(find);
}

int	find_key(t_env_token *list, char *find)
{
	t_env_token	*temp;
	int			len;

	temp = list;
	while (temp != NULL)
	{
		len = ft_strlen(temp->env_key);
		if (ft_strncmp(temp->env_key, find, len) == 0)
			return (1);
		temp = temp -> next;
	}
	return (0);
}

char	*find_value(t_info *info, char *find)
{
	t_env_token	*temp;
	char		*value;

	temp = info->exp;
	value = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->env_key, find) == 0)
		{
			value = ft_strdup(temp->env_value);
			return (value);
		}
		temp = temp -> next;
	}
	return (value);
}
