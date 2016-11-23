#include "get_next_line.h"
#include <stdio.h>

static int		len_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		i++;
	}
	return (i);
}

static int		ft_count_char(char **tab)
{
	int		i;
	int		j;
	int		count;

	i = 1;
	count = 0;
	while (tab[i++])
	{
		j = 0;
		while (tab[i][j++])
			count++;
		count++;
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
	string = (char*)malloc((count + 1) * sizeof(*string));
	i = 1;
	count = 0;
	while (tab[i++])
	{
		j = -1;
		while (tab[i][++j])
			string[count++] = tab[i][j];
		string[count++] = i < len_tab(tab) ? '\n' : 0;
	}
	return (string);
}

int		get_next_line(const int fd, char **line)
{
	int			count_char;
	int			i;
	char		buff[BUFF_SIZE + 1];
	static char	*next_buff;
	char		**tab;

	while ((count_char = read(fd, buff, BUFF_SIZE)))
	{
		i = 0;
		while (i < count_char)
		{
			if (buff[i] == '\n')
			{
				if (next_buff)
				{
					tab = ft_strsplit(next_buff, '\n');
					//ft_print_words_tables(tab);
					if (len_tab(tab) > 1)
					{
						free(*line);
						*line = NULL;
						*line = (char *)malloc((ft_strlen(tab[0]) + 1) * sizeof(*line));
						*line = tab[0];
						free(next_buff);
						next_buff = NULL;
						next_buff = ft_concat_tab(tab);
					}
					else
					{
						free(*line);
						*line = NULL;
						*line = ft_strjoin(next_buff, ft_strsub(buff, 0, i));
					}
				}
				else
				{
					*line = ft_strsub(buff, 0, i);
					next_buff = ft_strsub(buff, i + 1, (count_char - i - 1));
				}
				return (1);
			}
			else if (buff[i] == '\0')
			{
				*line = ft_strsub(buff, 0, i);
				return (0);
			}
			else
				count_char++;
			i++;
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
		printf("%s\n", *line);
		get_next_line(fd, line);
		printf("%s\n", *line);
		get_next_line(fd, line);
		printf("%s\n", *line);
		get_next_line(fd, line);
		printf("%s\n", *line);
		get_next_line(fd, line);
		printf("%s\n", *line);
		if (ft_close(fd) == 1)
			return (1);
	}
	return (0);

}
