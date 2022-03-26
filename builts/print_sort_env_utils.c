/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sort_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:46:33 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/19 12:51:17 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_sort_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	next = (*env)->next;
	while (next)
	{
		if (ft_strncmp(current->key, next->key, 1000) > 0)
			return (0);
		current = current->next;
		next = next->next;
	}
	return (1);
}

void	print_copy(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		write(1, "=\"", 2);
		ft_putstr_fd(tmp->value, 1);
		write(1, "\"\n", 2);
		tmp = tmp->next;
	}
}

void	copy_env(t_env **env, t_env **copy)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		lst_add_back_env(copy, lst_new_env(ft_strdup(tmp->key),
				ft_strdup(tmp->value)));
		tmp = tmp->next;
	}
}

void	swap_env(t_env *elem1, t_env *elem2)
{
	char	*key;
	char	*value;

	key = elem1->key;
	value = elem1->value;
	elem1->key = elem2->key;
	elem1->value = elem2->value;
	elem2->key = key;
	elem2->value = value;
}

void	sort_copy_env(t_env **env)
{
	t_env	*tmp;

	while (!check_sort_env(env))
	{
		tmp = *env;
		while (tmp->next)
		{
			if (ft_strncmp(tmp->key, tmp->next->key, 1000) > 0)
				swap_env(tmp, tmp->next);
			tmp = tmp->next;
		}
	}
}
