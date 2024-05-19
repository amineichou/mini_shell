/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:52:13 by moichou           #+#    #+#             */
/*   Updated: 2024/05/17 18:25:45 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// this func will set t_toexec node to it's default values
void	ft_set_default_vals(t_toexec *node, t_env *envl)
{
	node->input = 0;
	node->output = 1;
	node->args = NULL;
	node->env = envl;
}

static void	ft_hanlde_red_ap(t_token **lst_token, t_toexec *node)
{
	node->output = open((*lst_token)->next->value,
			O_RDWR | O_APPEND | O_CREAT, 0777);
	if (node->output == -1)
	{
		ft_printerror("");
		perror((*lst_token)->next->value);
		ft_set_status(1, 1);
		close_all();
		(*lst_token) = NULL;
		return ;
	}
	(*lst_token) = (*lst_token)->next;
}

static void	ft_hanlde_red_rp(t_token **lst_token, t_toexec *node)
{
	node->output = open((*lst_token)->next->value,
			O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (node->output == -1)
	{
		ft_printerror("");
		perror((*lst_token)->next->value);
		ft_set_status(1, 1);
		close_all();
		(*lst_token) = NULL;
		return ;
	}
	(*lst_token) = (*lst_token)->next;
}

static void	ft_hanlde_red_in(t_token **lst_token, t_toexec *node)
{
	node->input = open((*lst_token)->next->value, O_RDWR, 0777);
	if (node->input == -1)
	{
		ft_printerror("");
		perror((*lst_token)->next->value);
		ft_set_status(1, 1);
		close_all();
		(*lst_token) = NULL;
		return ;
	}
	(*lst_token) = (*lst_token)->next;
}

void	ft_handle_redirections(t_token **lst_token, t_toexec *node)
{
	while ((*lst_token) && ((*lst_token)->token == RD_AP
			|| (*lst_token)->token == RD_RP
			|| (*lst_token)->token == RD_IN))
	{
		if ((*lst_token)->next == NULL || (*lst_token)->next->token != WORD)
		{
			ft_printerror("ambiguous redirect\n");
			node->args = NULL;
			(*lst_token) = (*lst_token)->next;
			ft_set_status(1, 1);
			return ;
		}
		if ((*lst_token)->token == RD_AP)
			ft_hanlde_red_ap(lst_token, node);
		else if ((*lst_token)->token == RD_RP)
			ft_hanlde_red_rp(lst_token, node);
		else if ((*lst_token)->token == RD_IN)
			ft_hanlde_red_in(lst_token, node);
		if ((*lst_token))
			(*lst_token) = (*lst_token)->next;
	}
}
