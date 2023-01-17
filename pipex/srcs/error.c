#include "pipex.h"

void	error_message(void)
{
	perror("The program detected an error ");
	exit(1);
}