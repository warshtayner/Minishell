/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:45:51 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/21 12:06:39 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_sort_env(t_env **env)
{
	t_env	*copy;

	copy = NULL;
	copy_env(env, &copy);
	sort_copy_env(&copy);
	print_copy(&copy);
	free_env(&copy);
}

t_env	*add_new_arg(char *str)
{
	int		i;
	t_env	*new;

	i = 0;
	while (str[i] != '=')
		i++;
	new = lst_new_env(ft_substr(str, 0, i),
			ft_substr(str, i + 1, ft_strlen(str)));
	return (new);
}

void	change_arg(t_env *tmp, t_env *new)
{
	free(tmp->value);
	tmp->value = ft_strdup(new->value);
	free(new->value);
	free(new->key);
	free(new);
}

void	export_args(t_point *p)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = 1;
	while (p->cmd->cmd_arg[i])
	{
		new = add_new_arg(p->cmd->cmd_arg[i]);
		tmp = p->env_list;
		while (tmp)
		{
			if (ft_strnstr(tmp->key, new->key, 1000))
			{
				change_arg(tmp, new);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			lst_add_back_env(&p->env_list, new);
		i++;
	}
}

void	export_built(t_point *p)
{
	if (!p->cmd->cmd_arg[1])
		print_sort_env(&p->env_list);
	else
		export_args(p);
}
