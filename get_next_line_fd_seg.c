/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:39:12 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/28 19:18:57 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_buff	*ft_lstnewbuff(char *buffer, int fd)
{
	t_buff	*new;

	new = (t_buff*)malloc(sizeof(t_buff));
	if (new == NULL)
		return (NULL);
	if (buffer == NULL)
	{
		new->buffer = NULL;
		new->fd = 0;
	}
	else
	{
		new->buffer = (void*)malloc(ft_strlen(buffer) + 1);
		new->buffer = ft_memcpy(new->buffer, (void*)buffer, \
		ft_strlen(buffer) + 1);
		new->fd = fd;
	}
	return (new);
}

int		if_stock_exist(t_list **stock, char **line, int fd)
{
	int				j;
	t_list			*new;
	t_buff			*buffer;
	int				size;

	j = 0;
	while ((*(char *)(CT((*stock)->content)->buffer + j)) != '\0')
	{
		if ((*(char *)(CT((*stock)->content)->buffer + j)) == '\n')
		{
			ft_memdel((void *)line);
			*line = ft_strsub(CT((*stock)->content)->buffer, 0, j);
			size = (*stock)->content_size - j - 1;
			buffer = ft_lstnewbuff(ft_strsub(CT((*stock)->content)->buffer, \
					j + 1, size), fd);
			new = ft_lstnew(buffer, size);
			ft_structdelete(*stock);
			ft_lstadd(stock, new);
			return (1);
		}
		j++;
	}
	return (0);
}

int		if_i_inf_ret(t_list **stock, char **line, char *buf, t_var *var)
{
	int				i;
	t_list			*new;
	t_buff			*buffer;

	i = -1;
	while (++i < var->ret)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			ft_memdel((void *)line);
			if (*stock)
			{
				*line = ft_strnew(i + (*stock)->content_size);
				*line = ft_strjoin(CT((*stock)->content)->buffer, \
					ft_strsub(buf, 0, i));
				buffer = ft_lstnewbuff(ft_strsub(buf, i + 1, RET), var->fd);
				new = ft_lstnew(buffer, RET);
			}
			else
			{
				*line = ft_strsub(buf, 0, i);
				buffer = ft_lstnewbuff(ft_strsub(buf, i + 1, RET), var->fd);
				new = ft_lstnew(buffer, RET);
			}
			*stock = new;
			return (-1);
		}
	}
	return (i);
}

int		if_ret_inf_size(t_list **stock, char **line, char *buf, t_var *var)
{
	if (var->ret < BUFF_SIZE)
	{
		if (*stock && ft_strchr(CT((*stock)->content)->buffer, '\n') != NULL)
		{
			ft_memdel((void *)line);
			*line = ft_strjoin(CT((*stock)->content)->buffer, \
					ft_strsub(buf, 0, var->ret));
			return (0);
		}
	}
	return (-1);
}

void	if_i_equal_ret(t_list **stock, char *buf, t_var *var)
{
	t_list			*new;
	t_buff			*buffer;

	new = NULL;
	if (var->i == var->ret)
	{
		if (*stock)
		{
			buffer = ft_lstnewbuff(ft_strjoin(CT((*stock)->content)->buffer, \
						ft_strsub(buf, 0, ft_strlen(buf))), var->fd);
			new = ft_lstnew(buffer, var->ret + (*stock)->content_size);
		}
		else
		{
			buffer = ft_lstnewbuff(buf, var->fd);
			new = ft_lstnew(buffer, var->ret);
		}
		*stock = new;
	}
}

int		get_next_line(const int fd, char **line)
{
	char			*buf;
	static t_list	*stock = NULL;
	t_var			*var;

	var = NULL;
	var->ret = 0;
	var->fd = fd;
	while (stock && CT((stock)->content)->fd != fd)
		stock = stock->next;
	if (stock && CT((stock)->content)->fd == fd)
		if (if_stock_exist(&stock, line, fd) == 1)
			return (1);
	buf = (char *)malloc((BUFF_SIZE + 1) * sizeof(buf));
	while ((var->ret = read(fd, buf, BUFF_SIZE)))
	{
		if (if_ret_inf_size(&stock, line, buf, var) == 0)
			return (0);
		if (if_i_inf_ret(&stock, line, buf, var) == -1 ||
			((var->i = if_i_inf_ret(&stock, line, buf, var)) && 0))
			return (1);
		if_i_equal_ret(&stock, buf, var);
	}
	return (-1);
}
