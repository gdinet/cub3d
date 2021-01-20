/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:26:14 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/30 14:45:31 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 128

t_file		*find_fd(t_file **start, int fd)
{
	t_file	*prev;
	t_file	*tmp;

	if (*start)
	{
		if ((*start)->fd == fd)
		{
			tmp = *start;
			*start = (*start)->next;
			return (tmp);
		}
		prev = *start;
		while (prev->next)
		{
			if (prev->next->fd == fd)
			{
				tmp = prev->next;
				prev->next = tmp->next;
				return (tmp);
			}
			prev = prev->next;
		}
	}
	return (NULL);
}

int			read_file(t_file **start, char *buf, int fd)
{
	t_file	*tmp;
	int		len;

	if ((len = read(fd, buf, 0)) != 0)
	{
		if ((tmp = find_fd(start, fd)))
		{
			free(tmp->buf);
			free(tmp);
		}
		return (len);
	}
	if ((tmp = find_fd(start, fd)))
	{
		ft_strcpy(buf, tmp->buf);
		free(tmp->buf);
		free(tmp);
		return (ft_strlen(buf));
	}
	len = read(fd, buf, BUFFER_SIZE);
	buf[len] = '\0';
	return (len);
}

void		keep_line(t_file **start, int fd, char *end_buf)
{
	t_file	*new;

	end_buf[-1] = '\0';
	if (*end_buf)
	{
		if (!(new = malloc(sizeof(t_file))))
			return ;
		new->fd = fd;
		if (!(new->buf = ft_strdup(end_buf)))
			return ;
		new->next = *start;
		*start = new;
	}
}

char		*ft_strjoin_free(char **s1, const char *s2)
{
	char	*str;
	size_t	len;

	len = ft_strlen(*s1) + ft_strlen(s2) + 1;
	if (!(str = malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(str, *s1);
	ft_strcat(str, s2);
	free((*s1));
	return (str);
}

int			get_next_line(int fd, char **line)
{
	static t_file	*start = NULL;
	char			buf[BUFFER_SIZE + 1];
	int				i;
	int				len;
	int				join;

	if (fd < 0 || !line)
		return (-1);
	join = 0;
	while ((len = read_file(&start, buf, fd)) > 0)
	{
		i = 0;
		while (i < len && buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
			keep_line(&start, fd, buf + i + 1);
		*line = (join) ? ft_strjoin_free(line, buf) : ft_strdup(buf);
		join = 1;
		if (i < len)
			return (1);
	}
	if (!(*line))
		*line = ft_strdup("");
	return (len);
}
