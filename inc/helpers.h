/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:08:58 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/11/04 11:17:03 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

char	**ft_split_set(char const *s, char const *set);
void	*ft_free_split(char **ret);
double	ft_atof(const char *str);
char	*ft_ftoa(double val);

#endif