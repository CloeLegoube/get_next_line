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
	if (stock)
	{
		j = 0;
		while ((*(char *)(CONTENT + j)) != '\0')
		{
			if ((*(char *)(CONTENT + j)) == '\n')
			{
				ft_memdel((void *)line);
				*line = ft_strsub(CONTENT, 0, j);
				new = ft_lstnew(ft_strsub(CONTENT, j + 1, (SIZE - j - 1)), (SIZE - j - 1));
				ft_lstdelete(stock);
				ft_lstadd(&stock, new);
				return (1);
			}
			j++;
		}
	}
	buf = (char *)malloc((BUFF_SIZE + 1) * sizeof(buf));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		i = 0;
		if (ret < BUFF_SIZE)
		{
			if (stock && ft_strchr(CONTENT, '\n') != NULL)
			{
				ft_memdel((void *)line);
				*line = ft_strjoin(CONTENT, ft_strsub(buf, 0, ret));
				return (0);
			}
		}
		while (i < ret)
		{
			if (buf[i] == '\n' || buf[i] == '\0')
			{
				if (stock != NULL && SIZE != 0)
				{
					ft_memdel((void *)line);
					*line = ft_strnew(i + SIZE);
					*line = ft_strjoin(CONTENT, ft_strsub(buf, 0, i));
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					stock = new;
				}
				else
				{
					ft_memdel((void *)line);
					*line = ft_strsub(buf, 0, i);
					new = ft_lstnew(ft_strsub(buf, i + 1, (ret - i - 1)), (ret - i - 1));
					stock = new;
				}
				return (1);
			}
			i++;
		}
		if (i == ret)
		{
			if (stock)
			{
				new = ft_lstnew(ft_strjoin(CONTENT, ft_strsub(buf, 0, ft_strlen(buf))), ret + SIZE);
				stock = new;
			}
			else
			{
				new = ft_lstnew(buf, ret);
				stock = new;
			}
		}
	}
	return (-1);
}
