/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksiziva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:59:01 by ksiziva           #+#    #+#             */
/*   Updated: 2018/06/30 08:25:38 by ksiziva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int          check_new_line(char **stack, char **line)
{
    char            *tmp_stack;
    char            *strchr_stack;
    int             i;

    i = 0;
    strchr_stack = *stack;
    while (strchr_stack[i] != '\n')
        if (!strchr_stack[i++])
            return (0);
    tmp_stack = &strchr_stack[i];
    *tmp_stack = '\0';
    *line = ft_strdup(*stack);
    *stack = ft_strdup(tmp_stack + 1);
    return (1);
}

static  int         read_file(int fd, char *heap, char **stack, char **line)
{
    int             ret;
    char            *tmp_stack;

    while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
    {
        heap[ret] = '\0';
        if (*stack)
        {
            tmp_stack = *stack;
            *stack = ft_strjoin(tmp_stack, heap);
            free(tmp_stack);
            tmp_stack = NULL;
        }
        else
            *stack = ft_strdup(heap);
        if (check_new_line(stack, line))
            break ;
    }
    return (RET_VALUE(ret));
}

int                 get_next_line(int const fd, char **line)
{
    static char     *stack[MAX_FD];
    char            *heap;
    int             ret;
    int             i;

    if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd, stack[fd], 0) < 0) \
        || !(heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
        return (-1);
    if (stack[fd])
        if (check_new_line(&stack[fd], line))
            return (1);
    i = 0;
    while (i < BUFF_SIZE)
        heap[i++] = '\0';
    ret = read_file(fd, heap, &stack[fd], line);
    free(heap);
    if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
    {
        if (!ret && *line)
            *line = NULL;
        return (ret);
    }
    *line = stack[fd];
    stack[fd] = NULL;
    return (1);
}
