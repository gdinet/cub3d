/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:33:42 by gdinet            #+#    #+#             */
/*   Updated: 2020/03/04 15:03:02 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RES_X_MAX 2560
# define RES_Y_MAX 1440
# define FOV 60

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
	float	angle;
	float	dir_x;
	float	dir_y;
}					t_vector;

typedef struct		s_texture
{
	int		*img;
	int		size;
	int		width;
	int		height;
}					t_text;

typedef struct		s_map
{
	int		res_x;
	int		res_y;
	float	screen_d;
	char	**map;
	t_text	north;
	t_text	south;
	t_text	east;
	t_text	west;
	int		floor;
	int		ceil;
	t_text	sprite;
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

typedef enum		e_key
{
	W = 1,
	A = 2,
	S = 4,
	D = 8,
	RIGHT = 16,
	LEFT = 32,
}					t_key;

typedef struct		s_param
{
	t_map	*map;
	t_mlx	*mlx;
	t_key	key;
}					t_param;

t_mlx				init_mlx(void);
void				init_win(t_map *map, t_mlx *mlx);
t_map				init_map(void);

void				parsing(t_map *map, t_mlx *mlx, int fd);
void				parse_map(t_map *map, char *line);
void				check_data(t_map *map);
int					is_map(char *line);
void				check_map(char **map);

int					render(t_map *map, t_mlx *mlx);
void				mlx_end(t_mlx *mlx);
void				move_straight(t_key key, t_map *map);
void				move_side(t_key key, t_map *map);
void				rotate(t_key key, t_map *map);
int					get_color(t_text *text, int line, int wall_h, t_map *map, float hit);
float				wall_hit(t_distance *dist, t_vector *ray, float distance);
void				error_msg(char *str);

#endif