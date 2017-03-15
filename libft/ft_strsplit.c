/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:25:52 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 15:26:07 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_check_special_char(char chaine, char charset)
{
	if (chaine == charset)
		return (1);
	return (0);
}

static int			by_word(char *str, char charset)
{
	int chaine;
	int mot;

	chaine = 0;
	mot = 0;
	while (str[chaine])
	{
		if (!ft_check_special_char(str[chaine], charset) && str[chaine])
		{
			if (ft_check_special_char(str[chaine + 1], charset)
				|| !str[chaine + 1])
				++mot;
		}
		chaine++;
	}
	return (++mot);
}

static t_var		*initialize_variables(void)
{
	t_var	*var;

	if (!(var = (t_var*)malloc(sizeof(t_var))))
		return (NULL);
	var->chaine = -1;
	var->mot = 0;
	var->lettre = 0;
	var->next = NULL;
	return (var);
}

static void			by_letter(char **tab, char *str, char charset)
{
	int		chaine;
	int		mot;
	int		lettre;

	chaine = 0;
	mot = 0;
	lettre = 0;
	while (str[chaine])
	{
		if (!ft_check_special_char(str[chaine], charset) && str[chaine])
		{
			if (ft_check_special_char(str[chaine + 1], charset)
				|| !str[chaine + 1])
			{
				tab[mot++] = (char*)malloc((lettre + 1) * sizeof(char));
				lettre = 0;
			}
		}
		lettre++;
		chaine++;
	}
	tab[mot] = (char*)malloc((lettre + 1) * sizeof(char));
}

char				**ft_strsplit(char const *str, char charset)
{
	char	**tab;
	t_var	*var;

	if (!str || !charset)
		return (NULL);
	if (!(tab = (char**)malloc(by_word((char *)str, charset) * sizeof(char*))))
		return (NULL);
	by_letter(tab, (char *)str, charset);
	var = initialize_variables();
	while (str[++var->chaine])
	{
		if (!ft_check_special_char(str[var->chaine], charset) &&
			str[var->chaine])
		{
			tab[var->mot][var->lettre++] = str[var->chaine];
			if (ft_check_special_char(str[var->chaine + 1], charset) ||
				!str[var->chaine + 1])
			{
				tab[var->mot++][var->lettre] = '\0';
				var->lettre = 0;
			}
		}
	}
	tab[var->mot] = 0;
	return (tab);
}
