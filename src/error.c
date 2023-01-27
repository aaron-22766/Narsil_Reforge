/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:14:21 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/23 10:48:38 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_puterror(const char *fault, const char *expectation)
{
	if (ft_strlen(expectation) == 0)
		ft_printf("\nERROR!\n%s\n", fault);
	else
		ft_printf("\nERROR!\n%s Expected: %s\n", fault, expectation);
	exit(1);
}

void	ft_error(char code)
{
	if (code == 0)
		ft_puterror("Something went wrong! (perhaps memory allocation)", "");
	else if (code == 1)
		ft_puterror("Too few or too many input files!", "1");
	else if (code == 2)
		ft_puterror("Wrong input file type!", "*.ber");
	else if (code == 3)
		ft_puterror("Could not find the input file!", "");
}

void	ft_ferror(char code, t_player *player)
{
	ft_free_player(player);
	if (code == 0)
		ft_puterror("Something went wrong! (perhaps memory allocation)", "");
	else if (code == 10)
		ft_puterror("Empty line in map!", "");
	else if (code == 11)
		ft_puterror("Map is not rectangular!", "");
	else if (code == 12)
		ft_puterror("Map does not have enough columns!", "At least 3");
	else if (code == 13)
		ft_puterror("Map does not have enough rows!", "At least 3");
	else if (code == 14)
		ft_puterror("Map contains a non-permitted character!", "Only '10CEP'");
	else if (code == 15)
		ft_puterror("Map does not contain a collectible (C)!", "At least 1");
	else if (code == 16)
		ft_puterror("Map has too few or too many exits (E)!", "1");
	else if (code == 17)
		ft_puterror("Map has too few or too many starting positions (P)!", "1");
	else if (code == 18)
		ft_puterror("The map is not entirely surrounded by walls!", "");
	else if (code == 19)
		ft_puterror("No valid path to all collectibles and/or the exit!", "");
	else if (code == 20)
		ft_puterror("Input file is empty!", "");
}

void	ft_mlxerror(t_player *player)
{
	ft_printf("\nERROR!\n%s\n", mlx_strerror(mlx_errno));
	ft_terminate_free(player, 1);
}
