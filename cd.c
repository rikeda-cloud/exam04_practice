#include "microshell.h"

void	cd(t_word_list *word_list)
{
	word_list = word_list->next;
	if (!word_list->word || word_list->next)
		ft_putendl(ERR_CD_BAD);
	else
	{
		if (chdir(word_list->word))
			err_print(ERR_CD, word_list->word);
	}
}
