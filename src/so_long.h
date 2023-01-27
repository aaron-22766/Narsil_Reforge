/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:23:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/23 10:49:08 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/mlx/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

# define RES 32

typedef struct s_player
{
	mlx_t			*mlx;
	mlx_image_t		*img_player;
	char			**map;
	char			*sprite_path;
	int				x;
	int				y;
	unsigned int	moves;
	unsigned int	collects;
	unsigned int	all_collects;
}	t_player;

// so_long.c
// int		main(int argc, char **argv);

// check_map.c
void		ft_check_map(t_player *player);

// check_path.c
int			ft_get_pos(char **map, char c);
void		ft_check_path(t_player *player);

// play.c
void		ft_play(t_player *player);

// render.c
mlx_image_t	*ft_get_img(t_player *player, char *file_name);
void		ft_render_background(t_player *player);
void		ft_render_player(t_player *player);

// error.c
void		ft_error(char code);
void		ft_ferror(char code, t_player *player);
void		ft_mlxerror(t_player *player);

// free.c
void		ft_free_player(t_player *player);
void		ft_terminate_free(t_player *player, int err);

// utils.c
int			ft_count_c(char **map, char c);
char		*ft_get_file_name(char c);

#endif