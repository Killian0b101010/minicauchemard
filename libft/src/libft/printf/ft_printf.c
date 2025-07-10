/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:15:45 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:15:45 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"
#include "../../../includes/libft.h"

int	ft_parseformat(va_list args, const char *format)
{
	int	printed_chars;

	printed_chars = 0;
	if (*format == 'c')
		printed_chars += ft_printchar(va_arg(args, int));
	else if (*format == 's')
		printed_chars += ft_printstr(va_arg(args, char *));
	else if (*format == 'p')
		printed_chars += ft_printptr(va_arg(args, unsigned long long));
	else if (*format == 'd' || *format == 'i')
		printed_chars += ft_printnbr(va_arg(args, int));
	else if (*format == 'u')
		printed_chars += ft_printnbrui(va_arg(args, unsigned int));
	else if (*format == 'x')
		printed_chars += ft_print_lowerhex(va_arg(args, unsigned int));
	else if (*format == 'X')
		printed_chars += ft_print_upperhex(va_arg(args, unsigned int));
	else if (*format == '%')
		printed_chars += ft_printchar('%');
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	printed_chars = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed_chars += ft_parseformat(args, format);
			format++;
		}
		else
			printed_chars += ft_printchar(*format++);
	}
	va_end(args);
	return (printed_chars);
}

/* int	main(void)
{
	int	x;

	ft_printf("ft_printf: %c\n", 'A');
	printf("printf: %c\n", 'A');
	ft_printf("ft_printf: %s\n", "Hello, World!");
	printf("printf: %s\n", "Hello, World!");
	x = 42;
	ft_printf("ft_printf: %p\n", &x);
	printf("printf: %p\n", &x);
	ft_printf("ft_printf: %d\n", 12345);
	printf("printf: %d\n", 12345);
	ft_printf("ft_printf: %i\n", -6789);
	printf("printf: %i\n", -6789);
	ft_printf("ft_printf: %u\n", 4294967295U);
	printf("printf: %u\n", 4294967295U);
	ft_printf("ft_printf: %x\n", 255);
	printf("printf: %x\n", 255);
	ft_printf("ft_printf: %X\n", 255);
	printf("printf: %X\n", 255);
	ft_printf("ft_printf: %%\n");
	printf("printf: %%\n");
	ft_printf("ft_printf: %s\n", (char *)NULL);
	printf("printf: %s\n", (char *)NULL);
	ft_printf("ft_printf: %p\n", NULL);
	printf("printf: %p\n", NULL);
	ft_printf("ft_printf: %d\n", 0);
	printf("printf: %d\n", 0);
	ft_printf("ft_printf: %u\n", 0);
	printf("printf: %u\n", 0);
	return (0);
} */
