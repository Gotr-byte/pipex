/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:43:42 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/27 16:33:47 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

int main (void)
{
	printf ("Start of programme\n");
	if (mkfifo("Nexus", 0777) == -1)
		{
			if (errno != EEXIST)
			{
				printf ("Could not create fifo file\n");
				return (1);
			}
		}
	printf("After mkfifo \n");
	printf("Opening\n");
	int fd = open("myfifo1", O_WRONLY);
	printf("Opened\n");
	int x = 97;
	printf("Writing\n");
	write(fd, &x, sizeof(x));
	// if (write(fd, &x, sizeof(x)) == -1)
	// {
	// 	printf("Err while writing");
	// 	return (2);
	// }
	close (fd);
	return (0);
}