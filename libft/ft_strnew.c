/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 22:11:05 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 10:29:52 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*string;
	size_t	i;

	i = 0;
	string = (char *)malloc((size + 1) * sizeof(*string));
	if (string == NULL)
		return (NULL);
	*(string + size) = '\0';
	while (i < size)
	{
		*(string + i) = 0;
		i++;
	}
	return (string);
}
