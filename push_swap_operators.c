/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:50:22 by lguiet            #+#    #+#             */
/*   Updated: 2024/12/04 12:52:46 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_top(t_list **stack)
{
	t_list	*tmp;

	if (*stack && (*stack)->next)
	{
		tmp = (*stack)->next; // save pointeur du 2e noeud
		(*stack)->next = tmp->next;
		// 1er noeud saute 2e noeud pour pointer directmnt vers 3e
		tmp->next = *stack; // fait pointer 2e noeud vers 1er
		*stack = tmp;       // met la tete de liste sur l'ex 2e noeud
	}
	printf("sa\n");
}

void	ss(t_list **a, t_list **b)
{
	swap_top(a);
	swap_top(b);
}

void	pa(t_list **a, t_list **b)
{
	t_list	*tmp;

	tmp = NULL;
	if (*b)
	{
		tmp = (*b)->next; // save future nouvelle tete
		(*b)->next = *a;  // fait pointer next de b vers l'ancienne tete de a
		*a = *b;          // new tete de a
		*b = tmp;         // new tete de b
	}
	printf("pa\n");
}
void	pb(t_list **a, t_list **b)
{
	t_list	*tmp;

	tmp = NULL;
	if (*a)
	{
		tmp = (*a)->next;
		(*a)->next = *b;
		*b = *a;
		*a = tmp;
	}
	printf("pb\n");
}
void	ra(t_list **a)
{
	t_list	*tmp;
	t_list	*new_head;

	if (*a && (*a)->next)
	{
		new_head = (*a)->next;
		tmp = (*a);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *a;    // attache l'ancienne tete à la fin
		(*a)->next = NULL; // coupe le lien
		*a = new_head;
	}
	write(1, "ra\n", 3);
}
void	rb(t_list **b)
{
	t_list	*tmp;
	t_list	*new_head;

	if (*b && (*b)->next)
	{
		new_head = (*b)->next;
		tmp = (*b);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *b;    // attache l'ancienne tete à la fin
		(*b)->next = NULL; // coupe le lien
		*b = new_head;
	}
	write(1, "rb\n", 3);
}

void	rr(t_list **a, t_list **b)
{
	ra(a);
	rb(b);
}

void	rra(t_list **a)
{
	t_list	*tmp;
	t_list	*prev;

	if (!(*a) || !(*a)->next)
		return ;
	tmp = *a;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	tmp->next = *a;
	prev->next = NULL;
	*a = tmp;
	write(1, "rra\n", 4);
}
void	rrb(t_list **b)
{
	t_list	*tmp;
	t_list	*prev;

	if (*b || !(*b) || !(*b)->next)
		return ;
	tmp = *b;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	tmp->next = *b;
	prev->next = NULL;
	*b = tmp;
	write(1, "rrb\n", 4);
}
void	rrr(t_list **a, t_list **b)
{
	rra(a);
	rrb(b);
}