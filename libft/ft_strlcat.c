/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 15:40:30 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/06 16:46:31 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int j;
	unsigned int size_src;
	unsigned int size_dest;

	size_dest = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (size_dest > size)
		size_dest = size;
	j = -1;
	if (size_dest < size - 1)
	{
		while (++j + size_dest < size - 1 && src[j])
			dst[size_dest + j] = src[j];
		dst[size_dest + j] = '\0';
	}
	return (size_dest + size_src);
}
