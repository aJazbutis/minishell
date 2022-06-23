/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:57:21 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/30 00:01:04 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char **bfd)
{
	char	*line;
	char	*tmp;

	if (gnl_strchr(*bfd))
	{
		line = gnl_substr(*bfd, 0, gnl_strchr(*bfd) - *bfd + 1);
		tmp = *bfd;
		*bfd = gnl_substr(gnl_strchr(*bfd) + 1, 0, gnl_l(*bfd) - gnl_l(line));
		if (gnl_l(*bfd) == 0)
		{
			free(*bfd);
			*bfd = NULL;
		}
		free(tmp);
	}
	else
	{
		line = gnl_strdup(*bfd);
		free(*bfd);
		*bfd = NULL;
	}
	return (line);
}

static	void	ft_feed_buffer(int fd, char *buff, char **bfd, int size)
{
	int	rd;

	rd = 1;
	while (rd)
	{
		rd = read(fd, buff, size);
		if (rd <= 0)
			break ;
		buff[rd] = '\0';
		if (gnl_strchr(buff))
		{
			*bfd = gnl_strjoin(*bfd, buff);
			return ;
		}
		*bfd = gnl_strjoin(*bfd, buff);
	}
}

char	*get_next_line(int fd)
{
	static char	*b_fd[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1023)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (b_fd[fd])
		{
			free(b_fd[fd]);
			b_fd[fd] = NULL;
		}
		return (NULL);
	}
	if (gnl_strchr(b_fd[fd]))
		line = ft_get_line(&b_fd[fd]);
	else
	{
		ft_feed_buffer(fd, buffer, &b_fd[fd], BUFFER_SIZE);
		line = ft_get_line(&b_fd[fd]);
	}
	free(buffer);
	return (line);
}
