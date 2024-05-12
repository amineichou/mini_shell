/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:05:57 by moichou           #+#    #+#             */
/*   Updated: 2024/05/12 21:52:22 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_between_quotes(char *str, int *i, int type)
{
	char	*res;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && ft_isquote(str[*i]) != type)
		(*i)++;
	if (str[*i])
		(*i)++;
	res = ft_strldup(&str[start], (*i) - start);
	return (res);
}

static t_expand	*ft_create_expand_list(char *str)
{
	t_expand	*lst_expand;
	t_expand	*node;
	char		*res;
	int			i;
	int			start;
	bool		is_expand;

	i = 0;
	lst_expand = NULL;
	while (str[i])
	{
		is_expand = true;
		res = NULL;
		if (str[i] && ft_isquote(str[i]) == 1)
		{
			res = ft_get_between_quotes(str, &i, 1);
			is_expand = false;
		}
		else if (str[i] && ft_isquote(str[i]) == 2)
			res = ft_get_between_quotes(str, &i, 2);
		else
		{
			start = i;
			while (str[i] && !ft_isquote(str[i]))
				i++;
			if (start != i)
				res = ft_strldup(&str[start], i - start);
		}
		node = ft_create_expand_node(res);
		node->is_expand = is_expand;
		ft_append_node_expand(&lst_expand, node);
	}
	return (lst_expand);
}

char	*ft_expand_dollar(char *str, t_env *env)
{
	t_expand	*lst_expand;
	t_expand	*tmp;
	char		*res;

	lst_expand = ft_create_expand_list(str);
	tmp = lst_expand;
	res = NULL;
	while (tmp)
	{
		if (tmp->is_expand)
			tmp->value = ft_replace_dollar(tmp->value, env);
		tmp = tmp->next;
	}
	tmp = lst_expand;
	while (tmp)
	{
		res = ft_strjoin(res, tmp->value, true);
		tmp = tmp->next;
	}
	return (res);
}

char	*ft_expand(t_token *lst_token, t_env *envl)
{
	t_token	*tmp;
	char	*res;

	tmp = lst_token;
	res = NULL;
	while (tmp)
	{
		if (tmp && tmp->token == HEREDOC)
		{
			res = ft_strjoin_addspace(res, tmp->value, true);
			tmp = tmp->next;
		}
		else if (tmp && tmp->token == WORD)
			tmp->value = ft_expand_dollar(tmp->value, envl);
		res = ft_strjoin_addspace(res, tmp->value, true);
		tmp = tmp->next;
	}
	return (res);
}
