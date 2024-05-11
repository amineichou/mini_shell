/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:39:33 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/11 15:29:38 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	free_env_list(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		current = next;
	}
}

void	ft_unset(t_env **env, char *to_del)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	if (tmp != NULL && ft_strcmp(tmp->name, to_del) == 0)
		*env = (*env)->next;
	else
	{
		while (tmp)
		{
			if (tmp->next && (ft_strcmp(tmp->next->name, to_del) == 0))
			{
				prev = tmp->next;
				if (tmp->next->next)
					tmp->next = tmp->next->next;
				else
					tmp->next = NULL;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	unseter(t_toexec *cmd, t_pipe *needs)
{
	int	i;

	(void)needs;
	i = 1;
	while (cmd->args[i])
	{
		ft_unset(&cmd->env, cmd->args[i]);
		i++;
	}
	*(needs->ex_stat) = 0;
	return (1);
}
