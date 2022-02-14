/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 06:17:31 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/14 01:06:54 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: export
** export -> prints "declare -x" and then, env variable. Env variables are
** 	sorted using their name using ascii.
** export (name) -> prints '\n' and then, adds (name) to env vars.
** More than the first parametter has to be handled
** ! Although env prints just env variables with value, export prints everything
** 	even if there is no value set for that env variable.
*/

static inline void
	print_env_list(t_list *l_env)
{
	t_list	*env_node;

	env_node = l_env;
	while (env_node)
	{
		if (((t_env *)(env_node->content))->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)(env_node->content))->key,
				((t_env *)(env_node->content))->value);
		else
			printf("declare -x %s\n", ((t_env *)(env_node->content))->key);
		env_node = env_node->next;
	}
}

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

int
	ft_is_valid_identifier(char *str)
{
	return (!ft_isalpha(*str));
}

int
	ft_export(int argc, char **argv, t_list *env)
{
	char	**arg;
	t_list	*cpy;
	int		i;

	if (argc >= 2)
	{
		i = 0;
		while (argv[i++])
		{
			arg = ft_split(argv[i], '=');
			if (arg && arg[0])
			{
				if (ft_is_valid_identifier(arg[0]))
					dprintf(2, "%s: export: `%s': not a valid identifier\n",
						SHELL_NAME, arg[0]);
			}
			arg = ft_free_tab(arg);
		}
		return (0);
	}
	cpy = lst_cpy(env);
	ft_lstsort(cpy);
	print_env_list(cpy);
	ft_lstclear(&cpy, NULL);
	return (0);
}
