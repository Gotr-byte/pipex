/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:43:47 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/25 10:52:53 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

// int main (int ac, char **av)
int main (void)
{
	printf ("Code starts here\n");
	int id = fork();
	fork();
	fork();
	if (id == 0)
	{
		printf ("Live long and prosper I am the young Volcan so my id is %d \n", id);
	}
	else
	{
		// the parent process executes twice
		printf ("I am your future self, my id is %d \n", id);
	}
}