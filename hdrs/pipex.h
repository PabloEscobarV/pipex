/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:22 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/14 11:29:42 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define PATH            "PATH="
#define PATH_STD    "/usr/bin"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line_bonus.h"

int		cmdexecute(char **argv, char **envp, int v_read);
////////////////////////////PATH\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
char	**pathmaker(char **envp);
char	*findexecpath(char **path, char **argv, int pname);
char	*pathexec(char **argv, char **envp, int pname);
////////////////////////////TOOLS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
int		*freepipefd(int *pipefd);
void	freematrix(void **data);
char	**pathcmd(char **argv, char **envp);



