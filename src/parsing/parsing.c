/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:54 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/22 16:58:17 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use printf
#include <fcntl.h>		//to use open
#include <sys/stat.h>	//to use open
#include "structs.h"
#include "parsing.h"
#include "libft.h"

//TODO
//error handling
//make unit tests
//check if enough valid elements are present (minimum 1 object, cam, light, ambient)




//check valid file name
//open file
//get next line

int is_valid_extension(char* str)
{
	char *extension;

	extension = ft_strrchr(str, '.');
	if (extension == NULL)
		return (0);
	if (ft_strlen(extension) == ft_strlen(".rt") \
&& ft_strncmp(extension, ".rt", 3) == 0)
		return (1);
	return (0);
}

/// @brief opens the file with a given filename
/// @param filename name of the file opened
/// @return -1 on failure. fd on success.
int open_file(char *filename)
{
	int fd;

	if(is_valid_extension(filename) == 0)
		return (printf("Parsing: Filetype not supported"), -1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Parsing: Opening file failed"), -1);
	return (fd);
}



int	select_element(t_scene *scene, char **line)
{
	if (ft_strncmp(line[1], "A", ft_strlen(line[1])) == 0)
		return(new_ambient_struct(scene, line));
	if (ft_strncmp(line[1], "C", ft_strlen(line[1])) == 0)
		return(new_camera_struct(scene, line));
	if (ft_strncmp(line[1], "L", ft_strlen(line[1])) == 0)
		return(new_light_struct(scene, line));
	if (ft_strncmp(line[1], "sp", ft_strlen(line[1])) == 0)
		return(new_sphere_struct(scene, line));
	if (ft_strncmp(line[1], "pl", ft_strlen(line[1])) == 0)
		return(new_plane_struct(scene, line));
	if (ft_strncmp(line[1], "cy", ft_strlen(line[1])) == 0)
		return(new_cylinder_struct(scene, line));
	printf("Parsing: Element %s not found", line[1]);
	return(1);
}

