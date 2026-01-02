/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:54 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/27 17:17:58 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "helpers.h"
#include "libft.h"
#include "parsing.h"
#include "structs.h"
#include <stdio.h>  //to use printf
#include <unistd.h> //to use close

int	is_scene_valid(t_scene *scene)
{
	if (scene->ambient == NULL)
		return (printf("Error\nParsing: No ambient element defined\n"), 0);
	if (scene->camera == NULL)
		return (printf("Error\nParsing: No camera element defined\n"), 0);
	if (scene->lights == NULL)
		return (printf("Error\nParsing: No light element defined\n"), 0);
	if (scene->objects == NULL)
		return (printf("Error\nParsing: No object element defined\n"), 0);
	return (1);
}

int	parse_file(t_scene *scene, char *filename)
{
	int		fd;
	int		error;
	char	*line;

	error = 0;
	fd = open_file(filename);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd); //creates leakes when multiple elements are found where only one is allowed.
		if (line == NULL)
			break ;
		if (line[0] != '\0' && line[0] != '#' && error == 0)
			if (process_line(scene, line) != 0)
				error = -1;
		free(line);
	}
	close(fd);
	if (error == -1 || is_scene_valid(scene) != 1)
		return (-1);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	process_line(t_scene *scene, char *line)
{
	char	**split_line;

	split_line = ft_split_set(line, " \n\t");
	if (split_line == NULL)
		return (printf("Error\nParsing: Malloc fail\n"), -1);
	if (split_line[0] == NULL)
		return (free(split_line), 0);
	if (select_element(scene, split_line) != 0)
		return (free_split(split_line), -1);
	free_split(split_line);
	return (0);
}

int	select_element(t_scene *scene, char **line)
{
	if (ft_strncmp(line[0], "A", ft_strlen(line[0])) == 0)
		return (new_ambient_struct(scene, line));
	if (ft_strncmp(line[0], "C", ft_strlen(line[0])) == 0)
		return (new_camera_struct(scene, line));
	if (ft_strncmp(line[0], "L", ft_strlen(line[0])) == 0)
		return (new_light_struct(scene, line));
	if (ft_strncmp(line[0], "sp", ft_strlen(line[0])) == 0)
		return (new_sphere_struct(scene, line));
	if (ft_strncmp(line[0], "pl", ft_strlen(line[0])) == 0)
		return (new_plane_struct(scene, line));
	if (ft_strncmp(line[0], "cy", ft_strlen(line[0])) == 0)
		return (new_cylinder_struct(scene, line));
	printf("Error\nParsing: Element %s not supported\n", line[0]);
	return (1);
}
