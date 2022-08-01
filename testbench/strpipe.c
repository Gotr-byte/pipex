/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:14:24 by pbiederm          #+#    #+#             */
/*   Updated: 2022/08/01 18:14:24 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int	main(int ac, char **av)
{
	int fd[2];
	int pid;
	if(pipe(fd) == -1)
	{
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		return (2);
	}
	if (pid == 0)
	{
		// child process
		close(fd[0]);
		char str[200];
		printf("Input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';
		int n = strlen(str)+1;
		write(fd[1], &n, sizeof(int));

		if (write(fd[1], str, strlen(str) + 1) < 0)
		{
			return 3;
		}
		close(fd[1]);
	}
	else
	{
		// parent process
		close(fd[1]);
		char str[200];
		int n;
		if (read(fd[0], &n, sizeof(int)) <0 )
			return (5);
		if (read(fd[0], str, sizeof(char) * n) < 0)
			return(6);
		printf("Recieved %s", str);
		close (fd[0]);
		wait(NULL);
	}
	return (0);
}