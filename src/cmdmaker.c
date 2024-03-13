/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:55:06 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/13 18:04:59 by blackrider       ###   ########.fr       */
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

int	startproc(char **cmd, char *pathname, char *filename, int *pipefd)
{
	int		file;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return (-1);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(pathname, cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}



int	cmdexecute(int argc, char **argv, char **envp, int v_read)
{
    pid_t   pid;
    char    *pathname;
    int     *pipefd;
    char	**cmd;

    pipefd = pipefd_f(v_read, argv + 1);
    if (!pipefd)
        return (-1);
	cmd = ft_split(*argv, ' ');
	pathname = pathexec(cmd, NULL, 0);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (!pid)
    {
        return (pipefd[]);
    }
}