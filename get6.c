#include <stdio.h>
#include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "getnextline.h"
char *read_joint(int fd, char *handOver);
char *ft_strdup(const char *string);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*get_line_from_handOver(char **handOver);
char	*ft_strchr(const char *s, int c);

char *get_line_from_handOver(char **handOver) 
{
    char *line;
    char *tmp;
    size_t i = 0;
     size_t j = 0;

    if (!*handOver)
        return (NULL);

    // 改行位置を探す
    while ((*handOver)[i] && (*handOver)[i] != '\n')
        i++;
    
    // 改行が見つかった場合
    if ((*handOver)[i] == '\n') {
        line = malloc(i + 2); // 改行含む + '\0'
        if (!line)
            return (NULL);
        line[i + 1] = '\0';
        while (j <= i) {
            line[j] = (*handOver)[j];
            j++;
        }
        //line[0] = (*handOver)[0];
        
        tmp = ft_strdup(*handOver + i + 1); // 残りを tmp にコピー
        free(*handOver);
        *handOver = tmp;
    } else {
        line = ft_strdup(*handOver); // 全体をコピー
        free(*handOver);
        *handOver = NULL;
    }

    return (line);
}

char *read_joint(int fd, char *handOver)
{
    char *tmp;
    ssize_t bytesread; 
     char *new_handOver;


    tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));//バッファサイズは1
    if(!tmp)
        return(NULL);
    bytesread = read(fd, tmp, BUFFER_SIZE);//読み込んだバイト数をリターン
    if(bytesread <= 0)
     {    free(tmp);
      return(handOver);
     }
    tmp[bytesread] = '\0';//めっちゃ大事
   // printf("%s\n", tmp);
     if (!handOver)
        handOver = ft_strdup(""); // handOverがNULLなら空文字列で初期化
    new_handOver = ft_strjoin(handOver, tmp);
  free(handOver); 
    free(tmp);
    return(new_handOver);
}

char	*ft_strjoin(char *s1, char *s2)
{
	// size_t	s1_len;
	// size_t	s2_len;
	char	*result;
    size_t i;
    size_t c;

    i = -1;
    c = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	// s1_len = ft_strlen(s1);
	// s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
    while(s1[++i] != '\0')
        result[i] = s1[i];
    while (s2[c] != '\0')
        result[i++] = s2[c++];
    result[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (result);
}
char	*ft_strdup(const char *string)//ある文字列をそのままコピーする
{
	char	*dst;
	size_t	len;
	size_t	i;

	i = 0;
	len = 1;
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (string[i])
	{
		dst[i] = string[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
char	*ft_strchr(const char *s, int c)
{
	char	cchar;

	cchar = (char)c;
	while (*s != '\0')
	{
		if (*s == cchar)
			return ((char *)s);
		s++;
	}
	if (cchar == '\0')
		return ((char *)s);
	else
		return (NULL);
}

char *get_next_line(int fd)
{
    static char *handOver; //前回実行からの受け継ぎ
    char *line;
    
    if(fd < 0 || BUFFER_SIZE <= 0)
    return(NULL);

     while (!handOver || !ft_strchr(handOver, '\n')) 
    {
        handOver = read_joint(fd, handOver);
        if (!handOver)
            return (NULL);
    }

    line = get_line_from_handOver(&handOver);
    return (line);
    //handOver = read_joint(fd, handOver);

    //return(handOver);

}

int	main(void)
{
	int		fd;
    char* return_str;
    
    return_str = "";
	fd = open("test.txt", O_RDONLY);
    if(fd < 0)
    { 
        perror("Error opening file");
        return(1);
    }

    return_str = get_next_line(fd);
        printf("%s\n", return_str); // 1文字出力
       
    return_str = get_next_line(fd);
         printf("%s\n", return_str); // 1文字出力
    // return_str = get_next_line(fd);
    //     printf("%s\n", return_str); // 1文字出力
    // return_str = get_next_line(fd);
    //     printf("%s\n", return_str); // 1文字出力
    // return_str = get_next_line(fd);
    //     printf("%s\n", return_str); // 1文字出力

        free(return_str); // メモリ解放

    close(fd);
	return(0);
}