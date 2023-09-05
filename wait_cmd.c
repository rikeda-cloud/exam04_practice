#include "microshell.h"

void	wait_cmd(t_list *cmd_line)
{
	if (!cmd_line->next && strcmp(cmd_line->word_list->word, "cd") == 0)
		return ;
	while (cmd_line)
	{
		waitpid(cmd_line->pid, NULL, 0);
		if (cmd_line->next)
			cmd_line = cmd_line->next->next;
		else
			cmd_line = NULL;
	}
}

