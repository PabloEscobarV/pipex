/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:18:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/12 16:52:02 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	childproc(char **argv, char **envp, int *pipefd)
{
	int		file;
	char	*pathname;
	char	**path;

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
	path = pathmaker(envp);
	pathname = findexecpath(path, argv, 2);
	execve(pathname, argv + 2, envp);
	perror("execve");
	exit(EXIT_FAILURE);
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

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	__pid_t	pid;

	if (argc < 2)
		return (0);
	if (pipe(pipefd) == -1)
	{
		printf("ERROR\n");
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (!pid)
	{
		childproc(argv, envp, pipefd);
		return (0);
	}
	parentprov(pipefd);
	return (0);
}