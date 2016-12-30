/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:21:02 by clegoube          #+#    #+#             */
/*   Updated: 2016/12/30 18:31:30 by clegoube         ###   ########.fr       */
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

void	line_and_stock(char *stock, char **line, char line_until, char *stock_until)
{
	*line = ft_strsub(stock, 0, line_until);
	stock = ft_strcpy(stock, stock_until);
}

int		get_lines(char *stock, char **line)
{
	char			*tmp;

	if ((tmp = ft_strchr(stock, '\n')))
	{
		line_and_stock(stock, line, (tmp - stock), (tmp + 1));
		tmp = NULL;
		return (1);
	}
	return (0);
}

int		ret_inf_zero(char *stock, char **line, int ret)
{
	char			*tmp;

	if (ret == -1)
		return (-1);
	if (ft_strcmp(stock, "\0") != 0)
	{
		if ((tmp = ft_strchr(stock, '\n')) != NULL) // ici tu verifie que ta lecture est terminee mais stock pas nulle
		{
			line_and_stock(stock, line, (tmp - stock), (tmp + 1));
			return (1); // au prochain appel, il ne peut pas y avoir un '/n' et un '/0'
		}
		if (tmp == NULL && ft_strcmp(stock, "\0") != 0) //ca gere le cas ou il n'y a pas de '/n' a la fin
		{
			line_and_stock(stock, line, (ft_strchr(stock, '\0') - stock), ft_strchr(stock, '\0'));
			return (1);
		}
		free(tmp);
	}
	return (0);
}


int				get_next_line(int const fd, char **line)
{
	// static char		*stock;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;
	static t_list	*stock = NULL;

	while (stock && ((t_buff *)(stock->content))->fd != fd)
	{
		printf("\nstock-content : %d - %d\n", ((t_buff *)(stock->content))->fd, fd);
		stock = stock->next;
	}
	// ft_memdel((void *)line);
	// *line = ft_strsub(BUFFER, 0, j);
	// size = (*stock)->content_size - j - 1;
	// buffer = ft_lstnewbuf(ft_strsub(BUFFER,
	// 		j + 1, size), var->fd);
	// new = ft_lstnew(buffer, size);
	// ft_structdelete(*stock);
	// ft_lstadd(stock, new);
	if (stock)
		if (get_lines(stock, line, fd))
			return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = (stock) ? ft_strjoin(stock, buf) : ft_strdup(buf);
		free(stock);
		stock = ft_strdup(tmp);
		free(tmp);
		if (get_lines(stock, line, fd))
			return (1);
	}
	return (ret_inf_zero(stock, line, ret));
}
