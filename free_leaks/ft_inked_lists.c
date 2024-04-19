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
		tmp = tmp->next;
		ft_free_args(tmp->args);
		free(tmp);
	}
	ft_free_args(head->args);
	free(head);
	head = NULL;
}

void	ft_free_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		free(tmp->value);
		free(tmp);
	}
	free(head->value);
	free(head);
}
