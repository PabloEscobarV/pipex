/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:18:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/12 11:40:20 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "pipex.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line_bonus.h"

char	**pathsetstd(char **path, char *pathstd)
{
	int		size;
	char	**tmp;

	if (!path)
		return (path);
	tmp = path;
	size = ft_strlen(pathstd);
	while (*tmp && ft_strncmp(*tmp, pathstd, size))
		++tmp;
	if (!tmp)
		return (path);
	pathstd = *path;
	*path = *tmp;
	*tmp = pathstd;
	return (path);
}

char	**pathaddchr(char **path, char ch)
{
	char	**tmp;

	if (!path)
		return (path);
	tmp = path;
	while (*tmp)
	{
		*tmp = ft_straddchrfree(*tmp, ch);
		++tmp;
	}
	return (path);
}

char	**pathmaker(char **envp)
{
	int		pathsize;
	char	*path_ol;
	char	**path;

	if (!envp || !(*envp))
		return (NULL);
	pathsize = ft_strlen(PATH);
	while (*envp && ft_strncmp(*envp, PATH, pathsize))
		++envp;
	if (!(*envp))
		return (NULL);
	path_ol = ft_strtrim(*envp, PATH);
	path = ft_split(path_ol, ':');
	free(path_ol);
	pathsetstd(path, PATH_STD);
	return (pathaddchr(path, '/'));
}

int	main(int argc, char **argv, char **envp)
{
	char	**path;

	if (argc < 2)
		return (0);
	path = pathmaker(envp);
	while (*path)
	{
		printf("%s\n", *path);
		++path;
	}
	return (0);
}