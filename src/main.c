/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:25:19 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/08 15:39:18 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keys.h"
#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int		key_press(int keycode, t_param *param)
{
	if (keycode == KEY_W)
		param->key |= W;
	if (keycode == KEY_A)
		param->key |= A;
	if (keycode == KEY_S)
		param->key |= S;
	if (keycode == KEY_D)
		param->key |= D;
	if (keycode == KEY_RIGHT)
		param->key |= RIGHT;
	if (keycode == KEY_LEFT)
		param->key |= LEFT;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int		key_release(int keycode, t_param *param)
{
	if (keycode == KEY_W)
		param->key &= ~W;
	if (keycode == KEY_A)
		param->key &= ~A;
	if (keycode == KEY_S)
		param->key &= ~S;
	if (keycode == KEY_D)
		param->key &= ~D;
	if (keycode == KEY_RIGHT)
		param->key &= ~RIGHT;
	if (keycode == KEY_LEFT)
		param->key &= ~LEFT;
	return (0);
}

int		loop_hook(t_param *param)
{
	move_straight(param->key, param->map);
	move_side(param->key, param->map);
	rotate(param->key, param->map);
	render(param->map, param->mlx);
	return (0);
}

int		close_window(t_param *param)
{
	(void)param;
	exit(0);
}

int		main(int ac, char **av)
{
	t_map		map;
	t_mlx		mlx;
	int			fd;
	t_param		param;

	if (ac == 1)
	{
		printf("map svp\n");
		return (0);
	}
	map = init_map();
	mlx = init_mlx();
	fd = open(av[1], O_RDONLY);
	parsing(&map, &mlx, fd);
	close(fd);
	printf("map ok\n");
	param.map = &map;
	param.mlx = &mlx;
	param.key = 0;
	
	mlx_hook(mlx.win, 2, 1L << 0, &key_press, &param);
	mlx_hook(mlx.win, 3, 1L << 1, &key_release, &param);
	mlx_hook(mlx.win, 17, 0, &close_window, &param);
	mlx_loop_hook(mlx.mlx_ptr, &loop_hook, &param);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
