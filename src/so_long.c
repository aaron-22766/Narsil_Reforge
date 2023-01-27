/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/01/23 10:48:52 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static char	**ft_get_map(int fd)
{
	size_t	i;
	char	**map;

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
	int			fd;

	ft_check_args(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(3);
	player = malloc(sizeof(t_player));
	if (!player)
		ft_error(0);
	player->map = ft_get_map(fd);
	close(fd);
	if (!player->map)
		ft_error(0);
	ft_check_map(player);
	player->sprite_path = argv[0];
	ft_play(player);
}
