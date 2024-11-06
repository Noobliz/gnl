/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisux <lisux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/06 11:13:34 by lisux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return ((char *)ptr - (char *)str);
}
char	*ft_strchr(const char *s, int c)
{
	const char	*str;
	int			i;

	str = s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)str + i);
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	if (dest_len >= size)
		return (src_len + size);
	i = 0;
	while (src[i] && dest_len + i < size - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (dst == NULL || src == 0)
		return (0);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = malloc(s1_len + s2_len + 1);
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1, s1_len + 1);
	ft_strlcat(arr, s2, s2_len + s1_len + 2);
	return (arr);
}
//---------------------------------------------------------------------------------------------------------------------
char	*line_extraction(char **draft, int bytes_r)
{
	size_t	line_len;
	char	*new_pos;
	char	*line;
	char	*temp;
	new_pos = ft_strchr(*draft, '\n');
	if (new_pos) // si on a trouvé une ligne
	{
		line_len = new_pos - *draft; // on trouve la len en soustrayant les 2 adresses
		line = malloc(line_len + 1);
		if (!line)
			return (NULL);
		ft_strlcpy(line, *draft, line_len + 1); // on copie dans line jusqu'au \n
		free(*draft); //on enlève ce qu'il y a dans draft (initialisé avec strjoin ou strdup)
		*draft = ft_strdup(new_pos + 1); // puis on remet ce qu'il y avait après le \n
		return (line);
	}
	else if (bytes_r == 0) // si on est à la fin du fichier on renvoie ce qu'il reste dans draft
	{
		line = ft_strdup(*draft);
		free(*draft);
		*draft = NULL;
		return (line);
	}
	else
	{
		line = NULL;
		return (line);
	}
}
char	*get_next_line(int fd)
{
	static char	*draft;
	char		buffer[BUFFER_SIZE];
	char		*line;
	int			bytes_r;
	char	*temp;
// tant qu'il n'y a pas de \n et qu'on est pas à la fin du fichier on lit et on copie dans draft
	bytes_r = 1;
	while (!ft_strchr(draft, '\n') && bytes_r > 0)
	{
		bytes_r = read(fd, buffer, BUFFER_SIZE);
		if (draft) // si y'a déjà qqchose dans draft, on y ajoute le buffer
		{
			temp = ft_strjoin(draft, buffer);
			free(draft);
			draft = temp;
		}
		else if (!draft) // si y'a rien dans draft on y fait une copie du buffer
			draft = ft_strdup(buffer);
	}
	// si y'a un \n ou qu'on arrive à la fin du fichier
	line = line_extraction(&draft, bytes_r);
	return (line);
}
int	main(void)
{
	char	*line;
	int		fd;

	// int		bytes_r;
	fd = open("salut.txt", O_RDONLY);
	/*
	bytes_r = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_r] = '\0';
	printf("%s", buffer);*/
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
}
