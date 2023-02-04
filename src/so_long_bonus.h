/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:23:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/04 18:15:33 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include "../lib/mlx/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define RES 32
# define N_H 16
// N_H = Height of UI numbers
# define N_W 10
// N_W = Width of UI numbers
# define PLAYER_SPEED 2
# define SPRINT_SPEED 4
# define ENEMY_SPEED 1
// RES % X_SPEED == 0 !!
# define END_ANI 128
// Duration of the end animation in frames
# define ANI_FRAMES 16
// Number of frames in animation
// Best if END_ANI % 16 == 0

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_enemy
{
	mlx_image_t		*img;
	int				x;
	int				y;
	int				dir;
	char			*num;
}	t_enemy;

// dir: 0 = UP / 1 = RIGHT / 2 = DOWN / 3 = LEFT

typedef struct s_player
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*ani_img;
	char			**map;
	char			*sprite_path;
	char			*end;
	int				frames;
	int				wait;
	int				key_down;
	int				key_hold;
	int				speed;
	int				x;
	int				y;
	int				dir;
	int				moves;
	int				collects;
	int				all_collects;
	t_enemy			**enemies;
	mlx_image_t		**moves_ui;
	mlx_image_t		**collects_ui;
	mlx_image_t		**all_collects_ui;
}	t_player;

// dir: 0 = UP / 1 = RIGHT / 2 = DOWN / 3 = LEFT

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

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
void		ft_update_player_img(t_player *player);
void		ft_init_player(t_player *player);
void		ft_render_counters(t_player *player);

// init_enemies.c
void		ft_init_enemies(t_player *player);

// enemies.c
void		ft_update_enemy_img(t_player *player, t_enemy *enemy);
void		ft_enemies(t_player *player);

// animation.c
void		ft_end_animation(t_player *player);
void		ft_animate_player_move(t_player *player);
void		ft_animate_enemy(t_player *player, t_enemy *enemy);

// player_move.c
void		ft_move(t_player *player, int x, int y);

// ui.c
void		ft_moves_ui(t_player *player);
void		ft_collects_ui(t_player *player);

// get_file_name.c
char		*ft_get_file_name(char c);
char		*ft_get_dir_file_name(t_player *player, char *type, int dir);
char		*ft_get_ani_file_name(t_player *player);

// utils.c
int			ft_count_c(char **map, char c);
int			ft_to_power(int nb, int power);
int			ft_count_digits(int n);

// free.c
void		ft_free_player(t_player *player);
void		ft_terminate_free(t_player *player, int err);

// error.c
void		ft_error(char code);
void		ft_ferror(char code, t_player *player);
void		ft_terror(char code, t_player *player);
void		ft_mlxerror(t_player *player);

#endif