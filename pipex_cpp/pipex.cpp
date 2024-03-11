/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:48:41 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/11 12:54:45 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C"
{
    #include <unistd.h>
}
#include <iostream>
#include <cstdlib>

using namespace std;

int	main(void)
{
	pid_t	pid;
	int		pipepid[2];

	if (pipe(pipepid) == -1)
	{
		cout << "Bad chanal allocation!!!\n";
		exit(EXIT_FAILURE);
	}

	return (0);
}