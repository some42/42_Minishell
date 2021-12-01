/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:53:12 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 03:57:38 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "builtin.h"
# define  _GNU_SOURCE
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

# define SHELL_NAME "minishell"

// # define PIPE "|"
// # define DQUOTE "\""
// # define QUOTE "\'"
// # define DOLLAR "$"
// # define DELIMITER "<<"
// # define IN "<"
// # define APPEND ">>"
// # define OUT ">"

# define CLEAR      0b00000000 // 0
# define PIPE       0b00000001 // 1
# define OUT        0b00000010 // 2
# define DELIMITER  0b00000011 // 3
# define IN         0b00000100 // 4
# define APPEND     0b00000101 // 5
# define QUOTE      0b00000110 // 6
# define DOLLAR     0b00000111 // 7
# define DQUOTE     0b00001000 // 8

typedef struct s_mini
{
	int		argc;
	char	**argv;
	char	**env;
	char	*line;
	char	*line_cpy;
	char	*buffer;
	int		flag;
	// int		errno;
	int		p_error;
	t_list	*l_env;
	t_list	*cmds;
	t_list	*delimiters;
	t_list	*chars;
	int		(*p[9])(struct s_mini*);
}				t_mini;

typedef struct s_cmd
{
	int		argc;
	char	**argv;
	char	**env;
	t_list	*l_argv;
	int		infile;
	int		outfile;
}				t_cmd;

typedef struct s_chars
{
	char	c;
	int		flag;
	int		end;
}				t_chars;

/*
** Parser functions
*/
int		parse(t_mini *mini);
int		specials(t_mini *mini);
int		parse_clear(t_mini *mini);
int		parse_pipe(t_mini *mini);
int		parse_dquote(t_mini *mini);
int		parse_quote(t_mini *mini);
int		parse_dollar(t_mini *mini);
int		parse_delimiter(t_mini *mini);
int		parse_in(t_mini *mini);
int		parse_append(t_mini *mini);
int		parse_out(t_mini *mini);

void	make_command(t_mini *mini);
void	make_argv(t_mini *mini);

/*
** Exec functions
*/
int		ft_execve(t_cmd command);

#endif