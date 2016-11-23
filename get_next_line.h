#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef	struct	s_var
{
	int				chaine;
	int				mot;
	int				lettre;
	struct s_var	*next;
}				t_var;

int			get_next_line(const int fd, char **line);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
void		ft_putstr(char const *s);
void		ft_putchar(char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		**ft_strsplit(char const *str, char charset);
char		*ft_concat_tab(char **tab);
char		*ft_strcat(char *s1, const char *s2);
void		ft_print_words_tables(char **tab);

#endif
