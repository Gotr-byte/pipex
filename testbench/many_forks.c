/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:54:44 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/25 17:34:30 by pbiederm         ###   ########.fr       */
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
	int id1 = fork();
	int id2 = fork();

	if (id1 == 0)
	{
		if (id2 == 0)
		{
			printf("I am protos y - child of x protos\n");
		}
		else
		{
			printf("I am protos x - parent of y protos, child of parent protos\n");
		}
	}
	else
	{
		if (id2 == 0)
		{
			printf("I am protos z second child of parent protos\n");
		}
		else
		{
			printf("I am the parent protos\n");		
		}
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		printf("Waited for a child to finish\n");
	}
}
