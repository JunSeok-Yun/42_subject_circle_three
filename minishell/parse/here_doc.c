/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:42:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/31 02:31:53 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		eof_check(t_token *token, char *eof, char *param);
int		pipe_parse(t_token *token, t_info *info);
char	*make_file_name(char *file_name);
void	child_process(t_token *token, t_info *info);

int	pipe_parse(t_token *token, t_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		signal(SIGINT, sig_handler_child);
		child_process(token, info);
		return (1);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		g_dj = WEXITSTATUS(status);
		init_exit_code(info);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler_pa);
		return (0);
	}
	return (0);
}

void	child_process(t_token *token, t_info *info)
{
	char	*param;
	char	*eof;

	eof = ft_strdup(token->data);
	while (1)
	{
		param = readline("heredoc>");
		if (param == NULL)
			break ;
		if (param[0] == '\0')
			continue ;
		if (eof_check(token, eof, param))
			return ;
		substitution(token, info, NULL);
		write(token->fd, token->data, ft_strlen(token->data));
		write(token->fd, "\n", 1);
		free(param);
	}
	free(eof);
	free(param);
	return ;
}

int	eof_check(t_token *token, char *eof, char *param)
{
	if (ft_strcmp(eof, param) == 0)
	{
		free(eof);
		free(param);
		return (1);
	}
	free(token->data);
	token->data = ft_strdup(param);
	return (0);
}

char	*make_file_name(char *file_name)
{
	int		num;
	char	*tmp;

	if (file_name == NULL)
	{
		tmp = ft_itoa(100);
		return (tmp);
	}
	num = ft_atoi(file_name);
	num = num + 1;
	tmp = ft_itoa(num);
	free(file_name);
	return (tmp);
}

int	here_doc(t_token *head, t_token *token, t_info *info)
{
	char	*file_name;

	file_name = NULL;
	while (token->fd == -1)
	{
		file_name = make_file_name(file_name);
		token->fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, 0777);
	}
	if (pipe_parse(token, info))
	{
		free(file_name);
		free_all(head, info);
		exit(0);
	}
	close(token->fd);
	token->fd = open(file_name, O_RDWR | O_APPEND, 0777);
	free(token->data);
	token->data = file_name;
	return (0);
}
