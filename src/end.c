/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:24:49 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/26 15:14:17 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>

int		close_window(t_param *param)
{
	(void)param; // free param
	exit(0);
}

void	error_msg(char *str, t_param *param)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	close_window(param);
}

void	error_msg_tmp(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	exit(0);
}
