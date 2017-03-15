/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:13:44 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 10:30:31 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	if ((int)size <= 0)
		return (NULL);
	dest = (char *)malloc((size + 1) * sizeof(*dest));
	if (dest == NULL)
		return (NULL);
	dest[i + size] = '\0';
	while (i < size)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
