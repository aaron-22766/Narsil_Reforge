/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/07/13 16:51:24 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Narsil_Reforge.h"

static char	**ft_realloc_map(char **ptr, size_t count)
{
	char	**new;
	size_t	i;

	if (count < 2)
		return (NULL);
	if (!ptr)
		return (ft_calloc(count, sizeof(char *)));
	new = ft_calloc(count, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (ptr[++i])
		new[i] = ptr[i];
	free(ptr);
	return (new);
}

static char	**ft_get_map(char *path)
{
	int		fd;
	size_t	i;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(3);
	map = 0;
	i = 0;
	while (1)
	{
		map = ft_realloc_map(map, i + 2);
		if (!map)
			return (NULL);
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			break ;
		if (ft_strchr(map[i], '\n'))
			ft_strchr(map[i], '\n')[0] = 0;
		i++;
	}
	close(fd);
	return (map);
}

static void	ft_check_args(int argc, char **argv)
{
	if (argc != 2)
		ft_error(1);
	if (!ft_strnstr(&argv[1][ft_strlen(argv[1])] - 4, ".ber", 4))
		ft_error(2);
}

int	main(int argc, char **argv)
{
	t_player	*player;

	ft_check_args(argc, argv);
	player = malloc(sizeof(t_player));
	if (!player)
		ft_error(0);
	player->map = ft_get_map(argv[1]);
	player->enemies = 0;
	player->moves_ui = 0;
	player->collects_ui = 0;
	if (!player->map)
		ft_ferror(0, player);
	ft_check_map(player);
	player->sprite_path = argv[0];
	ft_play(player);
}
