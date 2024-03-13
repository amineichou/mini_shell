/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/03/13 02:04:08 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_sanitizer(char *line)
{
	char **sanitize_result;

	if (ft_sanitize_pipes(line) == -1 
		|| ft_sanitize_quotes(line) == -1
		|| ft_sanitize_redirections(line) == -1)
		return (NULL);
	sanitize_result = ft_remove_split_spaces(line);
	return (sanitize_result);
}