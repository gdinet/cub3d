/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:33:42 by gdinet            #+#    #+#             */
/*   Updated: 2021/02/08 16:09:36 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

# define RES_X_MAX 1920
# define RES_Y_MAX 1080
# define FOV 60

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_ESC 65307

/*
** Calcul
*/
typedef struct		s_calc
{
	float	angle;
	float	dir_x;
	float	dir_y;
	int		step_x;
	int		step_y;
	float	delta_x;
	float	delta_y;
	float	side_x;
	float	side_y;
	int		side_hit;
}					t_calc;

/*
** Texture
*/
typedef struct		s_texture
{
	int		*img;
	int		size;
	int		width;
	int		height;
	void	*ptr;
}					t_text;

/*
** Sprite list
*/
typedef struct		s_sprite
{
	float	dist;
	float	pos_x;
	float	pos_y;
}					t_sprite;

/*
** Main datas
*/
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
	t_text	sprite;
	int		floor;
	int		ceil;
	t_list	*lst_sprite;
	float	*dist_array;
	float	pos_x;
	float	pos_y;
	float	angle;
}					t_map;

typedef enum		e_key
{
	W = 1,
	A = 2,
	S = 4,
	D = 8,
	RIGHT = 16,
	LEFT = 32,
}					t_key;

typedef enum		e_dir
{
	north,
	south,
	east,
	west,
}					t_dir;

/*
** Minilibx pointers
*/
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

typedef struct		s_param
{
	t_map	*map;
	t_mlx	*mlx;
	t_key	key;
}					t_param;

t_mlx				init_mlx(void);
void				init_win(t_param *param);
t_map				init_map(void);

void				parsing(t_param *param, int fd);
void				parse_map(t_param *param, char *line);
void				check_data(t_param *param);
int					is_map(char *line);
void				check_map(char **map, t_param *param);

int					render(t_param *p);
void				move_straight(t_key key, t_map *map);
void				move_side(t_key key, t_map *map);
void				rotate(t_key key, t_map *map);
float				horizontal_hit(t_map *map, t_calc *calc);
float				vertical_hit(t_map *map, int line, int wall_h);
int					get_color(t_text *text, float i, float j);

void				sort_sprite(float x, float y, t_list *lst_sprite);
void				sprite(t_param *p);

void				bmp_file(t_param *p);

void				error_msg(char *str, t_param *param);
int					close_window(t_param *param);

#endif
