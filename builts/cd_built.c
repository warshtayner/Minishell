/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:58:52 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/18 13:38:17 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd_go_home(t_point *p, char *old_path)
{
	t_env	*tmp;
	t_env	*home_dir;

	home_dir = find_value_env("HOME", &p->env_list);
	chdir(home_dir->value);
	getcwd(old_path, 1000);
	tmp = find_value_env("PWD", &p->env_list);
	free(tmp->value);
	tmp->value = ft_strdup(old_path);
}

void	cd_go_absolute(t_point *p, char *old_path)
{
	t_env	*tmp;
	char	*tmp_value;
	char	*tmp_home;

	tmp = find_value_env("OLDPWD", &p->env_list);
	free(tmp->value);
	tmp->value = ft_strdup(old_path);
	tmp_value = ft_substr(p->cmd->cmd_arg[1], 1,
			(ft_strlen(p->cmd->cmd_arg[1])));
	free(p->cmd->cmd_arg[1]);
	p->cmd->cmd_arg[1] = tmp_value;
	tmp_home = ft_strdup(find_value_env("HOME", &p->env_list)->value);
	tmp_value = ft_strjoin(tmp_home, p->cmd->cmd_arg[1]);
	free(tmp_home);
	if (chdir(tmp_value))
		put_error(p->cmd->cmd_arg[0], p->cmd->cmd_arg[1],
			"No such file or directory", 1);
	tmp = find_value_env("PWD", &p->env_list);
	free(tmp->value);
	tmp->value = ft_strdup(tmp_value);
	free(tmp_value);
}

void	cd_go_relative(t_point *p, char *old_path)
{
	t_env	*tmp;
	char	*tmp_pwd;
	char	*path;

	path = ft_strdup(p->cmd->cmd_arg[1]);
	tmp = find_value_env("OLDPWD", &p->env_list);
	free(tmp->value);
	tmp->value = ft_strdup(old_path);
	tmp_pwd = get_absolute_from_relative(p, path);
	if (!tmp_pwd)
		return ;
	if (chdir(tmp_pwd) == -1)
		put_error(p->cmd->cmd_arg[0], p->cmd->cmd_arg[1],
			"No such file or directory", 1);
	free(tmp->value);
	tmp = find_value_env("PWD", &p->env_list);
	tmp->value = tmp_pwd;
}

void	cd_built(t_point *p)
{
	char	old_path[1000];

	getcwd(old_path, 1000);
	if (!find_value_env("OLDPWD", &p->env_list))
		lst_add_back_env(&p->env_list, lst_new_env("OLDPWD", old_path));
	if (!(p->cmd->cmd_arg[1]) || (ft_strlen(p->cmd->cmd_arg[1]) == 1
			&& ft_strnstr(p->cmd->cmd_arg[1], "~", 1)))
		cd_go_home(p, old_path);
	else if (ft_strnstr(p->cmd->cmd_arg[1], "~/", 2))
		cd_go_absolute(p, old_path);
	else
		cd_go_relative(p, old_path);
}
