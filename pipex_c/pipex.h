/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:22 by blackrider        #+#    #+#             */
/*   Updated: 2024/03/12 12:40:49 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define PATH            "PATH="
#define PATH_STD    "/usr/bin"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line_bonus.h"

char	*findexecpath(char **path, char **envp, char **argv, int pname);
char	**pathmaker(char **envp);