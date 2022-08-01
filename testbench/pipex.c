/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:54:53 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/31 15:54:53 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include <unistd.h>
#include <fcntl.h>

char **ft_path_array(char** env)
{
	int i;
	char **path_array;

	path_array = NULL;
	i = 0;
	while (env[i]!=NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
		{
			path_array = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break;
		}
		i++;
	}
		path_array[i] = '\0';
		return(path_array);
}


int main (int ac, char **av, char **env)
{
	char** 	path_array;
	int		i;
	int 	fd;
	fd = open(av[2], O_CREAT | O_RDWR | O_TRUNC, 0777);

	dup2(fd,1);
	close(fd);
	i = 0;
	path_array = ft_path_array(env);
	while (path_array[i] != NULL)
	{
		if((access(ft_strjoin(path_array[i], ft_strjoin("/", av[1])), F_OK)) == 0)
			execve(ft_strjoin(path_array[i], ft_strjoin("/", av[1])), &av[1], env);
		i++;
	}
}