/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:28:04 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/29 03:31:20 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void
	ft_skip_spaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && **str == ' ')
		++*str;
}