/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:25:35 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:24:20 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, &(*str++), 1);
}
/*
int	main(void)
{
	char	*str;
	int		fd;

	str = "Hello, World!";
	fd = 1; // Standard output (stdout)
	ft_putstr_fd(str, fd);
	return (0);
}
 */