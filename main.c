/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:18:40 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/29 10:17:12 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_open(int fd)
{
	if (fd == -1)
	{
		ft_putstr("Open failed \n");
		return (1);
	}
	return (0);
}

int	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr("Close failed \n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	// int		i;
	char	**line;

	line = (char **)malloc(3000 * sizeof(char **));
	if (argc < 2)
		ft_putstr("File name missing.\n");
	fd1 = open(argv[1], O_RDONLY);
	// if (ft_open(fd1) == 1)
	// 	return (1);
	fd2 = open(argv[2], O_RDONLY);
	// if (ft_open(fd2) == 1)
	// 	return (1);
	// i = 0;
	// while ((get_next_line(fd, line) != 0))
	// {
	// 	printf("\n%d) %s\n", i, *line);
	// 	i++;
	// }
	get_next_line(fd1, line);
	printf("\n1) fd = %d - %s", fd1, *line);
	get_next_line(fd2, line);
	printf("\n1) fd = %d - %s\n", fd2, *line);

	get_next_line(fd1, line);
	printf("\n2) fd = %d - %s", fd1, *line);
	get_next_line(fd2, line);
	printf("\n2) fd = %d - %s\n", fd2, *line);

	get_next_line(fd1, line);
	printf("\n3) fd = %d - %s", fd1, *line);
	get_next_line(fd2, line);
	printf("\n3) fd = %d - %s\n", fd2, *line);

	get_next_line(fd1, line);
	printf("\n4) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n5) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n6) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n7) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n8) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n9) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n10) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n11) %s\n", *line);
	get_next_line(fd1, line);
	printf("\n12) %s\n", *line);
	// if (ft_close(fd1) == 1)
	// 	return (1);
	// if (ft_close(fd2) == 1)
	// 	return (1);

	return (0);

}
