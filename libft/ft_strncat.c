/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 15:36:19 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 10:29:37 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i] && i < n)
		s1[len++] = s2[i++];
	s1[len] = '\0';
	return (s1);
}
