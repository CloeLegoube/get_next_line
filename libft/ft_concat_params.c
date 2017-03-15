/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:40:12 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/15 11:40:14 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_char(int argc, char **argv)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j++])
			count++;
		count++;
	}
	return (count);
}

char			*ft_concat_params(int argc, char **argv)
{
	char	*string;
	int		i;
	int		j;
	int		count;

	count = ft_count_char(argc, argv);
	string = (char*)malloc((count + 1) * sizeof(*string));
	i = 0;
	count = 0;
	while (argv[++i] && i < argc)
	{
		j = -1;
		while (argv[i][++j])
			string[count++] = argv[i][j];
		string[count++] = i < argc - 1 ? '\n' : 0;
	}
	return (string);
}
