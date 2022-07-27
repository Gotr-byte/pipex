/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:03:26 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/27 17:14:25 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main (int ac, char **av)
{
	int arr[5];
	srand(time(NULL));
	int i;
	for(i = 0; i < 5; i++)
	{
		arr[i] = rand() % 100;
	}
	int fd = open("sum", O_WRONLY);
	if (fd == -1)
	{
		return (1);
	}
	for (i = 0; i < 5; i++)
	{
		if (write(fd, &arr[i], sizeof(int)) == -1)
		{
			return(2);
		}
		printf("Wrote %d\n", arr[i]);
	}
	close (fd);
	return(0);
}