/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:18:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/14 11:39:49 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

void	pipex(char **argv, char **envp)
{
	int	v_read;

	v_read = 0;
	++argv;
	while (*(argv + 1))
	{
		v_read = cmdexecute(argv, envp, v_read);
		if (v_read < 0)
		{
			perror("cmdexecute");
			exit(EXIT_FAILURE);
		}
		++argv;
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (0);
	pipex(argv, envp);
	return (0);
}