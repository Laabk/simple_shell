#include "bshell.h"

/**
 * _visio - this func handle crtl + c call in prompt
 * @vis: handle signal
 */
void _visio(int vis)
{
	(void)vis;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
