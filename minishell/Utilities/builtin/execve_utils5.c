/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:04:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 06:19:46 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*move_next_cmd(t_token *token)
{
	while (token && token->type != E_TYPE_PIPE)
		token = token->next;
	if (token && token->type == E_TYPE_PIPE)
		token = token->next;
	return (skip_non_command_tokens(token));
}

char	**make_argv(t_token *token)
{
	return (create_argv_array(count_argv(token), token));
}

int	count_argv(t_token *token)
{
	int		cnt;
	t_token	*cur;

	cnt = 0;
	cur = token;
	while (cur && cur->type != E_TYPE_PIPE)
	{
		if (is_argv_token(cur->type))
			cnt++;
		cur = cur -> next;
	}
	return (cnt);
}

char	**create_argv_array(int cnt, t_token *token)
{
	char	**arg;
	int		i;
	t_token	*cur;

	arg = malloc(sizeof(char *) * (cnt + 1));
	if (!arg)
		return (NULL);
	i = 0;
	cur = token;
	while (cur && cur->type != E_TYPE_PIPE)
	{
		if (is_argv_token(cur->type))
		{
			arg[i] = ft_strdup(cur->data);
			if (argv_array_free(arg, i))
				return (NULL);
			i++;
		}
		cur = cur -> next;
	}
	arg[i] = NULL;
	return (arg);
}

int	argv_array_free(char **argv, int i)
{
	if (!argv[i])
	{
		while (--i >= 0)
			free(argv[i]);
		free(argv);
		return (1);
	}
	return (0);
}
