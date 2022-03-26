/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:07:17 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/23 18:21:33 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(char *cmd, char **env, char *str)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], str, ft_strlen(str)) == 0)
		i++;
	paths = ft_split(env[i] + ft_strlen(str), ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	put_error(char *str1, char *str2, char *str3, int exit_code)
{
	g_exit_cod = exit_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	write(2, ": ", 2);
	if (str2)
	{
		ft_putstr_fd(str2, 2);
		write(2, ": ", 2);
	}
	ft_putstr_fd(str3, 2);
	write(2, "\n", 1);
}

void	exec(t_point *p, char **env, t_cmd *cmd)
{
	char	*path;

	(void)env;
	path = get_path(cmd->cmd_arg[0], p->env, "PATH=");
	if (path == 0)
		path = get_path(cmd->cmd_arg[0], p->env, "PWD=");
	if ((execve(path, cmd->cmd_arg, p->env)) == -1)
	{
		put_error(cmd->cmd_arg[0], NULL, "command not found", 127);
		exit(127);
	}
}
