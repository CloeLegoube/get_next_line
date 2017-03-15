/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:13:12 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 14:47:09 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_whitespaces(char s)
{
	if (s == ' ' || s == '\n' || s == '\t')
		return (1);
	return (0);
}

static char		*check_malloc(char character, int size_malloc)
{
	char	*copy;

	if (character == '\0')
	{
		copy = (char *)malloc(1 * sizeof(*copy));
		copy[0] = '\0';
	}
	else
		copy = (char *)malloc(size_malloc * sizeof(*copy));
	return (copy);
}

char			*ft_strtrim(char const *s)
{
	char	*copy;
	int		start;
	int		end;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s) - 1;
	while (is_whitespaces(*(char *)(s + start)) == 1)
		start++;
	while (is_whitespaces(*(char *)(s + end)) == 1)
		end--;
	copy = check_malloc(*(char *)(s + start), (end - start + 2));
	if (copy == NULL)
		return (NULL);
	while (start <= end)
	{
		copy[i] = *(char *)(s + start);
		start++;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
