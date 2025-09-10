/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:56:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/05/20 15:37:07 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h> //to use NULL, size_t
# include <unistd.h> //to use write
# include <stdarg.h> //to use va_xxx

//ft_printf
int		ft_printf(const char *c, ...);
int		process_str(const char *c, va_list args);
int		select_print(char c, va_list args);

//print select 1
int		print_c(va_list args);
int		print_s(va_list args);
int		print_p(va_list args);
int		print_d(va_list args);
int		print_u(va_list args);

//print select 2
int		print_lx(va_list args);
int		print_ux(va_list args);
int		print_pct(void);

//helpers
size_t	pf_strlen(const char *str);
int		pf_putnbr(int nb);
int		pf_putunsignednbr(unsigned int nb);
int		pf_puthex(unsigned int nb, int uppercase);
int		pf_putpointer(unsigned long long p);

#endif
