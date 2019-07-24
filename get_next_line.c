#include "libft.h"
#include "stdio.h"

#define BUFF_SIZE 64

int     get_next_line(int fd, char **line)
{
    size_t  alloc_length = BUFF_SIZE;
    size_t  data_length = 0;
    char    *data = malloc(alloc_length);
    char    c;

    while(1)
    {
        read(fd, &c, 1);
        data[data_length] = c;
        if(data[data_length] == '\n' || data[data_length] == EOF)
            break;
        data_length++;
        if(data_length == alloc_length)
        {
            size_t new_length = alloc_length << 1;
            data = realloc(data, new_length);
            if(!data)
                return (-1);
            alloc_length = new_length;
        }
    }
    if(data[data_length] == '\n' || data[data_length] == EOF)
        data[data_length] = '\0';
    
    data = realloc(data, data_length);
    //ft_memcpy(*line, data, data_length);
    *line = data;
    //free(data);
    return (0);
}

int     main(int ac, char **av)
{
    int fd = open(av[1], O_RDONLY);
    char *line;

    int n = 10;
    while(n--)
    {
        get_next_line(fd, &line);
        printf("%s\n", line);
        //free(line);
    }

    return (0);
}
