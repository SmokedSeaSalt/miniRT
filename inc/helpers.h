/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:08:58 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/11/12 13:33:02 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

char	**ft_split_set(char const *s, char const *set);
void	*ft_free_split(char **ret);
double	ft_atof(const char *str);
char	*ft_ftoa(double val);

long long	get_time_in_ms(void);
long long	get_timestamp(long long start_time);

#endif