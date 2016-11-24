#include "get_next_line.h"
#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	int				ret;
	int				i;
	int				j;
	char			buf[BUFF_SIZE + 1];
	static t_list	**stock = NULL;
	t_list			*new;

	ret = 0;
	/*
	** -----------------------------------------------------------------------------------------------
	** 								VERIFICATION DE LA LISTE CHAINEE
	** -----------------------------------------------------------------------------------------------
	** Verifie si la liste chainee a stocke du buffer.
	** Si oui, parcours le contenu et renvoie dans line la 1ere partie jusqu'a \n
	** Le reste est de nouveau stocke dans la liste chaine au debut apres avoir supprime l'ancienne.
	** Si aucun \n n'est trouve, on fait une nouvelle lecture.
	*/
	if (stock->next != NULL)
	{
		j = 0;
		while ((char)(stock->content + j) != '\0')
		{
			if ((char)(stock->content + j) == '\n')
			{
				ft_memdel((void *)line);
				*line = ft_strnew(j);
				*line = ft_strsub(stock->content, 0, j);
				new = ft_lstnew(ft_strsub(buf, j + 1, (stock->content_size - j - 1)), (stock->content_size - j - 1));
				ft_lstdel(stock, del(stock->content, stock->content_size));
				ft_lstadd(stock, new);
			}
			else
				ret = read(fd, buf, BUFF_SIZE);
		}
	}
	else
		ret = read(fd, buf, BUFF_SIZE);
	/*
	** -----------------------------------------------------------------------------------------------
	** 								LECTURE DU FICHIER
	** -----------------------------------------------------------------------------------------------
	** Si le nbre de charactere lu n'est pas null alors on parcours le buffer.
	*/
	if (ret)
	{
		i = -1;
		while (++i < ret)
		{
			/*
			** Si un \n est trouve, on verifie si la liste chainee est vide ou non
			** Si elle n'est pas vide, on renvoie line avec le restant de la liste et le debut de buffer jusqu'au 1er \n
			** Le reste est stocke dans une liste chaine a la fin, apres avoir delete la struct precedente.
			** Si elle est vide, on renvoie seulement le debut du buffer jusqu'au 1er \n
			** et on stocke le reste dans la liste chainee a la fin.
			*/
			if (buf[i] == '\n')
			{
				if (stock->next != NULL)
				{
					ft_memdel((void *)line);
					*line = ft_strnew(i);
					*line = ft_strjoin(stock->content, ft_strsub(buf, 0, i));
					stock = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					ft_lstadd_end(stock, new);
				}
				else
				{
					ft_memdel((void *)line);
					*line = ft_strnew(i);
					*line = ft_strsub(buf, 0, i);
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					ft_lstadd_end(stock, new);
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
			else if (buf[i] == '\0')
			{
				if (stock->next != NULL)
				{
					ft_memdel((void *)line);
					*line = ft_strnew(i);
					*line = ft_strjoin(stock->content, ft_strsub(buf, 0, i));
				}
				else
				{
					ft_memdel((void *)line);
					*line = ft_strnew(i);
					*line = ft_strsub(buf, 0, i);
				}
				return (0);
			}
		}
	}
	return (-1);
}

int	ft_open(int fd)
{
	if (fd == -1)
	{
		ft_putstr("Open failed \n");
		return (1);
	}
	return (0);
}

int	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr("Close failed \n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int		fd;
	char	**line;

	line = (char **)malloc(3000 * sizeof(char **));
	if (argc < 2)
		ft_putstr("File name missing.\n");
	if (argc > 2)
		ft_putstr("Too many arguments.\n");
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (ft_open(fd) == 1)
			return (1);
		get_next_line(fd, line);
		printf("\n1) %s\n", *line);
		get_next_line(fd, line);
		printf("\n2) %s\n", *line);
		get_next_line(fd, line);
		printf("\n3) %s\n", *line);
		get_next_line(fd, line);
		printf("\n4) %s\n", *line);
		get_next_line(fd, line);
		printf("\n5) %s\n", *line);
		if (ft_close(fd) == 1)
			return (1);
	}
	return (0);

}
