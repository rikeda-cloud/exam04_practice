#include "microshell.h"

static t_list	*append_list(t_list *list, t_list *new_list)
{
	t_list	*tmp;

	tmp = list;
	if (!list)
		return (new_list);
	while (list->next)
		list = list->next;
	list->next = new_list;
	return (tmp);
}

static t_word_list	*new_word_list(char *str)
{
	t_word_list	*word_list;

	word_list = malloc(sizeof(t_word_list));
	word_list->word = str;
	word_list->next = NULL;
	return (word_list);
}

static t_list	*new_list(char *str, t_type type)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	new_list->word_list = new_word_list(str);
	new_list->next = NULL;
	new_list->fd = 0;
	new_list->type = type;
	return (new_list);
}

static t_list	*append_word_list(t_list *list, char *str)
{
	t_list		*tmp;
	t_word_list	*word_list;

	tmp = list;
	if (!list)
		return (new_list(str, WORD));
	while (list->next)
		list = list->next;
	if (list->type != WORD)
	{
		list->next = new_list(str, WORD);
		return (tmp);
	}
	word_list = list->word_list;
	while (word_list->next)
		word_list = word_list->next;
	word_list->next = new_word_list(str);
	return (tmp);
}

t_list	*create_list(int argc, char **argv)
{
	t_list	*list;
	size_t	i;

	i = 1;
	list = NULL;
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
