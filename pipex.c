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

struct	mediatior
{
	char	**path_array;
	char	**command;
	int		i;
	int 	fdr;
	int		fdw;
	int		pfd[2];
	int		access_to_command;
	int		status;
	int		id_greg;
	int		id_sara;
}m;

int	ft_child_one(int fd0, int fd1, int pfd0, int pfd1, char	**av, char **env)
{
	close(pfd0);
	close(fd1);
	dup2(fd0, STDIN_FILENO);
	close(fd0);
	dup2(pfd1, STDOUT_FILENO);
	close(pfd1);
	m.i = 0;
	m.path_array = ft_path_array(env);
	m.command = ft_split(av[2], ' ');
	if (m.command[0] == NULL)
	{
		perror("No command entered");
		exit(666);
	}
	m.access_to_command = -1;
	while (m.path_array[m.i] != NULL)
	{
		m.access_to_command = access(ft_strjoin(m.path_array[m.i], ft_strjoin("/", m.command[0])), F_OK);
		if (m.access_to_command == 0)
			execve(ft_strjoin(m.path_array[m.i], ft_strjoin("/", m.command[0])), m.command, env);
		m.i++;
	}
	perror("Child one wrong command");
	exit(667);
}

void	ft_child_two(int fdr, int fdw, int pfd0, int pfd1, char **av, char **env)
{
	close(pfd1);
	close(fdr);
	dup2(pfd0, STDIN_FILENO);
	close(pfd0);
	dup2(fdw, STDOUT_FILENO);
	close(fdw);
	m.i = 0;
	m.path_array = ft_path_array(env);
	m.command = ft_split(av[3], ' ');
	if (m.command[0] == NULL)
	{
		perror("Sara didn't recieve command");
		exit (668);
	}
	while (m.path_array[m.i] != NULL)
	{
		if(access(ft_strjoin(m.path_array[m.i], ft_strjoin("/", m.command[0])), F_OK) == 0)
			execve(ft_strjoin(m.path_array[m.i], ft_strjoin("/", m.command[0])), m.command, env);
		m.i++;
	}
	perror("Sara got the wrong command");
	exit (668);
}

void	parent(int fdr, int fdw, int pfd0, int pfd1, int id_greg, int id_sara)
{
	close(fdr);
	close(fdw);
	close(pfd1);
	close(pfd0);
	waitpid(id_greg, &m.status, 0); // wait for child to finish before exiting
	waitpid(id_sara, &m.status, 0); // wait for child to finish before exiting
	exit(800);
}


void ft_err_infile (void)
	{
		perror("Write infile and enter");
		exit(701);
	}

void ft_err_pipe (void)
	{
		perror("Pipe failed");
		exit(702);
	}

void ft_err_fork (void)
	{
		perror("Fork failed");
		exit(703);
	}

void ft_err_ac (void)
	{
		printf("Wrong number of arrrrgs\n");
		exit(777);
	}

int	main (int ac, char **av, char **env)
{
	if (ac == 5)
	{
	m.fdr = open(av[1], O_RDONLY);
	if (m.fdr < 0)
		ft_err_infile();
	m.fdw = open(av[4], O_CREAT | O_WRONLY, 0777);
	if (pipe(m.pfd) == -1)
		ft_err_pipe();
	m.id_greg = fork();
	if(m.id_greg == -1)
		ft_err_pipe();
	if (m.id_greg == 0)
		ft_child_one(m.fdr, m.fdw, m.pfd[0], m.pfd[1], av, env);
	else
	{
		m.id_sara = fork();
		if (m.id_sara == 0)
			ft_child_two(m.fdr, m.fdw, m.pfd[0], m.pfd[1], av, env);
		else
			parent(m.fdr, m.fdw, m.pfd[0], m.pfd[1], m.id_greg, m.id_sara);
	}
	}
	else
		ft_err_ac();
}


