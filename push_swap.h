/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:53:03 by lguiet            #+#    #+#             */
/*   Updated: 2024/12/04 12:16:30 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	long int		content;
	struct s_list	*next;
}					t_list;
//-----------------------------------------OPERATORS
void				swap_top(t_list **stack);
void				ss(t_list **a, t_list **b);
void				pa(t_list **a, t_list **b);
void				pb(t_list **a, t_list **b);
void				ra(t_list **a);
void				rb(t_list **b);
void				rr(t_list **a, t_list **b);
void				rra(t_list **a);
void				rrb(t_list **b);
void				rrr(t_list **a, t_list **b);

//-----------------------------------------UTILS
int					ft_isdigit(int c);
long				ft_atoi(const char *str);
t_list				*create_node(int value);
void				add_node(t_list **stack, int value);
void				print_stack(t_list *stack);
void				ft_lstclear(t_list **lst);
//--------------------------------------------------PARSING
int					valid_param(char **argv);
int					duplicated_nb(t_list *a);
// int					not_overflow(t_list *a);
int					is_sorted(t_list *a);

#endif