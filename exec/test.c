/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:26:15 by zyamli            #+#    #+#             */
/*   Updated: 2024/03/11 18:32:19 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>

int main()
{
	char *args[] = {"ls", "-l", NULL};
	execve("/bin/ls", args, NULL);
	printf("makhdamch/n");
}