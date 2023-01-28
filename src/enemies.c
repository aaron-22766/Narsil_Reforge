/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:07:29 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/27 13:45:43 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_update_enemy_img(t_player *player, t_enemy *enemy)
{
	char	*file_name;
	char	*type;
	int32_t	x;
	int32_t	y;

	type = ft_calloc(7, sizeof(char));
	if (!type)
		ft_terror(0, player);
	ft_strlcpy(type, "Enemy", 7);
	ft_strlcat(type, enemy->num, 7);
	x = enemy->x * RES;
	y = enemy->y * RES;
	if (enemy->img)
	{
		x = enemy->img->instances[0].x;
		y = enemy->img->instances[0].y;
		mlx_delete_image(player->mlx, enemy->img);
	}
	file_name = ft_get_dir_file_name(player, type, enemy->dir);
	free(type);
	enemy->img = ft_get_img(player, file_name);
	free(file_name);
	if (mlx_image_to_window(player->mlx, enemy->img, x, y) < 0)
		ft_mlxerror(player);
}

static int	ft_enemy_move(t_player *player, t_enemy *enemy, int x, int y)
{
	if (player->map[enemy->y + y][enemy->x + x] == '1')
		return (0);
	enemy->x += x;
	enemy->y += y;
	return (1);
}

static void	ft_new_enemy_target(t_player *player, t_enemy *enemy)
{
	char	walls[5];
	char	*c;
	int		prev_dir;

	prev_dir = enemy->dir;
	if (rand() % 50 == 42)
		enemy->dir = rand() % 4;
	ft_bzero(walls, 5);
	while (ft_enemy_move(player, enemy, enemy->dir % 2 * ((enemy->dir != 3)
				* 2 - 1), enemy->dir % 2 + ((enemy->dir == 2) * 2 - 1)) == 0)
	{
		c = ft_itoa(enemy->dir);
		ft_strlcat(walls, c, 5);
		free(c);
		while (ft_strchr(walls, '0' + enemy->dir) && ft_strlen(walls) < 4)
			enemy->dir = rand() % 4;
		if (ft_strlen(walls) == 4)
		{
			enemy->dir = -1;
			return ;
		}
	}
	if (enemy->dir != prev_dir)
		ft_update_enemy_img(player, enemy);
}

static void	ft_enemies_iteri(t_player *player,
		void (*f)(t_player *player, t_enemy *enemy))
{
	int	i;

	i = -1;
	while (player->enemies[++i])
	{
		if (player->enemies[i]->dir != -1)
			f(player, player->enemies[i]);
	}
}

void	ft_enemies(t_player *player)
{
	t_enemy	*enemy;

	enemy = player->enemies[0];
	if (enemy->img->instances[0].x == enemy->x * RES
		&& enemy->img->instances[0].y == enemy->y * RES)
		ft_enemies_iteri(player, &ft_new_enemy_target);
	ft_enemies_iteri(player, &ft_animate_enemy);
}
