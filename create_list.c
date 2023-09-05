#include "microshell.h"

static t_list	*append_word_list(t_list *list, char *str)
{
	t_list		*head = list;
	t_word_list	*word_list;

	if (!list)
		return (new_list(str, WORD));
	while (list->next)
		list = list->next;
	if (list->type != WORD)
	{
		list->next = new_list(str, WORD);
		return (head);
	}
	word_list = list->word_list;
	while (word_list->next)
		word_list = word_list->next;
	word_list->next = new_word_list(str);
	return (head);
}

static t_list	*append_list(t_list *list, t_list *new_list)
{
	t_list	*head = list;

	if (!list)
		return (new_list);
	while (list->next)
		list = list->next;
	list->next = new_list;
	return (head);
}

t_list	*create_list(int argc, char **argv)
{
	size_t	i = 1;
	t_list	*list = NULL;

	while (i < argc)
	{
		if (strcmp(argv[i], "|") == 0)
			list = append_list(list, new_list(argv[i], PIPE));
		else if (strcmp(argv[i], ";") == 0)
			list = append_list(list, new_list(argv[i], SEMI));
		else
			list = append_word_list(list, argv[i]);
		i++;
	}
	return (list);
}
