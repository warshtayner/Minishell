/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:07:45 by                   #+#    #+#             */
/*   Updated: 2022/01/26 14:58:27 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <term.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2

int	g_exit_cod;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;

}	t_list;

typedef struct s_cmd
{
	char			**cmd_arg;
	char			*control_icon;
	char			*file_name;
	int				fdin;
	int				fdout;
	int				fd[2];
	pid_t			pid;
	struct s_cmd	*next;

}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}	t_env;

typedef struct s_point
{
	char	**env;
	t_cmd	*cmd;
	t_env	*env_list;
	t_list	*heredoc_list;

}	t_point;

/*
 * from libft
 * */
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);

/*
 * list cmd
 * */
void	free_cmd(t_point *p);
t_cmd	*lst_last(t_cmd *lst);
t_cmd	*lst_new(char **cmd, char *icon);
void	lst_add_back(t_cmd **lst, t_cmd *new);

/*
 * list env
 * */
void	free_env(t_env **env);
void	parsing_env(t_point *p);
t_env	*lst_last_env(t_env *lst);
t_env	*lst_new_env(char *key, char *value);
void	lst_add_back_env(t_env **lst, t_env *new);

/*
 * Other parsing
 * */
int		dollar_len_question(void);
int		split_char(char c);
int		ft_count_arg(char *str);
int		ft_len_arg(char *str, t_env *env);
char	**cmd_split(char *str, t_point	*p);
int		parsing_cmd(char *input, t_point *p);
int		check_flag(char *str, int i, int *flag);
void	set_redirect(char *input, int *i, t_point *p);
void	set_arg(char **res, char **str, int i, t_env *env);
int		dollar_len_value(char *str, int *i, int *flag, t_env *env);
int		dollar_get_value(char **res, char **str, int *j, t_env *env);

/*
 * Libft
 * */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);

/*
 * Execute
 * */
void	execute(t_point *p, char **env);
void	find_built(t_point *p, char **env, t_cmd *cmd);
t_env	*find_value_env(char *key, t_env **env);
void	shell_commands(t_point *p, char **env, t_cmd *cmd);
void	exec(t_point *p, char **env, t_cmd *cmd);
void	command_not_found(char *cmd);
char	*get_path(char *cmd, char **env, char *str);
void	check_signals(void);
void	free_char_env(t_point *p);
void	update_char_env(t_point *p);
void	create_char_env(t_point *p, int size, char **env);
void	find_built(t_point *p, char **env, t_cmd *cmd);
void	redir_input(t_point *p, char **env, t_cmd *cmd);
void	redir_output_add(t_point *p, char **env, t_cmd *cmd);
void	redir_output(t_point *p, char **env, t_cmd *cmd);
void	put_error(char *str1, char *str2, char *str3, int exit_code);

/*
 * Builts
 * */
void	pwd_built(void);
void	exit_built(t_point *p);
void	cd_built(t_point *p);
void	env_built(t_env *env);
void	cut_pwd(t_env *current);
int		cut_begin_path(char **path, t_point *p);
char	*get_absolute_from_relative(t_point *p, char *path);
void	print_no_such(t_point *p);
void	export_built(t_point *p);
int		check_sort_env(t_env **env);
void	print_copy(t_env **env);
void	copy_env(t_env **env, t_env **copy);
void	swap_env(t_env *elem1, t_env *elem2);
void	sort_copy_env(t_env **env);
void	unset_built(t_point *p);
void	echo_built(t_cmd *cmd);

/*
 * Pipe
 * */
void	create_pipe(t_point *p, char **env, t_cmd *cmd);

/*
 * Readline
 * */
void	rl_replace_line(const char *buffer, int val);

#endif