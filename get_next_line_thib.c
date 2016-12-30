/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_thib.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:21:02 by clegoube          #+#    #+#             */
/*   Updated: 2016/12/30 16:03:13 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdio.h>

int		get_lines(char *stock, char **line)
{
	char			*tmp;

	if ((tmp = ft_strchr(stock, '\n')))
	{
		*line = ft_strsub(stock, 0, tmp - stock);
						// printf("\nLigne a afficher:%s - ", *line);
		// free(stock);
		// printf("\nTaille:%zu - ", ft_strlen(tmp + 1));
		// if (ft_strlen(tmp + 1) != 0)
			stock = ft_strcpy(stock, tmp + 1);
		// if (*(tmp + 1))
		// 	printf("\nstock restant:%s|\n", stock);
		// else
		// 	return (0);
		//
		// // if (ft_strncmp((tmp + 1), "\0", 1) != 0)
		// stock = ft_strdup(tmp + 1);
		// //
		// // else
		// // 	*stock = NULL;
		//
		// if (ft_strncmp(tmp + 1, "\0", 1) == 0)
		// {
		//
		// 	if (stock)
		// 	{
		// 		printf("\nstock de la fin:%s|\n", stock);
		// 		// free(stock);
		// 		stock = NULL;
		// 	}
		// }
		tmp = NULL;
		return (1);
	}
	// printf("mais pas de \\n - ");
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*stock;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	char			*w;
	int				ret;

	if (stock)
	{
						// printf("\nOui il y a du stock - ");
						// printf("\nLe stock est :%s", stock);
		if (get_lines(stock, line))
			return (1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = (stock) ? ft_strjoin(stock, buf) : ft_strdup(buf);
		// if (stock)
		// {
		// 	tmp = ft_strjoin(stock, buf);
		// 				printf("Test5");
		// 	free(stock);
		// }
		// else
		// 	tmp = ft_strdup(buf);

		stock = ft_strdup(tmp);
						// printf("\nTOUT le Stock :%s", stock);
		free(tmp);
		if (get_lines(stock, line))
			return (1);
	}
	if (ret == -1)
		return (-1);
		if (ft_strcmp(stock, "\0") != 0)
		    {
		        if ((w = ft_strchr(stock, '\n')) != NULL) // ici tu verifie que ta lecture est terminee mais stock pas nulle
		        {
		            *line = ft_strsub(stock, 0, (w - stock));
		            stock = ft_strcpy(stock, w + 1);
		            return (1); // au prochain appel, il ne peut pas y avoir un '/n' et un '/0'
		        }
		        if (w == NULL && ft_strcmp(stock, "\0") != 0) //ca gere le cas ou il n'y a pas de '/n' a la fin
		        {
		            *line = ft_strsub(stock, 0, ft_strchr(stock, '\0') - stock);
		            stock = ft_strcpy(stock, ft_strchr(stock, '\0'));
		            return (1);
		        }
		    }
		return (0);
}
