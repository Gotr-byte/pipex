/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppfk_practice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:37:05 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/26 17:38:18 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main ()
{
	int num_arr[] = {1, 1 ,1 ,2 , 1 , 1, 1};
	int arr_size = sizeof(num_arr) / sizeof(int);
	int fd[2];
	int fd1[2];
	int start;
	int end;
	int end2;
	int sub_sum;

	if (pipe(fd) == -1)
	{
		printf("Error while making pipe");
		return 1;
	}
	int id = fork();
	if (id == -1)
	{
		printf("Err with fork");
		return 2;
	}
	if (id == 0)
	{
		// start = 0;
		end = arr_size/2;
		write(fd[1], &end, sizeof(int));

		// printf ("%d", sub_sum);
		// return (0);
	}
	else
	{
		// if (pipe(fd1) == -1)
		// {
		// 	printf("Error while making pipe");
		// 	return 1;
		// }
		int id2 = fork();
		if (id2 == -1)
		{
			printf("Err with fork");
			return 2;
		}
		if (id2 == 0)
		{
			// start = arr_size/2;
			end = 19;
			write(fd[1], &end, sizeof(int));
		}
		else
		{
			wait(NULL);
			int reads;
			int reads2;
			read(fd[0], &reads, sizeof(int));
			printf ("The first child reads %d\n", reads);
			read(fd[0], &reads, sizeof(int));
			printf ("The second child reads too %d\n", reads);
		}
	}
		// sub_sum = 0;
		// int i;
		// i = start;
		// while (i < end)
		// {
		// 	sub_sum = sub_sum + num_arr[i];
		// 	i++;
		// }
		// printf ("Calculated partial sum: %d\n", sub_sum);

}

// int main (void)
// {
// 	int fd[2];
// 	//fd[1] - write
// 	//fd[0] - read
// 	if (pipe(fd) == -1)
// 		{
// 			printf ("An error occured while calling for pipe\n");
// 			return (1);
// 		}
// 	int id = fork();
// 	if (id == -1)
// 	{
// 		printf("An error occured while forking the process\n");
// 	}
// 	if (id == 0)
// 	{
// 		close (fd[0]);
// 		int x;
// 		printf ("How many drones?\n");
// 		scanf ("%d", &x);
// 		if (write (fd[1], &x , sizeof(int)) == -1)
// 		{
// 			printf ("An error occured while writing to the pipe\n");
// 			return (2);
// 		}
// 		close (fd[1]);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close (fd[1]);
// 		int y;
// 		if (read(fd[0], &y, sizeof(int)) == -1)
// 		{
// 			printf ("An error occured while reading from the pipe\n");
// 			return (2);
// 		}
// 		close (fd[0]);
// 		printf ("Got from child protos %d drones\n", y);
// 	}
// }