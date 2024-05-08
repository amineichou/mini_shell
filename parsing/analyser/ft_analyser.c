/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:02:34 by moichou           #+#    #+#             */
/*   Updated: 2024/05/08 21:26:05 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char		**ft_reallocate_copy(char **old_res, char *new)
{
	char	**res;
	int		i;

	i = 0;
	if (!old_res)
	{
		res = zyalloc(sizeof(char *) * 2, 'a', true);
		res[0] = ft_strdup(new, true); // leaks if new is mallocated
		res[1] = NULL;
	}
	else
	{
		while (old_res[i])
			i++;
		res = zyalloc(sizeof(char *) * (i + 2), 'a', true);
		i = 0;
		while (old_res[i])
		{
			res[i] = ft_strdup(old_res[i], true);
			i++;
		}
		res[i] = ft_strdup(new, true);
		res[i + 1] = NULL;
	}
	return (res);
}

void	ft_handle_args(t_toexec **node, t_token **lst_token)
{
	char	**joined;

	joined = (*node)->args;
	if ((*lst_token) && (*lst_token)->value == NULL)
	{
		(*node)->args = NULL;
		(*lst_token) = (*lst_token)->next;
		return ;
	}
	while ((*lst_token) && (*lst_token)->token == WORD)
	{
		joined = ft_reallocate_copy(joined, (*lst_token)->value); // TODO : leaks
		(*lst_token) = (*lst_token)->next;
	}
	(*node)->args = joined;
}

char	*ft_get_herdoc_del(char *line, int *i)
{
	int	start;
	int	length;

	*i += 2;
	length = 0;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] && ft_isquote(line[*i]))
		return (ft_get_inside_quotes(line, i, line[*i]));
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_isspecialchars(line[*i]))
	{
		(*i)++;
		length++;
	}
	if (length)
		return (ft_strldup(&line[start], length));
	return (NULL);
}

static void	ft_set_default_vals(t_toexec *node, t_env *envl)
{
	node->input = 0;
	node->output = 1;
	node->args = NULL;
	node->env = envl;
}

static char *ft_ckeck_herdoc_del(char *del, t_herdoc *node)
{
	char	*res;

	if (ft_isquote(del[0]))
	{
		node->is_expand = false;
		return (ft_strldup(&del[1], ft_strlen(del) - 2));
	}
	node->is_expand = true;
	res = ft_strdup(del, true);
	return (res);
}

static t_herdoc	*ft_go_for_herdoc(t_token **head)
{
	t_token		*tmp;
	t_herdoc	*lst_herdoc;
	t_herdoc	*herdoc_node;
	t_token		*pop_it;

	tmp = *head;
	lst_herdoc = NULL;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp && tmp->token == HEREDOC)
		{
			pop_it = tmp;
			tmp = tmp->next;
			ft_pop_node_t_token(head, pop_it);
			herdoc_node = zyalloc(sizeof(t_herdoc), 'a', true);
			herdoc_node->del = ft_ckeck_herdoc_del(tmp->value, herdoc_node);
			herdoc_node->next = NULL;
			ft_append_node_herdoc(&lst_herdoc, herdoc_node);
			pop_it = tmp;
			tmp = tmp->next;
			ft_pop_node_t_token(head, pop_it);
		}
		else
			tmp = tmp->next;
	}
	return (lst_herdoc);
}

static void	ft_run_for_herdoc(t_herdoc *head, t_toexec *node, int ex_sta)
{
	t_herdoc	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_heredoc_handler_exec(node, tmp, ex_sta) == -1)
		{
			open(ttyname(0), O_RDWR);
			signal(SIGINT, ft_sigkill_handler);
			break;
		}
		tmp = tmp->next;
	}
}

// analyser will analyze tokens and create the t_toexec list
t_toexec	*ft_analyser(char *sanitize_result, t_env *envl, int ex_sta)
{
	t_token		*lst_token;
	t_toexec	*lst_toexec;
	t_toexec	*node;
	t_herdoc	*lst_herdoc;
	int			is_expand;

	lst_token = ft_make_tokens(sanitize_result);
	// test_tokens(lst_token);
	lst_toexec = NULL;
	lst_herdoc = NULL;
	is_expand = 1;
	while (lst_token)
	{
		node = zyalloc(sizeof(t_toexec), 'a', true);
		if (!node)
			return (ft_printerror(MALLOC_ERORR), NULL);
		ft_set_default_vals(node, envl);
		lst_herdoc = ft_go_for_herdoc(&lst_token);
		if (lst_herdoc)
			ft_run_for_herdoc(lst_herdoc, node, ex_sta);
		else if (!lst_herdoc && is_expand)
		{
			ft_expand(lst_token, envl, ex_sta);
			is_expand = 0;
		}
		if (lst_token && lst_token->token == WORD)
		{
			ft_handle_args(&node, &lst_token);
			if (lst_token == NULL)
			{
				ft_append_node_t_toexec(&lst_toexec, node);
				break;
			}
		}
		if (lst_token && (lst_token->token == RD_AP || lst_token->token == RD_RP || lst_token->token == RD_IN))
		{
			ft_handle_redirections(&lst_token, node);
				ft_append_node_t_toexec(&lst_toexec, node);
			if (lst_token == NULL)
			{
				break;
			}
			// else if (lst_token->token == WORD)
			// {
			// 	ft_handle_args(&node, &lst_token);
			// 	if (lst_token == NULL)
			// 	{
			// 		ft_append_node_t_toexec(&lst_toexec, node);
			// 		break;
			// 	}
			// }
		}
		if (lst_token && lst_token->token == PIPE)
		{
			lst_token = lst_token->next;
			ft_append_node_t_toexec(&lst_toexec, node);
			continue;
		}
	}
	// test_lst(lst_toexec); ft_free_token(lst_token), 
	return (lst_toexec);
}
