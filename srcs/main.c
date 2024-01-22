/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:35:03 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 17:36:30 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_pwd(t_info *info)
{
	char	**pwd;
	int		i;

	i = 0;
	pwd = (char **)malloc(sizeof(char *) * 3);
	if (!pwd)
		return ;
	pwd[0] = ft_strdup("");
	pwd[1] = ft_strdup("OLDPWD");
	pwd[2] = NULL;
	(void)info;
	mini_unset(info, pwd);
	mini_export(info, pwd);
	while (pwd[i])
	{
		if (pwd[i])
			free(pwd[i]);
		i++;
	}
	free(pwd);
}

static void	info_init(t_info *info, char **envp)
{
	init_envlst(&info->env_list, envp);
	get_path_list(&info);
	info->stdin = dup(STDIN_FILENO);
	info->stdout = dup(STDOUT_FILENO);
	term_print_off(info);
	update_pwd(info);
}

static void	parse_line(t_info *info, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	info->syntax_error = 0;
	tokens = do_lexical(info, line);
	cmds = NULL;
	if (!info->syntax_error)
		info->syntax_error = do_syntax(tokens);
	if (!info->syntax_error && tokens)
		cmds = parse_cmds(tokens);
	free_tokens(tokens);
	if (cmds)
	{
		mini_execution(info, cmds);
		free_cmd_list(&cmds);
	}
}

char	*read_input(void)
{
	char	*line;

	line = readline("⊹ﾟ\033[36m✦𓂋 minishell𓂋 ✦\033[0mﾟ⊹$ ");
	add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_info		info;

	info_init(&info, envp);
	(void)argc;
	(void)argv;
	while (42)
	{
		setting_signal();
		line = read_input();
		if (!line)
		{
			mini_exit(&info, NULL);
			break ;
		}
		else if (line[0] != '\0')
		{
			parse_line(&info, line);
		}
		free(line);
	}
	return (0);
}
