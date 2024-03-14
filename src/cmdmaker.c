/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:55:06 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/14 11:40:41 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	startproc(char **cmdpath, char *filename, int *pipefd)
{
	int		file;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(*cmdpath, cmdpath + 1, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	cmdproc(char **cmdpath, int *pipefd, int v_read)
{
	dup2(v_read, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(v_read);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(*cmdpath, cmdpath + 1, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	endproc(char **cmdpath, char *filename, int *pipefd, int v_read)
{
	int		file;

	file = open(filename, O_WRONLY);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(v_read, STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(v_read);
	close(file);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(*cmdpath, cmdpath + 1, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	cmdexec(char **cmdpath, char **argv, int *pipefd, int v_read)
{
	int	file;

	file = -2;
	if (!v_read)
		return (startproc(cmdpath, *argv, pipefd));
	if (!(*(argv + 2)))
		return (endproc(cmdpath, *(argv + 1), pipefd, v_read));
	return (cmdproc(cmdpath, pipefd, v_read));
}

int	cmdexecute(char **argv, char **envp, int v_read)
{
    pid_t   pid;
    int     *pipefd;
    char	**cmdpath;

    pipefd = pipefd_f(v_read, argv + 1);
    if (!pipefd)
        return (-1);
	cmdpath = pathcmd(argv, envp);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (!pid)
		return (cmdexec(cmdpath, argv, pipefd, v_read));
	wait(&pid);
	freematrix((void **)cmdpath);
	close(pipefd[1]);
	if (!WIFEXITED(pid))
	{
		close(pipefd[0]);
		pipefd[0] = -1;
	}
	pid = pipefd[0];
	free(pipefd);
	return (pid);
}
