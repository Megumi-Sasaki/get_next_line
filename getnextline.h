# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#endif

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
#define BUFFER_SIZE 1

int gn_getchar(void);
void gn_putchar(char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
#endif