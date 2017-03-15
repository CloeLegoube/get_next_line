/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:07:04 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/06 17:28:03 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *copy_dest;

	copy_dest = dst;
	while (*src && len > 0)
	{
		*copy_dest++ = *src++;
		len--;
	}
	while (len > 0)
	{
		*copy_dest++ = '\0';
		len--;
	}
	return (dst);
}
