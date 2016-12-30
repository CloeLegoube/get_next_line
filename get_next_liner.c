/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_liner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:39:12 by clegoube          #+#    #+#             */
/*   Updated: 2016/12/30 13:21:53 by clegoube         ###   ########.fr       */
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

int		get_next_line(const int fd, char **line)
{
	int				ret;
	// int				i;
	char			*buf;
	static t_list	*stock = NULL;

	ret = 0;
	while (stock && ((t_buff *)(stock->content))->fd != fd)
	{
		// printf("\nstock-content : %d - %d\n", ((t_buff *)(stock->content))->fd, fd);
		stock = stock->next;
	}
	if (stock)
		if (if_stock_exist(&stock, line) == 1)
			return (1);
	buf = (char *)malloc((BUFF_SIZE + 1) * sizeof(buf));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);

		return (1);
	}
	if (ret == 0)
	{
		*line = 0;
		ft_structdelete(stock);
		return (0);
	}
	return (-1);
}
