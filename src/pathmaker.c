/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmaker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:17:35 by polenyc           #+#    #+#             */
/*   Updated: 2024/03/12 16:51:10 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

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

char	*findexecpath(char **path, char **argv, int pname)
{
	char	*pathname;

	if (!path)
		return (NULL);
	pathname = ft_strjoin(*path, argv[pname]);
	while (*path && access(pathname, F_OK))
	{
		free(pathname);
		pathname = ft_strjoin(*path, argv[pname]);
		++path;
	}
	if (*path)
		return (pathname);
	free(pathname);
	return (NULL);
}
