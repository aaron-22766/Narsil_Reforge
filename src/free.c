/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:24:03 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/06 16:41:36 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_free_player(t_player *player)
{
	int	i;

	i = 0;
	while (player->enemies && player->enemies[i])
		free(player->enemies[i++]);
	free(player->enemies);
	i = 0;
	while (player->map[i])
		free(player->map[i++]);
	free(player->map);
	free(player->moves_ui);
	free(player->collects_ui);
	free(player);
}

void	ft_terminate_free(t_player *player, int err)
{
	mlx_close_window(player->mlx);
	mlx_terminate(player->mlx);
	ft_free_player(player);
	// system("leaks so_long_bonus");
	exit(err);
}
