/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/04 17:20:46 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	find_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-42);
}
int	main(void)
{
	int			fd;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_r;
	int			i;
	int			k;
	char static	*stock;

	i = find_line(buffer);
	k = 0;
	fd = open("salut.txt", O_RDONLY);
	bytes_r = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_r] = '\0';
	printf("%s", buffer);
	if (find_line(buffer) == -42)
	{
		while (buffer[k])
		{
			stock[k] = buffer[k];
		}
	}
	else if (find_line(buffer))
	{
		while (k < i)
		{
			ft_putchar(buffer[k]);
			i++;
		}
	}
}
