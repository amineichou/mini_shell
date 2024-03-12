/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:32 by moichou           #+#    #+#             */
/*   Updated: 2024/03/12 15:03:04 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_sanitizer(char *line)
{
	char **sanitize_result;

	if (ft_sanitize_pipes(line) == -1 
		|| ft_sanitize_quotes(line) == -1
		|| ft_sanitize_redirections(line) == -1)
		return (-1);
	sanitize_result = ft_remove_split_spaces(line);
	return (0);
}
