/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:18:51 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/09 18:10:59 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*tdest;
	const char	*tsrc;

	tdest = dest;
	tsrc = src;
	if (tdest < tsrc)
		while (n)
		{
			*tdest++ = *tsrc++;
			n--;
		}
	else
	{
		tsrc = tsrc + n;
		tdest = tdest + n;
		while (n)
		{
			*--tdest = *--tsrc;
			n--;
		}
	}
	return (dest);
}
