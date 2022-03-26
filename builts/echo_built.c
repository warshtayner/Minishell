/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:25:06 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/21 11:39:25 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo_built(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!ft_strncmp(cmd->cmd_arg[1], "-n", 10))
		i = 2;
	while (cmd->cmd_arg[i])
	{
		ft_putstr_fd(cmd->cmd_arg[i], 1);
		if (cmd->cmd_arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp(cmd->cmd_arg[1], "-n", 10))
		write(1, "\n", 1);
}
