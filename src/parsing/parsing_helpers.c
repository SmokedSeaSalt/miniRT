/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:45:52 by mvan-rij          #+#    #+#             */
/*   Updated: 2026/01/15 14:34:00 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include "structs.h"
#include "helpers.h"
#include "libft.h"

int	count_arguments(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
		i++;
	return (i);
}

t_vec3	fill_vec3(char *x_str, char *y_str, char *z_str)
{
	t_vec3	vec3;

	vec3 = vec3_new(ft_atof(x_str), ft_atof(y_str), ft_atof(z_str));
	return (vec3);
}

void	add_object_to_back(t_object **list, t_object *new)
{
	t_object	*tmp;

	if (list == NULL)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

//checks for arguments with comma's if they are valid
int	has_incorrect_commas(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ',')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == ',' && str[i -1] == ',')
			return (1);
		i++;
	}
	if (str[i - 1] == ',')
		return (1);
	return (0);
}

int	parse_color_val(char *str)
{
	const int	len = ft_strlen(str);
	int			result;
	int			i;

	i = 0;
	result = 0;
	if (len == 0 || len > 3)
		return (-1);
	if (len > 1 && str[0] == '0')
		return (-1);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	return (result);
}
