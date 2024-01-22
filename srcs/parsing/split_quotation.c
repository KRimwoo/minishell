/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:09:54 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:58:30 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*joining_partials(char **partials)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(partials[0]);
	tmp = res;
	res = ft_strjoin(tmp, partials[1]);
	free(tmp);
	tmp = res;
	res = ft_strjoin(tmp, partials[2]);
	free(tmp);
	free(partials[0]);
	free(partials[1]);
	free(partials[2]);
	return (res);
}

int	find_env_idx(char *str, int *start, int *end)
{
	*start = 0;
	while (str[*start] && str[*start] != '$')
		(*start)++;
	if (str[*start] == '\0')
		return (0);
	*end = *start + 1;
	if (str[*end] == '?' || ft_isdigit(str[*end])
		|| (!ft_isalnum(str[*end]) && str[*end] != '_'))
	{
		(*end)++;
		return (1);
	}
	if (str[*end] == '\0' || (!ft_isalnum(str[*end]) && str[*end] != '_'))
		return (0);
	while (str[*end] && (ft_isalnum(str[*end]) || str[*end] == '_'))
		(*end)++;
	return (1);
}

char	*convert_env(t_info *info, char *str)
{
	char	*partials[3];
	int		start;
	int		end;

	while (find_env_idx(str, &start, &end))
	{
		partials[0] = ft_substr(str, 0, start);
		if (str[start + 1] == '?')
		{
			end = start + 2;
			partials[1] = ft_itoa(g_termination_status);
		}
		else
		{
			partials[1] = ft_substr(str, start + 1, end - start - 1);
			partials[1] = get_envval(info->env_list, partials[1]);
		}
		partials[2] = ft_substr(str, end, ft_strlen(str) - end);
		free(str);
		str = joining_partials(partials);
	}
	return (str);
}

int	find_quote_idx(t_info *info, char *str, int *start, int *end)
{
	*start = 0;
	while (str[*start] && str[*start] != '\"' && str[*start] != '\'')
		(*start)++;
	if (str[*start] == '\0')
		return (0);
	*end = *start + 1;
	while (str[*end] && str[*end] != str[*start])
		(*end)++;
	if (str[*end] == '\0')
	{
		mini_error("quotation error\n", NULL);
		info->syntax_error = 1;
		return (0);
	}
	return (1);
}

char	**split_quotation(t_info *info, char *str)
{
	char	**res;
	int		start;
	int		end;

	if (!find_quote_idx(info, str, &start, &end))
		return (NULL);
	res = malloc(sizeof(char *) * 4);
	if (!res)
		return (NULL);
	if (start > 0 && str[start - 1] == '$')
		res[0] = ft_substr(str, 0, start - 1);
	else
		res[0] = ft_substr(str, 0, start);
	res[1] = ft_substr(str, start + 1, end - start - 1);
	if (str[start] == '\"')
		res[1] = convert_env(info, res[1]);
	res[2] = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	res[3] = 0;
	return (res);
}
