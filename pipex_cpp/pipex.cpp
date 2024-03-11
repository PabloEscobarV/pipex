/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:48:41 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/11 21:06:29 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C"
{
    #include <unistd.h>
	#include "../libft/libft.h"
	#include "../get_next_line/get_next_line_bonus.h"
}
#include <iostream>
#include <cstdlib>
#include <string>
#include "pipex.h"

using namespace std;

char	**setstandartpath(char **path, const char *st_path)
{
	char		**tmp;
	char		*swap_tmp;

	tmp = path;
	while (ft_strncmp(*tmp, st_path, ft_strlen(st_path)))
		++tmp;
	if (!(*tmp))
		return (path);
	swap_tmp = *path;
	*path = *tmp;
	*tmp = swap_tmp;
	return (path);
}

char	**pathmaker(char **envp)
{
	char		*envptrim;
	char		**res;
	char		**tmp;

	if (!envp || !(*envp))
		return (nullptr);
	while (ft_strncmp(*envp, PATH, ft_strlen(PATH)))
		++envp;
	envptrim = ft_strtrim(*envp, PATH);
	res = ft_split(envptrim, ':');
	if (!res)
		return (res);
	tmp = res;
	while (*tmp)
	{
		*tmp = ft_straddchrfree(*tmp, '/');
		++tmp;
	}
	free(envptrim);
	return (setstandartpath(res, STANDARTPATH));
}

char	*findexecut(char **path, const char *execute)
{
	char	*fullpath;

	fullpath = ft_strjoin(*path, execute);
	while (*path && access(fullpath, F_OK))
	{
		free(fullpath);
		++path;
		fullpath = ft_strjoin(*path, execute);
	}
	return (fullpath);
}

int	childproc(char **argv, char **envp, int *pipefd)
{
	char	**path;
	char	*execute;

	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	path = pathmaker(envp);
	execute = findexecut(path, *(argv + 1));
	if (execve(execute, argv + 1, NULL) == -1)
	{
		perror("execve");
		cout << "ERROR!!!\n";
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	char	*data;
	char	**path;
	string	str;

	if (pipe(pipefd) == -1)
	{
		cout << "Bad chanal allocation!!!\n";
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		if (childproc(argv, envp, pipefd))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (pid)
	{
		close(pipefd[1]);
		data = get_next_line(pipefd[0]);
		while (data)
		{
			str += data;
			data = get_next_line(pipefd[0]);
		}
		cout << "RESULT:\n" << str << endl;
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	}
	return (0);
}