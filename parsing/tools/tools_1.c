/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:54:19 by moichou           #+#    #+#             */
/*   Updated: 2024/04/22 16:17:59 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_legal_char(char *line, char c)
{
    int count = 0;
    int in_quotes = 0;
    char current_quote = '\0';

    for (int i = 0; line[i] != '\0'; i++) {
        if (ft_isquote(line[i])) {
            if (!in_quotes) {
                in_quotes = 1;
                current_quote = line[i];
            } else if (line[i] == current_quote) {
                in_quotes = 0;
                current_quote = '\0';
            }
        } else if (!in_quotes && line[i] == c) {
            count++;
        }
    }
    return count;
}

void	ft_printerror(char *msg)
{
	int	i;

	i = 0;
	write(2, "minishell: ", 12);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

// returns 1 if it is > < |
int	ft_isspecialchars(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

// returns 1 if it is single and 2 if double 0 if not quote
int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

// > == 1 | < == -1
int	ft_isredirection(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (-1);
	return (0);
}

char	*ft_strldup(char *s1, int lenght)
{
	int		i;
	char	*s2;

	i = 0;
	if (ft_strlen(s1) < lenght)
		return (NULL);
	s2 = malloc(sizeof(char) * (lenght + 1));
	if (!s2)
		return (NULL);
	while (i < lenght)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[lenght] = '\0';
	return (s2);
}

// remove the spaces/tabs form the bigg-end if str 
char	*ft_trim_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	j = ft_strlen(str) - 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (ft_isspace(str[j]))
		j--;
	j = ft_strlen(str) - j - 1;
	res = ft_strldup(str + i, (ft_strlen(str) - i - j));
	if (!res)
		ft_printerror(MALLOC_ERORR);
	return (res);
}

void	ft_skip_quotes(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] && ft_isquote(str[*i]) == 1)
		{
			(*i)++;
			while (str[*i] && ft_isquote(str[*i]) != 1)
				(*i)++;
		}
		else if (str[*i] && ft_isquote(str[*i]) == 2)
		{
			(*i)++;
			while (str[*i] && ft_isquote(str[*i]) != 2)
				(*i)++;
			
		}
		if (str[*i] == '\0')
			break ;
		// (*i)++;
		break ;
	}
}
