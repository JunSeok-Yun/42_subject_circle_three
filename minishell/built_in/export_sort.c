/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:17:58 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/21 23:48:45 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_len(char *s1, char *s2)
{
	if (ft_strlen(s1) <= ft_strlen(s2))
		return (ft_strlen(s2));
	else
		return (ft_strlen(s1));
}

int	exp_strncmp(char *s1, char *s2, int n)
{
	int		i;
	int		val;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	val = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (val < 0)
		return (1);
	else
		return (0);
}

void	swap_node(t_env_token *cmp1, t_env_token *cmp2)
{
	char	*temp;

	temp = cmp1->env_data;
	cmp1->env_data = cmp2->env_data;
	cmp2->env_data = temp;
	temp = cmp1->env_key;
	cmp1->env_key = cmp2->env_key;
	cmp2->env_key = temp;
	temp = cmp1->env_value;
	cmp1->env_value = cmp2->env_value;
	cmp2->env_value = temp;
}

void	exp_bubble_sort(t_env_token *node)
{
	t_env_token	*cmp_node_1;
	t_env_token	*cmp_node_2;
	int			len;

	cmp_node_1 = node;
	while (cmp_node_1->next != NULL)
	{
		cmp_node_2 = cmp_node_1 -> next;
		while (cmp_node_2 != NULL)
		{
			len = cmp_len(cmp_node_1->env_key, cmp_node_2->env_key);
			if (exp_strncmp(cmp_node_2->env_key, cmp_node_1->env_key, len))
				swap_node(cmp_node_1, cmp_node_2);
			cmp_node_2 = cmp_node_2 -> next;
		}
		cmp_node_1 = cmp_node_1 -> next;
	}
}
