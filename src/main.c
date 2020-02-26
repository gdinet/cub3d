/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:25:19 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/26 13:13:56 by gdinet           ###   ########.fr       */
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

int		key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;
	int		fd;
	void	*param = NULL;

	if (ac == 1)
	{
		printf("map svp\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	parsing(&map, fd);
	close (fd);
	mlx = init_mlx(&map);
	render(&map, &mlx);
	mlx_key_hook(mlx.win, &key_hook, param);
	//mlx_loop_hook(mlx.mlx_ptr, &render, param);
	mlx_loop(mlx.mlx_ptr);
	return 0;
}
