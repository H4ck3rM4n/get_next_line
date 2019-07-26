#include "get_next_line.h"

static  t_list  *get_file(int fd, t_list **files)
{
    t_list  *found;

    found = *files;
    while(found != NULL)
    {
        if((int)found->content_size == fd)
            return(found);
        found = found->next;
    }

    ft_lstadd(files, ft_lstnew("\0", fd));
    return (*files);
}

int             get_next_line(int fd, char **line)
{
    static  t_list  *files;
    size_t  byte_read;
    size_t  offset;
    char    *buffer;

    buffer = (char*)malloc(BUFF_SIZE + 1);
    t_list  *file;

    file = get_file(fd, &files);
    if(!file)
        return (-1);

    while((byte_read = read(fd, buffer, BUFF_SIZE)) == BUFF_SIZE)
    {
        buffer[byte_read] = '\0';
        file->content = ft_strjoin(file->content, buffer);
    }
    
    buffer[byte_read] = '\0';
    file->content = ft_strjoin(file->content, buffer);
    
    int i = 0;
    while((((char*)(file->content))[i] != '\n' && ((char*)(file->content))[i] != EOF) && i < ft_strlen(file->content))
        i++;

    *line = ft_strsub(file->content, 0, i);
    
    if(ft_strchr(file->content, '\n'))
    {
        ft_strcpy(file->content, ft_strchr(file->content, '\n') + 1);
        return (1);
    }
    else
    {
        ft_strcpy(file->content, ft_strsub(file->content, 0, ft_strlen(file->content)));
        return(0);
    }

    return (0);
}
