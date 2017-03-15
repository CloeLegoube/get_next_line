/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:51:08 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 12:24:48 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	int			i;
	char		*fresh_string;

	i = 0;
	if (!s || !f)
		return (NULL);
	fresh_string = (char *)malloc((ft_strlen(s) + 1) * sizeof(*fresh_string));
	if (fresh_string == NULL)
		return (NULL);
	while (*(char *)(s + i))
	{
		fresh_string[i] = f(*(char *)(s + i));
		i++;
	}
	fresh_string[i] = '\0';
	return (fresh_string);
}
