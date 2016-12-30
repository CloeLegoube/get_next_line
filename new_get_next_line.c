/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 09:08:54 by clegoube          #+#    #+#             */
/*   Updated: 2016/12/28 13:21:16 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_strindexchr(const char *s, int c)
{
	int		i;

	i = 0;
	if ((char)c == '\0')
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (0);
}

int	get_line(char *buf, t_list **stock, char **line)
{
	int		index;
	char	*temp;
	t_list		*new;

	if (buf)
	{
		temp = ft_strdup(buf);
		printf("temp-buff :%s", temp);
	}
	else
	{
		temp = ft_strdup((*stock)->content);
		printf("temp-stock :%s", temp);
	}
	index = ft_strindexchr(temp, '\n');
	printf("\nindex :%d", index);
	if (index)
	{

		// *temp = '\0';

		// if (stock)
		// 	// *line = ft_strdup((*stock)->content);
		// 	printf("\nIF STOCK");
		// 	// printf("stock : %s", (*stock)->content);
		// 	// *line = ft_strjoin((*stock)->content, ft_strsub(temp, 0, index));
		// else
			*line = ft_strsub(temp, 0, index);
		// *line = ft_strdup((*stock)->content);
		// ft_structdelete(*stock);
		new = ft_lstnew(ft_strsub(buf, index, ft_strlen(buf)), ft_strlen(buf) + 1);
		// printf("\nstock :%s", (*stock)->content);
		ft_lstadd(stock, new);
		ft_strdel(&buf);
		temp = NULL;
		return (1);
	}
	return (0);
}

// int	get_line(char *buf, t_list **stock, char **line)
// {
// 	char		*temp;
// 	// t_list		*new;
//
// 	if (buf)
// 	{
// 		temp = ft_strchr(buf, '\n');
// 		printf("Temp :%s", temp);
// 	}
// 	else
// 		temp = ft_strchr((*stock)->content, '\n');
// 	if (temp)
// 	{
//
// 		*temp = '\0';
//
// 		// if (stock)
// 		// 	*line = ft_strjoin((*stock)->content, buf);
// 		// else
// 		*line = ft_strdup("hello");
// 		// *line = ft_strdup((*stock)->content);
// 		// ft_structdelete(*stock);
// 		// new = ft_lstnew(ft_strdup(temp + 1), ft_strlen(temp) + 1);
// 		// ft_lstadd(stock, new);
// 		// ft_strdel(&buf);
// 		// temp = NULL;
// 		return (1);
// 	}
// 	return (0);
// }


int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			*buf;
	t_list			*new;
	static t_list	*stock = NULL;

	ret = 0;
	// while (stock && ((t_buff *)(stock->content))->fd != fd)
	// 	stock = stock->next;
	if (stock)
	{

		if (get_line(NULL, &stock, line))
			return (1);
	}

	buf = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (get_line(buf, &stock, line))
			return (1);
		new = ft_lstnew(ft_strjoin(stock->content, buf), ft_strlen(ft_strjoin(stock->content, buf)));
		ft_lstadd(&stock, new);
	}
	if (ret == -1)
		return (-1);
	if (!stock)
		return (0);
	*line = ft_strdup(stock->content);
	ft_strdel(&buf);
	ft_structdelete(stock);
	return (1);
}
