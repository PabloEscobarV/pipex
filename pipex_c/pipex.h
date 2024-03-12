/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:22 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/12 13:53:18 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define PATH            "PATH="
#define PATH_STD    "/usr/bin"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line_bonus.h"

char	**pathmaker(char **envp);
char	*findexecpath(char **path, char **envp, char **argv, int pname);
