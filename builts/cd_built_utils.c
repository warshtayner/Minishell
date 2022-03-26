/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builts_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:06:59 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/18 14:03:58 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cut_pwd(t_env *current)
{
	int		i;
	char	*res;

	i = ft_strlen(current->value) - 1;
	while (current->value[i] != '/')
		i--;
	res = ft_substr(current->value, 0, i);
	free(current->value);
	current->value = res;
}

int	cut_begin_path(char **path, t_point *p)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[0][i] == '.')
		i++;
	if (i != 2 && path[0][i - 1] != '/')
	{
		print_no_such(p);
		return (1);
	}
	while (path[0][i] == '/')
		i++;
	tmp = ft_substr(*path, i, ft_strlen(*path));
	free(*path);
	*path = tmp;
	return (0);
}

char	*get_absolute_from_relative(t_point *p, char *path)
{
	char	*tmp_path;
	char	*tmp_pwd;
	t_env	*tmp;

	tmp = find_value_env("PWD", &p->env_list);
	while (ft_strnstr(path, "..", 2) || ft_strnstr(path, "/..", 3))
	{
		if (cut_begin_path(&path, p))
			return (0);
		cut_pwd(tmp);
	}
	tmp_path = ft_strjoin(tmp->value, "/");
	free(tmp->value);
	tmp->value = tmp_path;
	tmp_pwd = ft_strjoin(tmp->value, path);
	free(path);
	return (tmp_pwd);
}

void	print_no_such(t_point *p)
{
	ft_putstr_fd("minishell%: ", 2);
	ft_putstr_fd(p->cmd->cmd_arg[0], 2);
	ft_putstr_fd(": no such file or directory: ", 2);
	ft_putstr_fd(p->cmd->cmd_arg[1], 2);
	write(2, "\n", 1);
}
