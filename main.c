#include "microshell.h"

int	main(int argc, char **argv)
{
	t_list	*list;

	list = create_list(argc, argv);
	exec_cmd_line(list);
	/* print_list(list); */
	return (0);
}
