/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:33:57 by xberger           #+#    #+#             */
/*   Updated: 2023/11/01 09:28:10 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *save_buff)
{
	int		i;
	char	*s;

	i = 0;
	if (!save_buff[i])
		return (NULL);
	while (save_buff[i] && save_buff[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save_buff[i] && save_buff[i] != '\n')
	{
		s[i] = save_buff[i];
		i++;
	}
	if (save_buff[i] == '\n')
	{
		s[i] = save_buff[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save_buff(char *save_buff)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (save_buff[i] && save_buff[i] != '\n')
		i++;
	if (!save_buff[i])
	{
		free(save_buff);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save_buff) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (save_buff[i])
		s[j++] = save_buff[i++];
	s[j] = '\0';
	free(save_buff);
	return (s);
}

char	*ft_read(int fd, char *save_buff)
{
	char	*buff;
	int		read_bytes;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save_buff, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save_buff = ft_strjoin(save_buff, buff);
	}
	free(buff);
	return (save_buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save_buff = ft_read(fd, save_buff);
	if (!save_buff)
		return (NULL);
	line = ft_get_line(save_buff);
	save_buff = ft_save_buff(save_buff);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int main() 
{
	char *line;
//	int	fd;

//	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(0)) != NULL)   
	{
		printf("%s", line);
		free(line);
	}
//	close(fd);
	return 0;
}

