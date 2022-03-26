/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:41:18 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/26 16:09:16 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir_input(t_point *p, char **env, t_cmd *cmd)
{
	if (!*cmd->cmd_arg && cmd->next && !cmd->next->control_icon)
	{
		cmd->next->control_icon = ft_strdup(cmd->control_icon);
		cmd->next->file_name = ft_strdup(cmd->file_name);
	}
	else if (!*cmd->cmd_arg && cmd->next
		&& !ft_strncmp(cmd->next->control_icon, "|", 1))
		cmd->next->fdin = open(cmd->file_name, O_RDONLY);
	else
		cmd->fdin = open(cmd->file_name, O_RDONLY);
	if (cmd->fdin == -1 || cmd->next->fdin == -1)
	{
		put_error(cmd->file_name, NULL, "No such file or directory", 1);
		return ;
	}
	if ((cmd->next && !ft_strncmp(cmd->next->control_icon, "|", 1))
		|| !cmd->next)
	{
		find_built(p, env, cmd);
		close(cmd->fdin);
	}
}

void	redir_output_add(t_point *p, char **env, t_cmd *cmd)
{
	if (!*cmd->cmd_arg && cmd->next && !cmd->next->control_icon)
	{
		cmd->next->control_icon = ft_strdup(cmd->control_icon);
		cmd->next->file_name = ft_strdup(cmd->file_name);
	}
	else
		cmd->fdout = open(cmd->file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if ((cmd->next && !ft_strncmp(cmd->next->control_icon, "|", 1))
		|| !cmd->next)
		find_built(p, env, cmd);
}

void	redir_output(t_point *p, char **env, t_cmd *cmd)
{
	if (!*cmd->cmd_arg && cmd->next && !cmd->next->control_icon)
	{
		cmd->next->control_icon = ft_strdup(cmd->control_icon);
		cmd->next->file_name = ft_strdup(cmd->file_name);
	}
	else
		cmd->fdout = open(cmd->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if ((cmd->next && !ft_strncmp(cmd->next->control_icon, "|", 1))
		|| !cmd->next)
		find_built(p, env, cmd);
}
