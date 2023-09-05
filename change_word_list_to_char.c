#include "microshell.h"

static size_t	get_list_size(t_word_list *word_list)
{
	size_t	size = 0;

	while (word_list)
	{
		size++;
		word_list = word_list->next;
	}
	return (size);
}

char	**change_word_list_to_char(t_word_list *word_list)
{
	size_t	idx = 0;
	size_t	size = get_list_size(word_list);
	char	**char_list = malloc(sizeof(char *) * (size + 1));

	while (idx < size)
	{
		char_list[idx++] = word_list->word;
		word_list = word_list->next;
	}
	char_list[idx] = NULL;
	return (char_list);
}
