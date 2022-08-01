/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:49:36 by pbiederm          #+#    #+#             */
/*   Updated: 2022/08/01 09:49:36 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int ac, char** av)
{
	int pid = fork();
	if (pid == 0)
	{
		// chill process
		int file = open ("pingResults.txt", O_WRONLY | O_CREAT, 0777);
		if(file == -1)
		{
			return (2);
		}
		printf("fd to pingResults.txt %d", file);
		int file2 = dup2(file, 1);
		close(file);
		printf("file2 fd after replacing the STDIN %d", file2);
		int err = execlp("ping", "ping", "-c", "1", "google.com",	NULL);
		if (err == -1)
		{
			printf ("Could not find programme to execute\n");
			return (0);
		}
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
			if(statusCode == 0)
			{
				printf("Success\n");
			}
			else
			{
				printf("Failure with status code %d\n", statusCode);
			}
		}
		printf("Some post processing goes here\n");
	}
	return(0);
}