#include "lemin.h"

int     is_comment(char **buffer)
{
    if (**buffer == COM_CHAR)
    {
        *buffer = ft_strchr(*buffer, '\n') + 1;
        return (1);
    }
    return (0);
}

int     skip_blank(char **buffer)
{
    if (!ft_isblank(**buffer))
        return (0);
    while (**buffer && ft_isblank(**buffer))
        *buffer += 1;
    return (1);
}

int     skip_num(char **buffer)
{
    if (!ft_isdigit(**buffer))
        return (0);
    while (**buffer && ft_isdigit(**buffer))
        *buffer += 1;
    return (1);
}

int     skip_alnum(char **buffer)
{
    if (!ft_isalnum(**buffer))
        return (0);
    while (**buffer && ft_isalnum(**buffer))
        *buffer += 1;
    return (1);
}

int     last_flag(char *buffer, char *real_buffer)
{
    int len;

    (void)real_buffer;
    len = 0;
    while (buffer[len] && buffer[len] != '\n')
        len++;
    if (ft_strnequ(CMD_START, buffer, len))
        return (FSTART);
    if (ft_strnequ(CMD_END, buffer, len))
        return (FEND);
    return (0);
}