/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 03:41:06 by moichou           #+#    #+#             */
/*   Updated: 2024/04/23 12:31:38 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_valid_fd(t_toexec *head)
{
	t_toexec	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->output == -1)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_toexec	*ft_parser(char *line, t_env *envl)
{
	char		*sanitize_result;
	t_toexec	*lst_toexec;

	sanitize_result = ft_sanitizer(line);
	if (!sanitize_result)
		return (NULL); // TODO : free
	lst_toexec = ft_analyser(sanitize_result, envl);
	if (!lst_toexec)
		return (NULL);
	if (ft_check_valid_fd(lst_toexec) == 0)
		return (ft_free_toexec(lst_toexec), NULL);
	// test_lst(lst_toexec);
	return (lst_toexec);
}
