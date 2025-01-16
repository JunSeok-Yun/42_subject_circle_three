/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:09:42 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/19 22:06:19 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	check_h(char const *s, char c);
static size_t	check_v(char const *s, char c, char **sol);
static void		f_all(char **sol, size_t h);
static char		*ft_dupcpy(char const *s, size_t size, size_t i);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	hsize;
	char	**sol;

	i = 0;
	hsize = check_h(s, c);
	sol = (char **)malloc(sizeof(char *) * (hsize + 1));
	if (sol == 0)
		return (0);
	sol[hsize] = 0;
	check_v(s, c, sol);
	while (i < hsize)
	{
		if (sol[i] == 0)
		{
			f_all(sol, hsize);
			return (0);
		}
		++i;
	}
	return (sol);
}

static void	f_all(char **sol, size_t h)
{
	size_t	i;

	i = 0;
	while (i < h)
	{
		free(sol[i]);
		++i;
	}
	free(sol);
}

static	char	*ft_dupcpy(char const *s, size_t size, size_t i)
{
	size_t	j;
	size_t	k;
	char	*sol;

	j = i - size;
	k = 0;
	sol = (char *)malloc(sizeof(char) * (size + 1));
	if (sol == 0)
		return (0);
	while (size > 0)
	{
		sol[k] = s[j];
		++k;
		++j;
		--size;
	}
	sol[k] = '\0';
	return (sol);
}

static size_t	check_v(char const *s, char c, char **sol)
{
	size_t	i;
	size_t	j;
	size_t	vsize;

	i = 0;
	j = 0;
	vsize = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			++i;
		while (s[i] != '\0' && s[i] != c)
		{
			++i;
			++vsize;
		}
		if (vsize > 0)
		{
			sol[j] = ft_dupcpy(s, vsize, i);
			vsize = 0;
			++j;
		}
	}
	return (0);
}

static size_t	check_h(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	hsize;

	i = 0;
	j = 0;
	hsize = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			++i;
		while (s[i] != '\0' && s[i] != c)
		{
			++i;
			++j;
		}
		if (j > 0)
		{
			++hsize;
			j = 0;
		}
	}
	return (hsize);
}
