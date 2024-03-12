/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:18:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/12 12:56:00 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	childproc(char **argv, char **envp, int *pipefd)
{
	char	*pathname;
	char	**path;
	char	**tmp;


	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	path = pathmaker(envp);

	pathname = findexecpath(path, envp, argv, 1);
	printf("%s\n", pathname);
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