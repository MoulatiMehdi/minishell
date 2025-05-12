/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:37:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 14:31:28 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main(int ac, char *av[],char *env[])
{
	(void) ac;
	(void) env;
	t_cmd cmd2;
	cmd2.name = "exit";
	cmd2.args = &av[1];
	printf("\nenv status return -> %d \n", exit_cmd(&cmd2, 12));
}