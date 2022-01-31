/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:25:30 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 05:09:42 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_execve(t_cmd command)
{
	pid_t	pid;
	int		status;

	// command.argv = malloc(sizeof(char*) * 3);
	// command.argv[0] = "/usr/bin/man";
	// command.argv[1] = "man";
	// command.argv[2] = NULL;
	// TODO: search in the PATH env variable for a match
	/*
	** if (!command)
	** 	return (printf(command not found...))
	*/
	// printf("command path %s\n",command.path);
	// FIXME: MINS-79
	pid = fork();
	if (pid == 0)
	{
		if (execve(command.path, command.argv, command.env) != 0)
			perror(strerror(errno));
	}
	else if (pid > 0)
		pid = wait(&status);
	status = WEXITSTATUS(status);
	return (status);
}
