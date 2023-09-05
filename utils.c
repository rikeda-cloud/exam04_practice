#include "microshell.h"

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (*str++)
		size++;
	return (size);
}

void	ft_putstr(const char *str)
{
	if (write(STDERR_FILENO, str, ft_strlen(str)) == -1)
		write(STDERR_FILENO, ERR_FATAL, ft_strlen(ERR_FATAL));
}

void	ft_putendl(const char *str)
{
	ft_putstr(str);
	if (write(STDERR_FILENO, "\n", 1) == -1)
		write(STDERR_FILENO, ERR_FATAL, ft_strlen(ERR_FATAL));
}

void	err_print(const char *str1, const char *str2)
{
	ft_putstr(str1);
	ft_putendl(str2);
}

void	err_fatal()
{
	ft_putendl(ERR_FATAL);
	exit(1);
}
