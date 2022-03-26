/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:41:18 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/26 16:09:16 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_command(t_point *p, char **env, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd_arg[0], "pwd", 4))
		pwd_built();
	else if (!ft_strncmp(cmd->cmd_arg[0], "env", 4))
		env_built(p->env_list);
	else if (!ft_strncmp(cmd->cmd_arg[0], "export", 7) && !cmd->cmd_arg[1])
		export_built(p);
	else if (!ft_strncmp(cmd->cmd_arg[0], "echo", 5)
		&& (!cmd->cmd_arg[1] || !ft_strncmp(cmd->cmd_arg[1], "-n", 3)))
		echo_built(cmd);
	else
		exec(p, env, cmd);
}

void	find_built_with_fork(t_point *p, char **env, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		dup2(cmd->fdout, STDOUT_FILENO);
		exec_command(p, env, cmd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_exit_cod = WEXITSTATUS(status);
	}
}

void	find_built(t_point *p, char **env, t_cmd *cmd)
{
	if (*cmd->cmd_arg)
	{
		if (ft_strnstr(cmd->cmd_arg[0], "exit", 4))
			exit_built(p);
		else if (ft_strnstr(cmd->cmd_arg[0], "cd", 2))
			cd_built(p);
		else if (ft_strnstr(cmd->cmd_arg[0], "unset", 5))
			unset_built(p);
		else if (ft_strnstr(cmd->cmd_arg[0], "export", 6)
			&& cmd->cmd_arg[1])
			export_built(p);
		else
			find_built_with_fork(p, env, cmd);
	}
}
