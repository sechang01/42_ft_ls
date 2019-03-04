/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:28:32 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 19:36:10 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/libft.h"
#include "ft_linkedlist.h"

// FIFO

t_queue		*queue_init_lst(void)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->size = 0;
	new->front = NULL;
	new->rear = NULL;
	return (new);
}

int			queue_in(t_queue *lst, void *data)
{
	t_sqnode	*tmp;

	if (!lst)
		return (-1);
	if (!lst->front)
	{
		if (!(lst->front = (t_sqnode *)malloc(sizeof(t_sqnode))))
			return (-1);
		lst->front->data = data;
		lst->front->next = 0;
		lst->rear = lst->front;
		lst->size++;
	}
	else
	{
		if (!(tmp = (t_sqnode *)malloc(sizeof(t_sqnode))))
			return (-1);
		tmp->data = data;
		tmp->next = 0;
		lst->rear->next = tmp;
		lst->rear = tmp;
		lst->size++;
	}
	return (1);
}

void		*queue_out(t_queue *lst)
{
	t_sqnode	*tmp;
	void		*tmp2;

	if (!lst || !lst->front)
		return (0);
	tmp = lst->front;
	tmp2 = lst->front->data;
	lst->front = lst->front->next;
	free(tmp);
	lst->size--;
	return (tmp2);
}

void		*queue_out_rear(t_queue *lst)
{
	t_sqnode	*tmp;
	void		*tmp3;
	int			i;

	i = 1;
	if (!lst || !lst->front)
		return (0);
	tmp = lst->front;
	if (lst->size == 1)
	{
//		printf("List size is one.\n");
		tmp3 = lst->front->data;
		lst->front = lst->front->next;
		free(tmp);
	}
	else
	{
		while (i < lst->size - 1)
		{
			tmp = tmp->next;
			i++;
		}
		lst->rear = tmp;
		tmp3 = tmp->next->data;
		tmp = tmp->next;
		free(tmp);
		lst->rear->next = 0;
	}
	lst->size--;
	return (tmp3);
}


void		queue_print(t_queue *lst)
{
	t_sqnode *tmp;

	if (!lst || !lst->front)
	{
		printf("List empty");
		return ;
	}
	tmp = lst->front;
	while (tmp)
	{
		printf("Print Out: %s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf(" ----- \n");	
}

/*
   int		main()
   {
   t_queue	*test;

   test = queue_init_lst();
   printf("Success: %d \n", queue_in(test, "123"));
   printf("Success: %d \n", queue_in(test, "456"));
   printf("Success: %d \n", queue_in(test, "789"));
   printf("Success: %d \n", queue_in(test, "000"));
   printf("Success: %d \n", queue_in(test, "ABX"));

   printf("Success: %s \n", (char *)queue_out(test));
   printf("Success: %s \n", (char *)queue_out(test));
   printf("Success: %s \n", (char *)queue_out(test));
   printf("Success: %s \n", (char *)queue_out(test));
//	printf("Success: %s \n", (char *)queue_out(test));

queue_print(test);
printf("Success: %s \n", (char *)queue_out(test));

queue_print(test);
return(0);
}
*/