#include "get_next_line.h"
#include <stdio.h>

static int		len_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

int		ft_count_char(char **tab)
{
	int		i;
	int		j;
	int		count;

	i = 1;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			count++;
			j++;
		}

		count++;
		i++;
	}
	return (count);
}

char			*ft_concat_tab(char **tab)
{
	char	*string;
	int		i;
	int		j;
	int		count;

	count = ft_count_char(tab);
	if (!(string = (char*)malloc(sizeof(char) * count + 1)))
		return (NULL);
	i = 1;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			string[count++] = tab[i][j];
			j++;
		}
		string[count++] = i < (len_tab(tab) - 1) ? '\n' : 0;
		i++;
	}
	//printf("String <%s> Fin_string\n", string);
	return (string);
}

int		get_next_line(const int fd, char **line)
{
	int			count_char;
	int			i;
	char		buff[BUFF_SIZE + 1];
	static char	*next_buff;
	char		**tab;


	if (next_buff)
	{
		tab = ft_strsplit(next_buff, '\n');
		if (len_tab(tab) > 1)
		{
			ft_memdel((void *)line);
			*line = (char *)malloc((ft_strlen(tab[0]) + 1) * sizeof(*line));
			*line = tab[0];
			ft_memdel((void *)&next_buff);
			next_buff = ft_concat_tab(tab);
			ft_memdel((void **)tab);
		}
	}
	else
	{
		count_char = read(fd, buff, BUFF_SIZE);
		if (count_char)
		{
			i = -1;
			while (++i < count_char)
			{
				printf("i = %d \n", i);
				if (buff[i] == '\n')
				{
					printf("|8|Point ");
					if (next_buff)
					{
						printf("|7|Point ");
						//printf("Debut_buff <%s> Fin_buff\n", next_buff);
						tab = ft_strsplit(next_buff, '\n');
						//ft_print_words_tables(tab);
						if (len_tab(tab) > 1)
						{
							ft_memdel((void *)line);
							*line = (char *)malloc((ft_strlen(tab[0]) + 1) * sizeof(*line));
							*line = tab[0];
							ft_memdel((void *)&next_buff);
							next_buff = ft_concat_tab(tab);
							ft_memdel((void **)tab);
							printf("|2|Point ");
							//printf("\n<<%s>>\n", next_buff);
						}
						else
						{
							printf("|3|Point ");
							ft_memdel((void *)line);
							*line = ft_strjoin(next_buff, ft_strsub(buff, 0, i));
							ft_memdel((void *)&next_buff);
						}
					}
					else
					{
						printf("|1|Point ");
						*line = ft_strsub(buff, 0, i);
						next_buff = ft_strsub(buff, i + 1, (count_char - i - 1));
					}
					return (1);
				}
				else if (buff[i] == '\0')
				{
					printf("|4|Point ");
					*line = ft_strsub(buff, 0, i);
					return (0);
				}
			}
			if (i == count_char)
			{
				if (next_buff)
				{
					printf("|5|Point ");
					*line = ft_strjoin(next_buff, ft_strsub(buff, 0, i));
				}
				else
				{
					printf("|6|Point ");
					next_buff = ft_strsub(buff, 0, count_char);
				}
			}
			count_char = read(fd, buff, BUFF_SIZE);
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
