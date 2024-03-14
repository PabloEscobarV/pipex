/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:25:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/14 11:31:14 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int		*freepipefd(int *pipefd)
{
    if (fcntl(pipefd[0], F_GETFL) > -1)
        close(pipefd[0]);
    if (fcntl(pipefd[1], F_GETFL) > -1)
        close(pipefd[1]);
    free(pipefd);
    return (NULL);
}

void	freematrix(void **data)
{
	void	**tmp;

	if (!data || !(*data))
		return ;
	tmp = data;
	while (*tmp)
	{
		free(*tmp);
		++tmp;
	}
	free(data);
}

char	**pathcmd(char **argv, char **envp)
{
	char	*pathname;
	char	**cmd;
	char	**result;

	cmd = ft_split(*argv, ' ');
	pathname = ft_straddchrfree(pathexec(cmd, envp, 0), ' ');
	pathname = ft_strjoinfree(pathname, *argv, 0);
	result = ft_split(pathname, ' ');
	while (*cmd)
	{
		free(cmd);
		++cmd;
	}
	free(cmd);
	free(pathname);
	return (result);
}
