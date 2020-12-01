/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:25:19 by gdinet            #+#    #+#             */
/*   Updated: 2020/12/01 17:28:01 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int		key_press(int keycode, t_param *param)
{
	if (keycode == KEY_Z)
		param->key |= W;
	if (keycode == KEY_Q)
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
		close_window(param);
	return (0);
}

int		key_release(int keycode, t_param *param)
{
	if (keycode == KEY_Z)
		param->key &= ~W;
	if (keycode == KEY_Q)
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
	render(param);
	sprite(param);
	mlx_put_image_to_window(param->mlx->mlx_ptr, param->mlx->win,
	param->mlx->img_ptr, 0, 0);
	return (0);
}

int		check_arg(int ac, char **av)
{
	if (ac == 1 || (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 5)))
	{
		ft_putendl_fd("Please give a map (file.cub) as first argument", 1);
		return (1);
	}
	else if (ac == 3 && !ft_strncmp(av[2], "--save", 7))
	{
		ft_putendl_fd("The second argument must be --save or nothing", 1);
		return (1);
	}
	else if (ac > 3)
	{
		ft_putendl_fd("2 arguments maximum", 1);
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_param		param;
	t_map		map;
	t_mlx		mlx;
	int			fd;

	if (!check_arg(ac, av))
	{
		map = init_map();
		mlx = init_mlx();
		param.map = &map;
		param.mlx = &mlx;
		param.key = 0;
		if ((fd = open(av[1], O_RDONLY)) == -1)
			error_msg("Error opening file", &param);
		parsing(&param, fd);
		close(fd);
		if (ac == 3)
			bmp_file(&param);
		mlx_hook(mlx.win, 2, 1L << 0, &key_press, &param);
		mlx_hook(mlx.win, 3, 1L << 1, &key_release, &param);
		mlx_hook(mlx.win, 17, 1L << 17, &close_window, &param);
		mlx_loop_hook(mlx.mlx_ptr, &loop_hook, &param);
		mlx_loop(mlx.mlx_ptr);
	}
	return (0);
}
