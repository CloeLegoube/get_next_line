/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:39:12 by clegoube          #+#    #+#             */
/*   Updated: 2016/12/21 19:44:15 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		if_stock_exist(t_list **stock, char **line)
{
	int				j;
	t_list			*new;
	int				size;

	j = 0;
	while ((*(char *)((*stock)->content + j)) != '\0')
	{
		if ((*(char *)((*stock)->content + j)) == '\n')
		{
			ft_memdel((void *)line);
			*line = ft_strsub((*stock)->content, 0, j);
			size = (*stock)->content_size - j - 1;
			new = ft_lstnew(ft_strsub((*stock)->content, j + 1, size), size);
			ft_structdelete(*stock);
			ft_lstadd(stock, new);
			return (1);
		}
		j++;
	}
	return (0);
}

int		if_i_inf_ret(t_list **stock, char **line, char *buf, int ret)
{
	int				i;
	t_list			*new;

	i = -1;
	while (++i < ret)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			ft_memdel((void *)line);
			if (*stock)
			{
				*line = ft_strnew(i + (*stock)->content_size);
				*line = ft_strjoin((*stock)->content, ft_strsub(buf, 0, i));
				new = ft_lstnew(ft_strsub(buf, i + 1, RET), RET);
			}
			else
			{
				*line = ft_strsub(buf, 0, i);
				new = ft_lstnew(ft_strsub(buf, i + 1, RET), RET);
			}
			*stock = new;
			return (-1);
		}
	}
	return (i);
}

int		if_ret_inf_size(t_list **stock, char **line, char *buf, int ret)
{
	if (ret < BUFF_SIZE)
	{
		if (*stock && ft_strchr((*stock)->content, '\n') != NULL)
		{
			ft_memdel((void *)line);
			*line = ft_strjoin((*stock)->content, ft_strsub(buf, 0, ret));
			return (0);
		}
	}
	return (-1);
}

void	if_i_equal_ret(t_list **stock, char *buf, int ret, int i)
{
	t_list			*new;

	new = NULL;
	if (i == ret)
	{
		if (*stock)
			new = ft_lstnew(ft_strjoin((*stock)->content, ft_strsub(buf, 0, \
				ft_strlen(buf))), ret + (*stock)->content_size);
		else
			new = ft_lstnew(buf, ret);
		*stock = new;
	}
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	int				i;
	char			*buf;
	static t_list	*stock = NULL;

	ret = 0;
	if (stock)
		if (if_stock_exist(&stock, line) == 1)
			return (1);
	buf = (char *)malloc((BUFF_SIZE + 1) * sizeof(buf));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		if (if_ret_inf_size(&stock, line, buf, ret) == 0)
			return (0);
		if (if_i_inf_ret(&stock, line, buf, ret) == -1 ||
			((i = if_i_inf_ret(&stock, line, buf, ret)) && 0))
			return (1);
		if_i_equal_ret(&stock, buf, ret, i);
	}
	if (ret == 0)
	{
		*line = 0;
		return (0);
	}

	return (-1);
}
