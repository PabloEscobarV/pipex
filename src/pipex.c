/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:18:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/13 14:55:38 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

void	freematrix(void **matrix)
{
	void	**tmp;

	if (!matrix || !(*matrix))
		return ;
	tmp = matrix;
	while (*matrix)
	{
		free(*matrix);
		++matrix;
	}
	free(tmp);
}

int	parentprov(int *pipefd)
{
	char	*data;
	char	*gnl_tmp;

	if (!pipefd)
		return (-1);
	close(pipefd[1]);
	gnl_tmp = get_next_line(pipefd[0]);
	data = NULL;
	while (gnl_tmp)
	{
		data = ft_strjoinfree(data, gnl_tmp, 2);
		gnl_tmp = get_next_line(pipefd[0]);
	}
	printf("RESULT:\t%s", data);
	close(pipefd[0]);
	return (0);
}

void	startproc(char **argv, char **cmd, char *pathname, int *pipefd)
{
	int		file;

	file = open(*(argv + 1), O_RDONLY);
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
	execve(pathname, cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	pipex(char **argv, char **envp)
{
	pid_t	pid;
	pid_t	status;
	int		pipefd[2];
	char	*pathname;
	char	**cmd;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cmd = ft_split(*(argv + 2), ' ');
	pathname = pathexec(cmd, envp, 0);
	pid = fork();
	if (!pid)
	{
		startproc(argv, cmd, pathname, pipefd);
		return ;
	}
	if (waitpid(pid, &status, 0) != -1)
		printf("STATUS:\t%d\n", status);
	parentprov(pipefd);
	free(pathname);
	freematrix((void **)cmd);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	pipex(argv, envp);
	return (0);
}