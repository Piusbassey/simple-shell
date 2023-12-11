#include "cat.h"

/**
 * add_sep_node_end_p - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_listp *add_sep_node_end_p(sep_listp **head, char sep)
{
	sep_listp *new, *temp;

	new = malloc(sizeof(sep_listp));
	if (new == NULL)
		return (NULL);

	new->separator_p = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sep_list_p - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sep_list_p(sep_listp **head)
{
	sep_listp *temp;
	sep_listp *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end_p - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line_p: command line.
 * Return: address of the head.
 */
line_list_p *add_line_node_end_p(line_list_p **head, char *line_p)
{
	line_list_p *new, *temp;

	new = malloc(sizeof(line_list_p));
	if (new == NULL)
		return (NULL);

	new->line_p = line_p;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_line_list_p - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list_p(line_list_p **head)
{
	line_list_p *temp;
	line_list_p *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
