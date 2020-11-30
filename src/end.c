/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:24:49 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/30 15:16:59 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>

void	free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
}

int		close_window(t_param *param)
{
	free_map(param->map->map);
	free(param->map->map);
	mlx_destroy_image(param->mlx->mlx_ptr, param->map->north.ptr);
	mlx_destroy_image(param->mlx->mlx_ptr, param->map->south.ptr);
	mlx_destroy_image(param->mlx->mlx_ptr, param->map->east.ptr);
	mlx_destroy_image(param->mlx->mlx_ptr, param->map->west.ptr);
	mlx_destroy_image(param->mlx->mlx_ptr, param->map->sprite.ptr);
	ft_lstclear(&(param->map->lst_sprite), NULL);
	free(param->map->dist_array);
	mlx_destroy_image(param->mlx->mlx_ptr, param->mlx->img_ptr);
	mlx_destroy_window(param->mlx->mlx_ptr, param->mlx->win);
	exit(0);
}

void	error_msg(char *str, t_param *param)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	close_window(param);
}
