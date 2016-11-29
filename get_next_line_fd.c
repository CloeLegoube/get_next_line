/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:39:12 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/29 14:38:37 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_buff	*ft_lstnewbuf(char *buffer, int fd)
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

int		if_stock_exist(t_list **stock, char **line, t_var *var)
{
	int				j;
	t_list			*new;
	t_buff			*buffer;
	int				size;

	j = 0;
	while ((*(char *)(BUFFER + j)) != '\0')
	{
		if ((*(char *)(BUFFER + j)) == '\n')
		{
			ft_memdel((void *)line);
			*line = ft_strsub(BUFFER, 0, j);
			size = (*stock)->content_size - j - 1;
			buffer = ft_lstnewbuf(ft_strsub(BUFFER, \
					j + 1, size), var->fd);
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
	t_list			*new;
	t_buff			*buffer;

	var->i = -1;
	while (++var->i < var->ret)
	{
		if (buf[var->i] == '\n' || buf[var->i] == '\0')
		{
			ft_memdel((void *)line);
			*line = *stock ? ft_strjoin(BUFFER, ft_strsub(buf, 0, var->i)) :
				ft_strsub(buf, 0, var->i);
			buffer = ft_lstnewbuf(ft_strsub(buf, var->i + 1, RET), var->fd);
			new = ft_lstnew(buffer, RET);
			*stock = new;
			return (-1);
		}
	}
	return (0);
}

int		if_ret_inf_size(t_list **stock, char **line, char *buf, t_var *var)
{
	if (var->ret < BUFF_SIZE)
	{
		if (*stock && ft_strchr(BUFFER, '\n') != NULL)
		{
			ft_memdel((void *)line);
			*line = ft_strjoin(BUFFER, \
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
			buffer = ft_lstnewbuf(ft_strjoin(BUFFER, \
					ft_strsub(buf, 0, ft_strlen(buf))), var->fd);
			new = ft_lstnew(buffer, var->ret + (*stock)->content_size);
		}
		else
		{
			buffer = ft_lstnewbuf(buf, var->fd);
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

	var = (t_var*)malloc(sizeof(t_var));
	var->ret = 0;
	var->fd = fd;
	while (stock && CT((stock)->content)->fd != fd)
		stock = stock->next;
	if (stock)
		if (if_stock_exist(&stock, line, var) == 1)
			return (1);
	buf = (char *)malloc((BUFF_SIZE + 1) * sizeof(buf));
	while ((var->ret = read(fd, buf, BUFF_SIZE)))
	{
		if (if_ret_inf_size(&stock, line, buf, var) == 0)
			return (0);
		if (if_i_inf_ret(&stock, line, buf, var) == -1)
			return (1);
		if_i_equal_ret(&stock, buf, var);
	}
	if (var->ret == 0)
		*line = NULL;
	return (-1);
}
