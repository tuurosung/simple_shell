#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_node_list(list_t *head);


alias_t *add_alias_end(alias_t **head, char *name, char *value)
{      
        alias_t *new_node = malloc(sizeof(alias_t));
        alias_t *end;

        if (!new_node)
                return (NULL);
        
        new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
        if (!new_node->name)
        {
                free(new_node);
                return (NULL);
        }

        new_node->value = value;
        _strcpy(new_node->name, name);

        if (*head)
        {
                end = *head;
                while (end->next != NULL)
                        end = end->next;
                end->next = new_node;
        }
        else 
                *head = new_node;
        
        return (new_node);

}


void free_alias_list(alias_t *head)
{
        alias_t *next;

        while (head)
        {
                next = head->next;
                free(head->value);
                free(head->name);
                free(head);
                head = next;
        }
}


list_t *add_node_end(list_t **head, char *dir)
{
        list_t *new_node = malloc(sizeof(list_t));
        list_t *end;

        if (!new_node)
                return (NULL);
        
        new_node->dir = dir;
        new_node->next = NULL;

        if (*head)
        {
                end = *head;
                while (end->next != NULL)
                        end = end->next;
                end->next = new_node;
        }
        else
                *head = new_node;
        
        return (new_node);
}

void free_node_list(list_t *head)
{
        list_t *next;

        while (head)
        {
                next = head->next;
                free(head->dir);
                free(head);
                head = next;
        }
}