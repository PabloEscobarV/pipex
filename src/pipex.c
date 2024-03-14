/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:18:26 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/14 13:22:15 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

void	pipex(char **argv, char **envp)
{
	int	v_read;

	v_read = 0;
	argv += 2;
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
	// char	**argv_;
	// char	*data;

	if (argc < 5)
		return (0);
	// printf("Enter a data:\n");
	// data = get_next_line(0);
	// argv_ = ft_split(data, '|');
	pipex(argv, envp);
	return (0);
}

// ./pipe|../test/file_in.txt|wc|wc -l|fileout.txt