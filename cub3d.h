/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:33:42 by gdinet            #+#    #+#             */
/*   Updated: 2020/01/27 09:36:40 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RES_X_MAX 2560
# define RES_Y_MAX 1440

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}					t_mlx;

typedef struct		s_data
{
	int		res_x;
	int		res_y;
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
}					t_data;

int			parsing(t_data *data, int fd);
int			parse_map(t_data *data, char *line);

#endif
