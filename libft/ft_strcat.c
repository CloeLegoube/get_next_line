/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:17:34 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/06 16:01:19 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	int len;
	int i;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i])
		s1[len++] = s2[i++];
	s1[len] = '\0';
	return (s1);
}
