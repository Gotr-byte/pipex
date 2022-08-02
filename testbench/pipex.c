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
#include <sys/errno.h>
// Get all the paths from env
char **ft_path_array(char** env)
{
	int i;
	char **path_array;

	path_array = NULL;
	i = 0;
	while (env[i]!=NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
		//if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
		{
			path_array = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break;
		}
		i++;
	}
		path_array[i] = NULL;
		return(path_array);
}


int main (int ac, char **av, char **env)
{
	char	**path_array;
	char	**command;
	char	*path;
	int		i;
	int 	fd[2];
	int		pfd[2];

	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[4], O_CREAT | O_WRONLY, 0777);
	if (pipe(pfd) == -1)
	{
		printf ("An error occured while calling for pipe\n");
		return (1);
	}
	int id1 = fork();
	if(id1 == -1)
	{
		perror("Fork failed");
		return (11);
	}

	if (id1 == 0)
	{
		// printf("I am protos x - parent of y protos, child of parent protos\n");
		close(pfd[0]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		i = 0;
		path_array = ft_path_array(env);
		command = ft_split(av[2], ' ');

		while (path_array[i] != NULL)
		{
			if(access(ft_strjoin(path_array[i], ft_strjoin("/", command[0])), F_OK) == 0)
				execve(ft_strjoin(path_array[i], ft_strjoin("/", command[0])), command, env);
			i++;
		}
	}
	else
	{
		int id2 = fork();
		if (id2 == 0)
		{
			// printf("I am protos z second child of parent protos\n");
			// Below goes to the second child
			close(pfd[1]);
			close(fd[0]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			i = 0;
			path_array = ft_path_array(env);
			command = ft_split(av[3], ' ');
			int n = 0;
			// while( path_array[n] != NULL)
			// {
			// 	fprintf(2, "%s", path_array[n]);
			// 	n++;
			// }

			while (path_array[i] != NULL)
			{
				if(access(ft_strjoin(path_array[i], ft_strjoin("/", command[0])), F_OK) == 0)
					execve(ft_strjoin(path_array[i], ft_strjoin("/", command[0])), command, env);
				i++;
			}
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			close(pfd[1]);
			close(pfd[0]);
			// while (waitpid(id1) != -1)
			// {
			// 	printf("Waited for a child to finish\n");
			// }
			// while (waitpid(id2) != -1)
			// {
			// 	printf("Waited for a child to finish\n");
			// }
			int status;
  			waitpid(id1, &status, 0); // wait for child to finish before exiting
			waitpid(id2, &status, 0); // wait for child to finish before exitin
			// Parent process waits for child processes to finish
			// printf("I am the parent protos\n");		
		}
	}
}


