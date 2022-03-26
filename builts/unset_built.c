/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:28:09 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/19 16:11:33 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_built(t_point *p)
{
	t_env	*tmp;
	t_env	*del;
	int		i;

	i = 1;
	while (p->cmd->cmd_arg[i])
	{
		del = find_value_env(p->cmd->cmd_arg[i], &p->env_list);
		if (!del)
			continue ;
		tmp = p->env_list;
		while (tmp->next != del)
			tmp = tmp->next;
		if (ft_strncmp(tmp->key, del->key, 1000) > 0)
		{
			free(del->key);
			free(del->value);
			tmp->next = del->next;
			free(del);
		}
		i++;
	}
}
