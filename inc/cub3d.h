/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:33:42 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/26 14:39:18 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RES_X_MAX 2560
# define RES_Y_MAX 1440
# define FOV 60
# define WALL_H 1

# define EAST_COLOR 0x1a1a1a
# define WEST_COLOR 0x1a1a1a
# define NORTH_COLOR 0x333333
# define SOUTH_COLOR 0x333333

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*win;
	void	*img_ptr;
	int		*img;
	int		bpp;
	int		size;
	int		endian;
}					t_mlx;

typedef struct		s_vector
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
}					t_vector;

typedef struct		s_map
{
	int		res_x;
	int		res_y;
	float	screen_d;
	char	**map;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor;
	int		ceil;
	char	*sprite;
	float	pos_x;
	float	pos_y;
	float	angle;
}					t_map;

typedef struct		s_distance
{
	int		step_x;
	int		step_y;
	float	delta_x;
	float	delta_y;
	float	side_x;
	float	side_y;
	int		side_hit;
}					t_distance;

int			parsing(t_map *map, int fd);
int			parse_map(t_map *map, char *line);
int			render(t_map *map, t_mlx *mlx);
t_mlx		init_mlx(t_map *map);
void		mlx_end(t_mlx *mlx);

#endif
