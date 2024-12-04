/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:52 by lguiet            #+#    #+#             */
/*   Updated: 2024/12/04 12:29:10 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
long	ft_atoi(const char *str)
{
	int			sign;
	long int	i;
	long int	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

t_list	*create_node(int value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	return (node);
}
void	add_node(t_list **stack, int value)
{
	t_list	*new_node;
	t_list	*last;

	last = NULL;
	new_node = create_node(value);
	if (!*stack)
		*stack = new_node;
	else
	{
		last = *stack;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}
void	print_stack(t_list *stack)
{
	while (stack)
	{
		printf("%ld -> ", stack->content);
		stack = stack->next;
	}
	printf("NULL\n");
}
void	ft_lstclear(t_list **lst)
{
	t_list *temp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst));
		*lst = temp;
	}
}