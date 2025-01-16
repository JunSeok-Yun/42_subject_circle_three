/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:08:23 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:58:55 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_size_two(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_OPTION)
		{
			if (ft_strncmp(temp->data, "--", 2) == 0)
				execute_tilde(info);
			else if (ft_strncmp(temp->data, "-", ft_strlen(temp->data)) == 0)
				execute_single_hypen(info);
			else if (ft_strncmp(temp->data, "-", ft_strlen(temp->data)) != 0)
				print_cd_error(temp->data, 2);
			break ;
		}
		else if (temp->type == E_TYPE_PARAM \
		&& ft_strncmp(temp->data, "~", ft_strlen(temp->data)) == 0)
		{
			execute_tilde(info);
			break ;
		}
		else
			chdir(temp->data);
		temp = temp -> next;
	}
}
