#include "microshell.h"

static char	*get_type(int type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == SEMI)
		return ("SEMI");
	return ("NONE");
}

static void	print_word_list(t_list *list)
{
	t_word_list	*word_list;

	printf("[%s]: ", get_type(list->type));
	word_list = list->word_list;
	while (word_list)
	{
		printf("%s -> ", word_list->word);
		word_list = word_list->next;
	}
	printf("NULL\n");
}

void	print_list(t_list *list)
{
	while (list)
	{
		print_word_list(list);
		list = list->next;
	}
	printf("END\n");
}
