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
	char			buf[BUFF_SIZE + 1];
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
	if (stock != NULL)
	{
		ft_putstr("test6");
		j = 0;
		while ((*(char *)(stock->content + j)) != '\0')
		{
			if ((*(char *)(stock->content + j)) == '\n')
			{
				ft_putstr("test8");
				ft_memdel((void *)line);
				*line = ft_strnew(j);
				*line = ft_strsub(stock->content, 0, j);
				new = ft_lstnew(ft_strsub(stock->content, j + 1, (stock->content_size - j - 1)), (stock->content_size - j - 1));
				ft_lstdelete(stock);
				ft_lstadd(&stock, new);
				ft_putstr(stock->content);
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
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		ft_putstr("test1\n");
		i = 0;
		while (i < ret)
		{
			/*
			** Si un \n est trouve, on verifie si la liste chainee est vide ou non
			** Si elle n'est pas vide, on renvoie line avec le restant de la liste et le debut de buffer jusqu'au 1er \n
			** Le reste est stocke dans une liste chaine a la fin, apres avoir delete la struct precedente.
			** Si elle est vide, on renvoie seulement le debut du buffer jusqu'au 1er \n
			** et on stocke le reste dans la liste chainee a la fin.
			*/
			// ft_putstr("test2");
			// ft_putchar(buf[i]);
			// ft_putstr("test2");
			printf("test 2 : %c --> %d\n", buf[i], i);
			if (buf[i] == '\n')
			{
				ft_putstr("test3");
				if (stock != NULL && stock->content_size != 0)
				{
					ft_putstr("test4");
					ft_memdel((void *)line);
					*line = ft_strnew(i + stock->content_size);
					*line = ft_strjoin(stock->content, ft_strsub(buf, 0, i));
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					//ft_lstdelete(stock);
					stock = new;
				}
				else
				{
					ft_putstr("test5");
					ft_memdel((void *)line);
					*line = ft_strnew(i);
					*line = ft_strsub(buf, 0, i);
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					stock = new;
				}
				return (1);
			}
			/*
			** ---------------------------------------------------------------------------------------------------
			** Si un \0 est trouve alors la lecture est terminee, on verifie si la liste chainee est vide ou non
			** Si elle n'est pas vide, on renvoie line avec le restant de la liste et le debut de buffer jusqu'au 1er \n
			** Il n'y a plus rien a stocker.
			** Si elle est vide, on renvoie seulement le debut du buffer jusqu'au 1er \n
			** Il n'y a plus rien a stocker.
			*/
			// else if (buf[i] == '\0')
			// {
			// 	if (stock->next != NULL)
			// 	{
			// 		ft_putstr("test11");
			// 		ft_memdel((void *)line);
			// 		*line = ft_strnew(i + stock->content_size);
			// 		*line = ft_strjoin(stock->content, ft_strsub(buf, 0, i));
			// 	}
			// 	else
			// 	{
			// 		ft_putstr("test12");
			// 		ft_memdel((void *)line);
			// 		*line = ft_strnew(i);
			// 		*line = ft_strsub(buf, 0, i);
			// 	}
			// 	return (0);
			// }
			i++;
		}
		if (i == ret)
		{
			ft_putstr("test new ret\nbuffer :");
			ft_putstr(buf);
			new = ft_lstnew(buf, ret);
			//ft_lstdelete(stock);
			stock = new;
			//ft_putstr(stock->content);

		}
		// if (stock && next_line == 1)
		// {
		// 	ft_putstr("test9");
		// 	ft_putstr("content-stock :");
		// 	ft_putstr(stock->content);
		// 	ft_putchar('\n');
		// 	ft_putstr("buff :");
		// 	ft_putstr(buf);
		// 	ft_putchar('\n');
		// 	new = ft_lstnew(ft_strjoin(stock->content, buf), ret + stock->content_size);
		// 	ft_lstdelete(stock);
		// 	//ret = read(fd, buf, BUFF_SIZE);
		// 	stock = new;
		// 	get_next_line(fd, line);
		// 	// ft_putstr("content-new :");
		// 	// ft_putstr(stock->content);
		// 	// ft_putchar('\n');
		// 	i++;
		// }
		// else
		// {
		// 	ft_putstr("test10");
		// 	new = ft_lstnew(buf, ret);
		// 	//ret = read(fd, buf, BUFF_SIZE);
		// 	stock = new;
		// 	get_next_line(fd, line);
		// 	// ft_putstr("content-new :");
		// 	// ft_putstr(stock->content);
		// 	// ft_putchar('\n');
		// 	i++;
		// }
	}
	return (-1);
}

/*
** Penser a la condition ret < BUFF_SIZE pour avoir la fin du FICHIER
*/
