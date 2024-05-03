/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:32:21 by moichou           #+#    #+#             */
/*   Updated: 2024/05/03 16:44:16 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
}

void ft_free_toexec(t_toexec *head)
{
	t_toexec	*tmp;

	tmp = head;
	while (tmp)
	{
		ft_free_args(tmp->args);
		free(tmp);
		tmp = tmp->next;
	}
	head = NULL;
}

void	ft_free_token(t_token *head)
{
	t_token	*tmp;

	if (head == NULL)
		return ;
	tmp = head;
	while (tmp)
	{
		free(tmp->value);
		free(tmp);
		tmp = tmp->next;
	}
	head = NULL;
}

void	ft_free_herdoc_lst(t_herdoc *head)
{
	t_herdoc	*tmp;

	if (head == NULL)
		return ;
	tmp = head;
	while (tmp)
	{
		free(tmp->del);
		free(tmp);
	}
	head = NULL;
}