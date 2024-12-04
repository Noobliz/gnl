/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:36:38 by lguiet            #+#    #+#             */
/*   Updated: 2024/12/04 12:20:30 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	valid_param(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			while (argv[i][j] == '-' || argv[i][j] == '+')
			{
				if (j > 0 && argv[i][j - 1] != ' ')
				{
					write(1, "Error\n", 6);
					return (0);
				}
				j++;
			}
			if (argv[i][j] != ' ' && !(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				write(1, "Error\n", 6);
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}
int	duplicated_nb(t_list *a)
{
	t_list	*tmp;
	t_list	*current;

	current = a;
	tmp = current->next;
	while (current)
	{
		while (tmp)
		{
			if (current->content == tmp->content)
			{
				write(1, "Error\n", 6);
				return (0);
			}
			tmp = tmp->next;
		}
		current = current->next;
		if (current->next == NULL)
			break ;
		tmp = current->next;
	}
	return (1);
}
// int	not_overflow(t_list *a)
// {
// 	long int i;
// 	long int j;
// 	t_list *tmp;

// 	i = 2147483647;
// 	j = -2147483648;
// 	tmp = a;
// 	while (tmp)
// 	{
// 		printf("tmp->content = %ld\n", tmp->content);
// 		if (tmp->content > i || tmp->content < j)
// 		{
// 			write(1, "Error\n", 6);

// 			return (0);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }
int	is_sorted(t_list *a)
{
	t_list *tmp;

	tmp = a;
	if (!a)
		return (0);
	while (tmp->next)
	{
		if (tmp->content > tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}