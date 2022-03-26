/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_char_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:53:54 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/26 14:53:54 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_char_env(t_point *p, int size, char **env)
{
	int		i;
	int		shlvl_int;
	char	*tmp;
	char	*shlvl_char;

	p->env = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "SHLVL=", 6))
		{
			tmp = ft_substr(env[i], 0, 6);
			shlvl_int = ft_atoi(env[i] + 6);
			shlvl_char = ft_itoa(++shlvl_int);
			p->env[i] = ft_strjoin(tmp, shlvl_char);
			free(tmp);
			free(shlvl_char);
			i++;
			continue ;
		}
		p->env[i] = ft_strdup(env[i]);
		i++;
	}
	p->env[i] = NULL;
}

void	free_char_env(t_point *p)
{
	int	i;

	i = 0;
	while (p->env[i])
	{
		if (p->env[i])
			free(p->env[i]);
		i++;
	}
	if (p->env)
		free(p->env);
	p->env = NULL;
}

void	update_char_env(t_point *p)
{
	int		i;
	char	*str;
	t_env	*tmp;

	tmp = p->env_list;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	p->env = malloc(sizeof(char *) * (i + 1));
	tmp = p->env_list;
	i = 0;
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		p->env[i] = ft_strjoin(str, tmp->value);
		free(str);
		tmp = tmp->next;
		i++;
	}
	p->env[i] = NULL;
}
