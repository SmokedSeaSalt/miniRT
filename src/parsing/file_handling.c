/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:18:18 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/24 14:21:36 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use prinf
#include <fcntl.h>		//to use open
#include <sys/stat.h>	//to use open
#include "libft.h"

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

/// @brief opens the file with a .rt file extension.
/// @param filename name of the file to open.
/// @return -1 on failure.
/// @return fd on success.
int open_file(char *filename)
{
	int fd;

	if(is_valid_extension(filename) == 0)
		return (printf("Parsing: Filetype not supported\n"), -1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Parsing: Opening file failed\n"), -1);
	return (fd);
}