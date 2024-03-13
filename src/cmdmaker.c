/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:55:06 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/13 18:52:50 by blackrider       ###   ########.fr       */
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

int *pipefd_f(int fd_read, char **filename)
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
    if (!fd_read)
    {
        file = open(*filename, O_RDONLY);
        if (dup2(pipefd[0], file) == -1)
            return (freepipefd(pipefd, file));
    }
    if (file > 0)
        close(file);
    return (pipefd);
}

int	startproc(char **cmd, char *pathname, char *filename, int *pipefd)
{
	int		file;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(pathname, cmd, NULL);
	perror("execve");
	return (-1);
}

int	cmdproc(char **cmd, char *pathname, int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(pathname, cmd, NULL);
	perror("execve");
	return (-1);
}

int	endproc(char **cmd, char *pathname, char *filename, int *pipefd)
{
	int		file;

	file = open(filename, O_WRONLY);
	if (file == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(file);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(pathname, cmd, NULL);
	perror("execve");
	return (-1);
}

int	cmdexecute(char **argv, char **envp, int v_read)
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
	if (v_read > 0)
	{
		dup2(pipefd[0], v_read);
		close(pipefd[0]);
		pipefd[0] = v_read;
	}
    pid = fork();
    if (pid == -1)
        return (-1);
    if (!pid)
    {
		if (!v_read)
			startproc(cmd, pathname, *argv, pipefd);
		else if (!(*(argv + 2)))
			endproc(cmd, pathname, *(argv + 1), pipefd);
		else
			cmdproc(cmd, pathname, pipefd);
    }
	wait(NULL);
	return (pipefd[]);
}