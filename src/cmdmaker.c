/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:55:06 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/13 15:58:16 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int *freepipefd(int *pipefd, int fd)
{
    if (fd > 0)
        close(fd);
    if (fcntl(pipefd[0], F_GETFL) > -1)
        close(pipefd[0]);
    if (fcntl(pipefd[1], F_GETFL) > -1)
        close(pipefd[1]);
    free(pipefd);
    return (NULL);
}

int *pipefd_m(int flag, char **filename)
{
    int *pipefd;
    int file;

    pipefd = malloc(2 * sizeof(int));
    file = -2;
    if (pipe(pipefd) == -1)
        return (NULL);
    if (!(*(filename + 1)))
    {
        file = open(*filename, O_WRONLY);
        if (dup2(pipefd[1], file) == -1)
            return (freepipefd(pipefd, file));
    }
    if (!flag)
    {
        file = open(*filename, O_RDONLY);
        if (dup2(pipefd[0], file) == -1)
            return (freepipefd(pipefd, file));
    }
    if (file > 0)
        close(file);
    return (pipefd);
}

int	cmdexecute(int argc, char **argv, char **envp, int v_read)
{
	int	    file;
    int     *pipefd;
    pid_t   pid;

    pipefd = pipefd_m(argc, argv + 1);
    if (!pipefd)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (!pid)
    {
        return (pipefd[]);
    }
}