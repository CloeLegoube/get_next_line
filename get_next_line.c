#include "get_next_line.h"

// typedef	struct	s_part
// {
// 	char			*content;
// 	size_t			content_size;
// 	struct s_part	*next;
// }				t_part;

int get_next_line(const int fd, char **line)
{
	int		count_char;
	int		i;
	char	buff[BUFF_SIZE + 1];
	static char *next_buff;

	while ((count_char = read(fd, buff, BUFF_SIZE)))
	{
		i = 0;
		while (i < count_char)
		{
			if (buff[i] == '\n')
			{
				if (next_buff)
					*line = ft_strjoin(next_buff, ft_strsub(buff, 0, i));
				else
				{
					*line = ft_strsub(buff, 0, i);
					next_buff = ft_strsub(buff, i + 1, (count_char - i + 1));
				}
				return (1);
			}
			else if (buff[i] == '\0')
			{
				*line = ft_strsub(buff, 0, i);
				return (0);
			}
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
		printf("%s", *line);
		get_next_line(fd, line);
		printf("%s", *line);
		get_next_line(fd, line);
		printf("%s", *line);
		get_next_line(fd, line);
		printf("%s", *line);
		if (ft_close(fd) == 1)
			return (1);
	}
	return (0);

}
