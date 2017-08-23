#include "lemin.h"

static int  update_buffer(char **buffer, char *line, size_t *size, int i)
{
    char    *tmp;
    
    if (ft_strlen(line) + i + 1 >= *size)
    {
        tmp = ft_memalloc((*size *= 2));
        ft_strcpy(tmp, *buffer);
        ft_strdel(buffer);
        *buffer = tmp;
        return (update_buffer(buffer, line, size, i));
    }
    ft_strcpy(*buffer + i, line);
    i += ft_strlen(line);
    ft_strcpy(*buffer + i++, "\n");
    return (i);
}

char    *read_buffer(int fd)
{
    char        *buffer;
    char        *line;
    size_t     size;
    size_t     i;

    i = 0;
    size = 40096;
    buffer = ft_memalloc(size);
    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        if (*line == '\0')
        {
            ft_strdel(&line);
            break ;
        }
        i = update_buffer(&buffer, line, &size, i);
        ft_strdel(&line);
    }
    return (buffer);
}