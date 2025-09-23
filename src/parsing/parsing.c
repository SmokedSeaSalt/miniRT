/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:54 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/23 11:19:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use printf
#include <unistd.h>		//to use close
#include "get_next_line.h"
#include "helpers.h"
#include "structs.h"
#include "parsing.h"
#include "libft.h"

//TODO
//error handling
//make unit tests

int parse_file(t_scene *scene, char *filename)
{
	int fd;
	char *line;

	fd = open_file(filename);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (line[0] != '\0') //check what happens with line with only whitespaces
			process_line(scene, line);
		free(line);
	}
	close(fd);
	//check_valid_scene(scene);
	//check if enough valid elements are present (minimum 1 object, cam, light, ambient)
	return (0);
}

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int process_line(t_scene *scene, char *line)
{
	char **split_line;

	split_line = ft_split_set(line, " \t,");
	if (split_line == NULL)
		return(printf("Parsing: Malloc fail\n"), -1);
	select_element(scene, split_line);
	free_split(split_line);
	return (0);
}

int	select_element(t_scene *scene, char **line)
{
	if (line[0] == NULL)
		return (0);
	if (ft_strncmp(line[0], "A", ft_strlen(line[0])) == 0)
		return(new_ambient_struct(scene, line));
	if (ft_strncmp(line[0], "C", ft_strlen(line[0])) == 0)
		return(new_camera_struct(scene, line));
	if (ft_strncmp(line[0], "L", ft_strlen(line[0])) == 0)
		return(new_light_struct(scene, line));
	if (ft_strncmp(line[0], "sp", ft_strlen(line[0])) == 0)
		return(new_sphere_struct(scene, line));
	if (ft_strncmp(line[0], "pl", ft_strlen(line[0])) == 0)
		return(new_plane_struct(scene, line));
	if (ft_strncmp(line[0], "cy", ft_strlen(line[0])) == 0)
		return(new_cylinder_struct(scene, line));
	printf("Parsing: Element %s not found\n", line[1]);
	return(1);
}

