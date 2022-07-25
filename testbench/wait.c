/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:04:11 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/25 11:36:33 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The order of the proccesses is decided by the operating system.
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void)
{
	int id = fork();
	int hp;
	if (id == 0)
	{
		hp = 4;
		// printf ("Apprentice hp: %d", hp);
	}
	else
	{
		hp = 16;
		// printf ("Sage hp %d", hp);
	}
	if (id != 0)
	{
		wait(0);
	}
	int health_buff;
	health_buff = hp; 
	while (health_buff < hp + 5)
	{
		printf("Buffed %d health: %d ", id, health_buff);
		// fflush(stdout);
		health_buff++;
	}
	if (id != 0)
	{
	printf("\n");
	}

}