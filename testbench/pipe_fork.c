/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:53:23 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/26 13:30:13 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main (void)
{
	int fd[2];
	//fd[1] - write
	//fd[0] - read
	if (pipe(fd) == -1)
		{
			printf ("An error occured while calling for pipe\n");
			return (1);
		}
	int id = fork();
	if (id == -1)
	{
		printf("An error occured while forking the process\n");
	}
	if (id == 0)
	{
		close (fd[0]);
		int x;
		printf ("How many drones?\n");
		scanf ("%d", &x);
		if (write (fd[1], &x , sizeof(int)) == -1)
		{
			printf ("An error occured while writing to the pipe\n");
			return (2);
		}
		close (fd[1]);
	}
	else
	{
		wait(NULL);
		close (fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf ("An error occured while reading from the pipe\n");
			return (2);
		}
		close (fd[0]);
		printf ("Got from child protos %d drones\n", y);
	}
}