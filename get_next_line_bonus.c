/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:23:43 by xberger           #+#    #+#             */
/*   Updated: 2023/11/01 08:36:52 by xberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*save_buff[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (0);
	save_buff[fd] = ft_read(fd, save_buff[fd]);
	if (!save_buff[fd])
		return (NULL);
	line = ft_get_line(save_buff[fd]);
	save_buff[fd] = ft_save_buff(save_buff[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int main() 
{
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);

	char *line1;
	char *line2;
	char *line3;

	while (1) 
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		if (line1) 
		{
			printf("File 1: %s", line1);
			free(line1);
		}

		if (line2) 
		{
			printf("File 2: %s", line2);
			free(line2);
		}
		if (line3) 
		{
			printf("File 3: %s", line3);
			free(line3);
		}
		if (!line1 && !line2 && !line3)
			break;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
}
*/
