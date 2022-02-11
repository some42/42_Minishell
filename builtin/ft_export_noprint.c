/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_noprint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 06:37:29 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 19:35:49 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**free_malloc(char **tab)
{
	unsigned int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

/*
** builtin: export
** export -> prints "declare -x" and then, env variable. Env variables are
** 	sorted using their name using ascii.
** export (name) -> prints '\n' and then, adds (name) to env vars.
** More than the first parametter has to be handled
** ! Although env prints just env variables with value, export prints everything
** 	even if there is no value set for that env variable.
*/

static inline t_list
	*lst_cpy(t_list *lst)
{
	t_list	*cpy;
	t_list	*lst_node;

	if (!lst)
		return (NULL);
	lst_node = lst;
	cpy = ft_lstnew(lst_node->content);
	lst_node = lst_node->next;
	while (lst_node)
	{
		ft_lstadd_back(&cpy, ft_lstnew(lst_node->content));
		lst_node = lst_node->next;
	}
	return (cpy);
}

static inline int
	ft_is_valid_identifier(char *str)
{
	return (!ft_isalpha(*str));
}

int
	ft_export_noprint(int argc, char **argv, t_list *env)
{
	char	**arg;
	t_list	*cpy;
	int		i;

	(void)cpy;
	if (argc >= 2)
	{
		i = 0;
		while (argv[i++])
		{
			arg = ft_split(argv[i], '=');
			if (arg && arg[0])
			{
				if (ft_is_valid_identifier(arg[0]))
				{
					free_malloc(arg);
					continue ;
				}
				if (arg[1])
				{
					if (*arg[1] == '\'' || *arg[1] == '"')
						ft_memcpy(arg[1], arg[1] + 1, ft_strlen(arg[1]));
					if (arg[1][ft_strlen(arg[1]) - 1] == '\''
						|| arg[1][ft_strlen(arg[1]) - 1] == '"')
						arg[1][ft_strlen(arg[1]) - 1] = '\0';
				}
				ft_env_set_value(env, arg[0], arg[1]);
			}
			free_malloc(arg);
		}
		return (0);
	}
	return (0);
}