/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:33:09 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 05:08:46 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	return_if(t_token *temp)
{
	if ((ft_strlen(temp->data) == 1 && ft_strcmp(temp->data, "-") == 0) \
	|| (ft_strlen(temp->data) == 2 && ft_strcmp(temp->data, "..") == 0))
		return (1);
	else if (ft_strlen(temp->data) == 1 && ft_strcmp(temp->data, ".") == 0)
		return (2);
	else if (ft_strlen(temp->data) == 2 && ft_strcmp(temp->data, "--") == 0)
		return (0);
	else if ((ft_strlen(temp->data) == 1 && ft_strcmp(temp->data, "-") != 0) \
	|| (ft_strlen(temp->data) == 2 && ft_strcmp(temp->data, "--") != 0))
		return (-1);
	return (0);
}

int	cd_validation(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_OPTION)
		{
			if (ft_strlen(temp->data) > 2)
				return (-1);
			else
				return (return_if(temp));
		}
		temp = temp -> next;
	}
	return (0);
}

void	execute_tilde(t_info *info)
{
	char	*find;

	find = find_value(info, "HOME");
	if (find_key(info->exp, "HOME") == 1)
	{
		if (chdir(find) != 0)
			print_cd_error(find, 1);
		else
			update_pwd(info);
	}
	else if (find_key(info->exp, "HOME") == 0)
	{
		if (chdir(info->home) != 0)
			print_cd_error(info->home, 1);
		else
			update_pwd(info);
	}
	free(find);
}

void	execute_single_hypen(t_info *info)
{
	char	*temp;

	if (info->oldpwd == NULL)
	{
		print_cd_error("OLDPWD", 3);
		return ;
	}
	temp = ft_strdup(info->oldpwd);
	if (chdir(temp) != 0)
	{
		print_cd_error(temp, 1);
		return ;
	}
	else
		printf("%s\n", temp);
	free(temp);
	update_pwd(info);
}

void	execute_double_hypen(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_PARAM)
		{
			if (chdir(temp->data) != 0)
				print_cd_error(temp->data, 1);
			else
				update_pwd(info);
		}
		temp = temp->next;
	}
}
