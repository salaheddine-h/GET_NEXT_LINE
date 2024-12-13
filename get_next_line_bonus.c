/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:37:46 by salhali           #+#    #+#             */
/*   Updated: 2024/12/13 13:58:23 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *storage)
{
	char		*buffer;
	ssize_t		read_bytes;
	char		*temp;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!storage || !ft_strchr(storage, '\n')))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(storage), storage = NULL, NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(storage, buffer);
		if (!temp)
			return (free(buffer), free(storage), (NULL));
		free(storage);
		storage = temp;
	}
	return (free(buffer), (storage));
}

char	*ft_line(char *storage)
{
	char	*line;
	int		i;
	int		j;

	if (!storage)
		return (NULL);
	i = 0;
	j = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
	{
		free(storage);
		return (NULL);
	}
	while (j < i)
 
		line[j] = storage[i];
		j++;
		i++;
	}
	line[j] = '\0';
	return (line);
}

char	*clean_storage(char *storage)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!storage)
		return (free(storage), NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (free(storage), NULL);
	if (storage[i++] == '\n')
		if (!storage[i])
			return (free(storage), NULL);
	cpy = malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!cpy)
		return (free(storage), NULL);
	while (storage[i])
		cpy[j++] = storage[i++];
	cpy[j] = '\0';
	free(storage);
	return (cpy);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	storage[fd] = ft_read(fd, storage[fd]);
	if (!storage[fd])
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	line = ft_line(storage[fd]);
	if (!line)
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	storage[fd] = clean_storage(storage[fd]);
	return (line);
}
