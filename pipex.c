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

// needs to stay in lines and have the error handling taken care of

#include <stdio.h>
#include "./libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <string.h>

char	**ft_path_array(char **env)
{
	int		i;
	char	**path_array;

	path_array = NULL;
	i = 0;
	while (env[i]!=NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] ==
		'T' && env[i][3] == 'H' && env[i][4] == '=')
		{
			path_array = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break ;
		}
		i++;
	}
	path_array[i] = NULL;
	return (path_array);
}

// int ft_child_one(int fd0, int fd1, int pfd0, int pfd1, char **pat, char *av2)
// {
// 	int i;
// 	int access_to_command;
// 	char **command;
// 	close(pfd0);
// 	close(fd1);
// 	dup2(fd0, STDIN_FILENO);
// 	close(fd0);
// 	dup2(pfd1, STDOUT_FILENO);
// 	close(pfd1);
// 	i = 0;
// 	access_to_command = -1;
// 	// path_array = ft_path_array(env);
// 	command = ft_split(av2, ' ');
// 	if (command[0] == NULL)
// 	{
// 		perror("No command entered");
// 		return(667);
// 	}
// 	while (pat[i] != NULL)
// 	{
// 		access_to_command = access(ft_strjoin(pat[i], ft_strjoin("/", command[0])), F_OK);
// 		i++;
// 	}
// 	if (access_to_command < 0)
// 	{
// 		perror("Child one wrong command: ");
// 		// exit ;
// 	}
// 	return(access_to_command);
// }
void	ft_child_one(int fd0, int fd1, int pfd0, int pfd1)
{
	close(pfd0);
	close(fd1);
	dup2(fd0, STDIN_FILENO);
	close(fd0);
	dup2(pfd1, STDOUT_FILENO);
	close(pfd1);
}

int	main (int ac, char **av, char **env)
{
	if (ac == 5)
	{

	char	**path_array;
	char	**command;
	int		i;
	int 	fd[2];
	int		pfd[2];

	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] < 0)
			perror("Write infile and enter: ");
	fd[1] = open(av[4], O_CREAT | O_WRONLY, 0777);
	if (pipe(pfd) == -1)
		perror("Pipe failed: ");
	int id1 = fork();
	if(id1 == -1)
		perror("Fork failed: ");
	if (id1 == 0)
	{
		ft_child_one(fd[0], fd[1], pfd[0], pfd[1]);
		i = 0;
		path_array = ft_path_array(env);
		command = ft_split(av[2], ' ');
		if (command[0] == NULL)
			perror("No command entered");
		int access_to_command;
		access_to_command = -1;
		while (path_array[i] != NULL)
		{
			access_to_command = access(ft_strjoin(path_array[i], ft_strjoin("/", command[0])), F_OK);
			if (access_to_command == 0)
				execve(ft_strjoin(path_array[i], ft_strjoin("/", command[0])), command, env);
			i++;
		}
		perror("Child one wrong command: ");
	}
	else
	{
		int id2 = fork();
		if (id2 == 0)
		{
			close(pfd[1]);
			close(fd[0]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			i = 0;
			path_array = ft_path_array(env);
			command = ft_split(av[3], ' ');
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
			int status;
  			waitpid(id1, &status, 0); // wait for child to finish before exiting
			waitpid(id2, &status, 0); // wait for child to finish before exiting
		}
	}
	}
	else
	{
		printf("Wrong number of arrrrgs\n");
		return(777);
	}
}


