#include "cat.h"

/**
 * add_rvar_node_p - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val_p: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var_p *add_rvar_node_p(r_var_p **head, int lvar, char *val_p, int lval)
{
	r_var_p *new, *temp;

	new = malloc(sizeof(r_var_p));
	if (new == NULL)
		return (NULL);

	new->len_var_p = lvar;
	new->val_p = val_p;
	new->len_val_p = lval;

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
 * free_rvar_list_p - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_rvar_list_p(r_var_p **head)
{
	r_var_p *temp;
	r_var_p *curr;

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
