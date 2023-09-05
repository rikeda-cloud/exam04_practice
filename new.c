#include "microshell.h"

t_word_list	*new_word_list(char *str)
{
	t_word_list	*word_list = malloc(sizeof(t_word_list));

	word_list->word = str;
	word_list->next = NULL;
	return (word_list);
}

t_list	*new_list(char *str, t_type type)
{
	t_list	*new_list = malloc(sizeof(t_list));

	new_list->word_list = new_word_list(str);
	new_list->next = NULL;
	new_list->type = type;
	return (new_list);
}

