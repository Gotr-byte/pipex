/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ff_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:15:09 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/28 10:16:15 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main (int ac, char **av)
{
	int arr[5];
	// int arr2[5];
	int fd = open ("sum", O_RDONLY);
	int fd2 = open ("sumback", O_WRONLY);
	printf("Opening\n");
	if (fd == -1)
	{
		printf("Err while opening\n");
		return(1);
	}
	printf("Reading\n");
	int i;
	for(i = 0; i < 5; i++)
	{
		if (read(fd, &arr[i], sizeof(int)) == -1)
		{
			printf("Err while reading\n");
			return (2);
		}
		// arr2[i] = arr[i];
		// if (write(fd2, &arr2[i], sizeof(int)) == -1)
		if (write(fd2, &arr[i], sizeof(int)) == -1)
		{
			printf("Err while writing\n");
			return (3);	
		}
		printf("Recieved %d & sent back %d\n", arr[i], arr[i]);
	}
	return(0);
}