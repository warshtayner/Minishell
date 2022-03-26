/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:41:18 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/26 16:09:16 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	correct_cmd_arg(t_cmd **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->cmd_arg[i])
		i++;
	(*cmd)->next->cmd_arg = malloc(i + 1);
	i = -1;
	while ((*cmd)->cmd_arg[++i])
		(*cmd)->next->cmd_arg[i] = ft_strdup((*cmd)->cmd_arg[i]);
	(*cmd)->next->cmd_arg[i] = 0;
}

void	start_heredoc(t_point *p, char **env, t_cmd *cmd)
{
	t_list	*tmp;

	pipe(cmd->fd);
	dup2(cmd->fd[0], cmd->fdin);
	tmp = p->heredoc_list;
	while (tmp)
	{
		write(cmd->fd[1], tmp->content, ft_strlen(tmp->content) + 1);
		write(cmd->fd[1], "\n", 1);
		tmp = tmp->next;
	}
	close(cmd->fd[1]);
	find_built(p, env, cmd);
}

void	read_until_delimiter(t_point *p, char **env, t_cmd *cmd)
{
	char	*str;

	if ((cmd->next && cmd->next->control_icon
			&& !ft_strncmp(cmd->next->control_icon, "|", 1)) || !cmd->next)
	{
		while (1)
		{
			str = readline("> ");
			if (!str || !ft_strncmp(str, p->cmd->file_name,
					ft_strlen(p->cmd->file_name) + 1))
				break ;
			ft_lstadd_back(&p->heredoc_list, ft_lstnew(str));
		}
		start_heredoc(p, env, cmd);
	}
}

void	check_control_icon(t_point *p, char **env, t_cmd *cmd)
{
	if (cmd->control_icon && cmd->next && !*cmd->next->cmd_arg
		&& ft_strncmp(cmd->next->control_icon, "|", 2))
		correct_cmd_arg(&cmd);
	if (cmd->control_icon && !ft_strncmp(cmd->control_icon, "|", 2))
		create_pipe(p, env, cmd);
	else if (cmd->control_icon && !ft_strncmp(cmd->control_icon, ">>", 3))
		redir_output_add(p, env, cmd);
	else if (cmd->control_icon && !ft_strncmp(cmd->control_icon, ">", 2))
		redir_output(p, env, cmd);
	else if (cmd->control_icon && !ft_strncmp(cmd->control_icon, "<<", 3))
		read_until_delimiter(p, env, cmd);
	else if (cmd->control_icon && !ft_strncmp(cmd->control_icon, "<", 2))
		redir_input(p, env, cmd);
	else
		find_built(p, env, cmd);
}

void	execute(t_point *p, char **env)
{
	t_cmd	*cmd;
	int		fd_in;

	cmd = p->cmd;
	while (cmd)
	{
		check_control_icon(p, env, cmd);
		cmd = cmd->next;
	}
	close(STDIN);
	fd_in = open("/dev/tty", O_RDONLY | O_NDELAY);
	dup2(fd_in, STDIN);
}
