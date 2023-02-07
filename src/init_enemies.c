/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:35:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/07 14:53:15 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Narsil_Reforge.h"

static t_enemy	*ft_new_enemy(t_player *player, int x, int y)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		ft_terror(0, player);
	enemy->x = x;
	enemy->y = y;
	enemy->dir = 2;
	enemy->img = 0;
	enemy->num = "2";
	ft_update_enemy_img(player, enemy);
	return (enemy);
}

static void	ft_random_enemy_text(t_player *player, t_enemy **enemies)
{
	int	random;

	random = 0;
	srand(time(0));
	if (ft_count_c(player->map, 'E') > 1)
		random = rand() % (ft_count_c(player->map, 'E') - 1);
	enemies[random]->num = "1";
	ft_update_enemy_img(player, enemies[random]);
	enemies[random]->img->instances[0].z = ft_count_c(player->map, 'E') + 4;
}

void	ft_init_enemies(t_player *player)
{
	t_enemy	**enemies;
	int		i;
	int		j;
	int		e;

	enemies = ft_calloc(ft_count_c(player->map, 'E') + 1, sizeof(t_enemy *));
	if (!enemies)
		ft_terror(0, player);
	e = -1;
	i = -1;
	while (player->map[++i])
	{
		j = -1;
		while (player->map[i][++j])
		{
			if (player->map[i][j] == 'E')
			{
				enemies[++e] = ft_new_enemy(player, j, i);
				enemies[e]->img->instances[0].z = e + 3;
			}
		}
	}
	ft_random_enemy_text(player, enemies);
	player->enemies = enemies;
}
