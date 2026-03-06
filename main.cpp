#include <windows.h>
#include "app_trening.h"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR, int show_command)
{
	app_trening app{ instance };
	return app.run(show_command);
}