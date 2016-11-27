#include "get_next_line.h"
#include <stdio.h>

void		ft_lstdelete(t_list *alst)
{
	t_list 	*tmp;

	if (alst->content != NULL && alst->content_size != 0)
	{
		free(alst->content);
		alst->content = NULL;
		tmp = (alst)->next;
		free(alst);
		alst = tmp;
	}
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	int				i;
	int				j;
	char			*buf;
	static t_list	*stock = NULL;
	t_list			*new;
	int				next_line;

	ret = 0;
	next_line = 0;
	/*
	** -----------------------------------------------------------------------------------------------
	** 					VERIFICATION DE LA LISTE CHAINEE
	** -----------------------------------------------------------------------------------------------
	** Verifie si la liste chainee a stocke du buffer.
	** Si oui, parcours le contenu et renvoie dans line la 1ere partie jusqu'a \n
	** Le reste est de nouveau stocke dans la liste chaine au debut apres avoir supprime l'ancienne.
	** Si aucun \n n'est trouve, on fait une nouvelle lecture.
	*/
	if (stock)
	{
		ft_putstr("test6");
		j = 0;
		while ((*(char *)(CONTENT + j)) != '\0')
		{
			if ((*(char *)(CONTENT + j)) == '\n')
			{
				ft_putstr("test8");
				ft_memdel((void *)line);
				//*line = ft_strnew(j);
				*line = ft_strsub(CONTENT, 0, j);
				new = ft_lstnew(ft_strsub(CONTENT, j + 1, (SIZE - j - 1)), (SIZE - j - 1));
				ft_lstdelete(stock);
				ft_lstadd(&stock, new);
				return (1);
			}
			j++;
		}
	}
	/*
	** -----------------------------------------------------------------------------------------------
	** 						LECTURE DU FICHIER
	** -----------------------------------------------------------------------------------------------
	** Si le nbre de charactere lu n'est pas null alors on parcours le buffer.
	*/
	buf = (char *)malloc((BUFF_SIZE + 1) * sizeof(buf));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		ft_putstr("test1\n");
		i = 0;
		/*
		** ---------------------------------------------------------------------------------------------------
		** Si un \0 est trouve alors la lecture est terminee, on verifie si la liste chainee est vide ou non
		** Si elle n'est pas vide, on renvoie line avec le restant de la liste et le debut de buffer jusqu'au 1er \n
		** Il n'y a plus rien a stocker.
		** Si elle est vide, on renvoie seulement le debut du buffer jusqu'au 1er \n
		** Il n'y a plus rien a stocker.
		*/
		if (ret < BUFF_SIZE)
		{
			ft_putstr("test14");
			if (stock && ft_strchr(CONTENT, '\n') != NULL)
			{
				ft_putstr("test11");
				ft_memdel((void *)line);
				//*line = ft_strnew(i + SIZE);
				*line = ft_strjoin(CONTENT, ft_strsub(buf, 0, ret));
				return (0);
			}
		}
		while (i < ret)
		{
			printf("test 2 : %c --> %d\n", buf[i], i);

			/*
			** ---------------------------------------------------------------------------------------------------------
			** Si un \n est trouve, on verifie si la liste chainee est vide ou non
			** Si elle n'est pas vide, on renvoie line avec le restant de la liste et le debut de buffer jusqu'au 1er \n
			** Le reste est stocke dans une liste chaine a la fin, apres avoir delete la struct precedente.
			** Si elle est vide, on renvoie seulement le debut du buffer jusqu'au 1er \n
			** et on stocke le reste dans la liste chainee a la fin.
			*/
			if (buf[i] == '\n' || buf[i] == '\0')
			{
				ft_putstr("test3");
				if (stock != NULL && SIZE != 0)
				{
					ft_putstr("test4");
					ft_memdel((void *)line);
					//*line = ft_strnew(i + SIZE);
					*line = ft_strjoin(CONTENT, ft_strsub(buf, 0, i));
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					//ft_lstdelete(stock);
					stock = new;
				}
				else
				{
					ft_putstr("test5");
					ft_memdel((void *)line);
					//*line = ft_strnew(i);
					*line = ft_strsub(buf, 0, i);
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					stock = new;
				}
				return (1);
			}
			i++;
		}
		/*
		** ---------------------------------------------------------------------------
		** Si le BUFF_SIZE < la longueur de la ligne.
		** on stocke la valeur du buff ou on ajoute le buff dans un nouveau maillon
		*/
		if (i == ret)
		{
			ft_putstr("test13");
			if (stock)
			{
				ft_putstr("test9");
				new = ft_lstnew(ft_strjoin(CONTENT, buf), ret + SIZE);
				ft_lstdelete(stock);
				stock = new;
			}
			else
			{
				ft_putstr("test10");
				new = ft_lstnew(buf, ret);
				stock = new;
			}
		}
	}
	return (-1);
}
