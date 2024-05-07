/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:59:34 by moichou           #+#    #+#             */
/*   Updated: 2024/05/07 15:51:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_is_alphanumeric(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(char *s1, bool to_free)
{
	int		str_length;
	int		i;
	char	*s2;

	i = 0;
	if(!s1)
		return (NULL);
	str_length = ft_strlen(s1) + 1;
	s2 = zyalloc(sizeof(char) * str_length, 'a', to_free);
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(char *s, int c)
{
	int				i;
	char			*searched;
	unsigned char	d;

	i = 0;
	searched = (char *)s;
	d = (unsigned char)c;
	while (searched[i])
	{
		if (searched[i] == d)
			return (&searched[i]);
		i++;
	}
	if (d == '\0')
		return (searched + ft_strlen(searched));
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_strcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

static int	ft_handler(const char *str, int sign)
{
	int			i;
	long long	handler;
	long long	tmp;

	i = 0;
	handler = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = handler * 10 + (str[i] - 48); 
		if (tmp < handler && sign == 1)
			return (-1);
		if (tmp < handler && sign == -1)
			return (0);
		handler = tmp;
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_handler(&str[i], sign) == -1)
		return (-1);
	if (ft_handler(&str[i], sign) == 0)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

char	*ft_strjoin(char *s1, char *s2, bool to_free)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2, to_free));
	else if (!s2)
		return (ft_strdup(s1, to_free));
	str = (char *)zyalloc(ft_strlen(s1) + ft_strlen(s2) + 1, 'a', to_free);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (str);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_lenth;
	size_t	src_lenth;

	src_lenth = ft_strlen(src);
	if (!dst && dstsize == 0 && src)
		return (src_lenth);
	dst_lenth = ft_strlen(dst);
	i = 0;
	if (dst_lenth >= dstsize)
		return (dstsize + src_lenth);
	while (src[i] && i + dst_lenth < dstsize - 1)
	{
		dst[dst_lenth + i] = src[i];
		i++;
	}
	dst[i + dst_lenth] = '\0';
	return (dst_lenth + src_lenth);
}

char	*ft_substr(char *s, int start, int len, bool to_free)
{
	char	*str;
	int		i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", to_free));
	i = 0;
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = (char *)zyalloc(sizeof(char) * len + 1, 'a', to_free);
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
// void	*talloc(size_t __size)
// {
// 	void	*__ptr;

// 	__ptr = malloc(__size);
// 	if (__ptr == NULL)
// 		return (NULL);
// 	printf("pointer \033[32m%p\033[0m was allocated, size : \033[32m%ld\033[0m\n", __ptr, __size);
// 	return (__ptr);
// }



// itoi

static int	ft_count_dig(long int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n, bool to_free)
{
	char		*converted_number;
	int			digit_count;
	long int	number;

	number = n;
	digit_count = ft_count_dig(number);
	if (number < 0)
	{
		number *= -1;
		digit_count++;
	}
	converted_number = zyalloc(sizeof(char) * (digit_count + 1), 'a', to_free);
	if (!converted_number)
		return (0);
	converted_number[digit_count] = '\0';
	while (digit_count--)
	{
		converted_number[digit_count] = (number % 10) + '0';
		number /= 10;
	}
	if (n < 0)
		converted_number[0] = '-';
	return (converted_number);
}

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

void garb_add(t_garbage **lst, t_garbage *new)
{
	t_garbage *lastone;

	if (!lst || !new)
		return;
	if (!(*lst))
	{
		*lst = new;
		return;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

t_garbage *garb_new(void *addrress, bool is_free)
{
    t_garbage *newnode = malloc(sizeof(t_garbage));
    if (newnode == NULL)
	{
        perror("malloc");
        return(NULL);
    }
    newnode->adr = addrress;
	newnode->is_free = is_free;
    newnode->next = NULL;
    return (newnode);
}

void free_garb_list(t_garbage **head)
{
	t_garbage *current;
	t_garbage *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->is_free)
		{
			// dprintf(2 ,"%s\n", current->adr);
			free(current->adr);
			current->adr = NULL;
			
		}
		current = next;
	}
}

void *zyalloc(size_t size, int flag, bool is_free)
{
	static t_garbage	*gooper;
	t_garbage			*node;
	void *address;
	
	address = NULL;
	if(flag == 'a')
	{
		address = malloc(size);
		if(!address)
			perror("malloc");
		if(gooper == NULL)
		{
			gooper = garb_new(address, is_free);
		}
		else
		{
			node = garb_new(address, is_free);
			garb_add(&gooper, node);
		}
	}
	else if(flag == 'f')
		free_garb_list(&gooper);
	return(address);
}

char* ft_strstr(const char* haystack, const char* needle)
{

    const char* p1;
    const char* p2;
    const char* p1_advance;

	if (*needle == '\0')
        return (char*)haystack;
	p1_advance = haystack;
    while (*p1_advance)
	{
        p1 = p1_advance;
        p2 = needle;
        
        while (*p1 && *p2 && *p1 == *p2)
		{
            p1++;
            p2++;
        }
        if (*p2 == '\0')
            return (char*)p1_advance;
        
        p1_advance++;
    }
    
    return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

