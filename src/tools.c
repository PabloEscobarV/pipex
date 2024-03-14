/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:25:43 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/14 13:03:28 by polenyc          ###   ########.fr       */
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
	pathname = pathexec(cmd, envp, 0);
	pathname = ft_straddchrfree(pathname, ' ');
	pathname = ft_strjoinfree(pathname, *argv, 0);
	result = ft_split(pathname, ' ');
	freematrix((void **)cmd);
	free(pathname);
	return (result);
}

void	printmatrix(char **data)
{

	while (*data)
	{
		printf("%s\n", *data);
		++data;
	}
}
