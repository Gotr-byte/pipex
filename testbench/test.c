/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:56:55 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/18 11:50:09 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Testing a script.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX 255
int main(void)
{
	char s[BUFFER_MAX + 1] = {"All pigs are equal, just some pigs are more equal than others"};
	char buffer[BUFFER_MAX + 1];

	int my_pipe[2];
	int readLenght;

	if ((pipe(my_pipe) < 0)){
		printf("Error creating a pipe \n");
		exit(EXIT_FAILURE);
	}
	// write message into the pipe
	write(myPipe[1], s, strlen(s)]);
	// read message from the pipe
	readLenght = read(myPipe[0], buffer , BUFFER_MAX);

	buffer[readLenght]=='';

	printf("%s", buffer);
	
	close (myPipe[0]);
	close (myPipe[1]);
	
	// printf( "Descriptors are %s and %s", my_pipe[1], my_pipe[2]);
	return 0;
}