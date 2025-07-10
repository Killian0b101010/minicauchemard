/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:38:35 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/16 13:13:50 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_printchar(char c);
int	ft_printnbr(int nb);
int	ft_printstr(char *str);
int	ft_print_upperhex(unsigned int nbr);
int	ft_print_lowerhex(unsigned int nbr);
int	is_valid_base(char *base);
int	ft_printnbrui(unsigned int nb);
int	ft_printptr(unsigned long long ptr);
int	ft_parseformat(va_list args, const char *format);

#endif