/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 02:16:30 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_dj;
int		input(t_info *info);
void	print_type(t_token *token);

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	if (ac != 1 || av[1] != NULL)
		return (print_error(1));
	signal(SIGQUIT, SIG_IGN);
	info = make_info(envp);
	if (info == NULL)
		return (print_error(1));
	if (input(info))
		return (print_error(1));
	free_info(info);
	return (0);
}

int	input(t_info *info)
{
	t_token	*token;
	char	*param;

	token = NULL;
	while (1)
	{
		signal(SIGINT, sig_handler_pa);
		param = readline("DJ_Shell>");
		if (param == NULL)
			break ;
		if (param[0] == '\0')
			continue ;
		else
		{
			add_history(param);
			token = tokenize(param, info);
			if (token == NULL)
				continue ;
			built_in(token, info);
		}
		free_token(token);
	}
	return (0);
}
