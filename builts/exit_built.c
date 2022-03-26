/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:56:17 by bsheryl           #+#    #+#             */
/*   Updated: 2022/01/19 16:52:56 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_built(t_point *p)
{
	(void)p;
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_cod);
}
