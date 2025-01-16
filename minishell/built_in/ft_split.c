/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 01:07:08 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/24 01:07:16 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_word(const char *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s != 0)
	{
		if (!(check_sep(*s, c)))
		{
			cnt++;
			while (*s != 0 && !(check_sep(*s, c)))
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

static char	*word_strdup(char const *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	while (str[len] && !(check_sep(str[len], c)))
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(new_str))
		return (0);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	**ft_split(char const *s, char c)
{
	int		word_cnt;
	int		i;
	char	**res;

	word_cnt = count_word(s, c);
	res = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!(res))
		return (0);
	i = 0;
	while (*s != 0)
	{
		if (!(check_sep(*s, c)))
		{
			res[i++] = word_strdup(s, c);
			while (!(check_sep(*s, c)) && *s != 0)
				s++;
		}
		else
			s++;
	}
	res[i] = 0;
	return (res);
}
