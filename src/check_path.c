/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:38:11 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/23 10:48:35 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_get_pos(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				return (i * ft_strlen(map[i]) + j);
			j++;
		}
		i++;
	}
	return (-1);
}

static int	ft_find_path(char **map, int pos, int dest, char *vis)
{
	size_t	len;

	if (pos < 0)
		return (-1);
	len = ft_strlen(map[0]);
	vis[pos] = 1;
	if (pos == dest)
		return (1);
	if (map[pos / len - 1][pos % len] != '1' && !vis[pos - len])
		if (ft_find_path(map, pos - len, dest, vis))
			return (1);
	if (map[pos / len][pos % len + 1] != '1' && !vis[pos + 1])
		if (ft_find_path(map, pos + 1, dest, vis))
			return (1);
	if (map[pos / len + 1][pos % len] != '1' && !vis[pos + len])
		if (ft_find_path(map, pos + len, dest, vis))
			return (1);
	if (map[pos / len][pos % len - 1] != '1' && !vis[pos - 1])
		if (ft_find_path(map, pos - 1, dest, vis))
			return (1);
	return (0);
}

void	ft_check_path(t_player *player)
{
	char	*vis;
	int		pos;
	int		i;
	int		j;
	int		path;

	i = -1;
	while (player->map[++i])
	{
		j = -1;
		while (player->map[i][++j])
		{
			if (ft_strchr("CE", player->map[i][j]))
			{
				pos = i * ft_strlen(player->map[0]) + j;
				vis = ft_calloc(ft_count_c(player->map, 0) + 1, sizeof(char));
				path = ft_find_path(player->map,
						ft_get_pos(player->map, 'P'), pos, vis);
				free(vis);
				if (path != 1)
					ft_ferror(19, player);
			}
		}
	}
}
