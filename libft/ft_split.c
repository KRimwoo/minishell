/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:11:15 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/24 17:08:07 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**free_p(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		free(strstr[i++]);
	free(strstr);
	return (0);
}

static int	str_cnt(char *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c)
		{
			cnt++;
			while (*str && *str != c)
				str++;
		}
		else
		{
			while (*str && *str == c)
				str++;
		}
	}
	return (cnt);
}

static int	wordcpy(int word_index, char *str, char c, char **splited_str)
{
	int	word_len;
	int	idx;

	word_len = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	splited_str[word_index] = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!splited_str[word_index])
		return (0);
	idx = 0;
	while (str[idx] && str[idx] != c)
	{
		splited_str[word_index][idx] = str[idx];
		idx++;
	}
	splited_str[word_index][idx] = '\0';
	return (idx);
}

char	**ft_split(char *str, char c)
{
	char	**splited_str;
	int		mv_len;
	int		word_index;

	word_index = 0;
	splited_str = (char **)malloc(sizeof(char *) * (str_cnt(str, c) + 1));
	if (!splited_str)
		return (0);
	while (*str)
	{
		if (*str != c)
		{
			mv_len = wordcpy(word_index, str, c, splited_str);
			if (!mv_len)
				return (free_p(splited_str));
			word_index++;
			str += mv_len;
		}
		while (*str && *str == c)
			str++;
	}
	splited_str[word_index] = 0;
	return (splited_str);
}
