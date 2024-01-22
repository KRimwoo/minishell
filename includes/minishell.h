/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:55:31 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 18:39:32 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <string.h>

int	g_termination_status;

typedef enum e_token_type
{
	WORD,
	ARGV,
	PIPE,
	REDIR,
	SPACING
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*type;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	int				pipe[2];
}					t_cmd;

typedef struct s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
}					t_envlst;

typedef struct s_info
{
	int				stdin;
	int				stdout;
	int				syntax_error;
	struct termios	ms_termios;
	t_envlst		*env_list;
	char			**path_list;
}	t_info;

// reading
char		*read_input(void);

// token_utils
t_token		*new_token(char *str, int type);
void		add_token(t_token **token, char *str, int type);
t_token		*delete_token(t_token **head, t_token *target);
void		free_tokens(t_token *head);

// env_utils
t_envlst	*new_envlst(char *key, char *value);
void		add_envlst(t_envlst **head, t_envlst *new);
t_envlst	*create_env_node(char *envp);
void		init_envlst(t_envlst **head, char *envp[]);
void		get_path_list(t_info **info);
char		*get_envval(t_envlst *head, char *key);
void		free_envlst(t_envlst *head);

/* option : execution */

// builtin
int			mini_cd(t_info *info, char **av);
int			mini_echo(char **av);
int			mini_env(t_envlst *envlst);
int			mini_exit(t_info *info, t_cmd *cmd_list);
int			mini_export(t_info *info, char **av);
int			mini_pwd(void);
int			mini_unset(t_info *info, char **av);

// cmd_list
void		free_cmd_list(t_cmd **cmd_list);

// execution
void		execute_another_cmd(t_info *info, t_cmd *cmd_list);
int			apply_redirections(t_cmd *cmd_list, int cnt);
void		execute_heredoc(t_info *info, t_cmd *cmd_list);
void		execute_another_cmd(t_info *info, t_cmd *cmd_list);
void		execute_single_cmd(t_info *info, t_cmd *cmd_list);

// utils.c
void		mini_error(char *str1, char *str2);
void		free_all(char **arr);
void		free_all_str(char *str1, char *str2, char *str3, char *str4);
void		unlink_heredoc_files(t_cmd *cmd_list);
char		*find_execute_path(char *cmd, char **path_list);
void		handle_command_not_found_error(char **path_list, char *str);
int			check_builtin(t_info *info, t_cmd *cmd_list, int cnt);
void		mini_execution(t_info *info, t_cmd *cmd_list);
char		**env_list_to_envp(t_envlst *env_list);

// parsing
// lexical
t_token		*do_lexical(t_info *info, char *line);

// heredoc
void		check_heredoc(t_info *info, t_token *tokens);

// quotation
void		check_quotation(t_info *info, t_token *token);

//split_quotation
char		**split_quotation(t_info *info, char *str);
int			find_env_idx(char *str, int *start, int *end);

// parsing_utils
int			is_separator(char c);
t_redir		*new_redir(t_token *tokens);
t_cmd		*new_cmd(void);

// env
void		check_env(t_info *info, t_token *token);

// split_env
char		**split_env(t_info *info, char *str);

// delimiter
void		parse_by_delimiter(t_token *tokens);

// syntax
int			do_syntax(t_token *tokens);

// parse cmds
t_cmd		*parse_cmds(t_token *tokens);

// signal
void		setting_signal(void);
void		sighandler_default(int signum);
void		sighandler_quit(int signum);
void		sighandler_heredoc(int signum);

void		term_print_on(t_info *info);
void		term_print_off(t_info *info);

// // parsing test
// void	print_tokens(t_token *tokens);
// void	print_envplst(t_envlst *head);
// void	print_path_list(char **list);
void		print_cmds(t_cmd *cmds);

#endif
