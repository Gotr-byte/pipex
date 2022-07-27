/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:15:47 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/25 15:44:37 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int id = fork();
	if (id == 0)
	{
		sleep(1);
	}
	int res = wait(NULL); 
	if ( res == -1)
	{
		printf("No children to wait for\n");
	}
	else
	{
		printf("Executed process %d\n", res);
	}

	printf("Child process id: %d Parent process id: %d\n", getpid(), getppid());
}