#define WINVER 0x501
#define _WIN32_WINNT 0x501

#include <windows.h>
#include <stdio.h>
#include "Win7TaskbarProgress.h"

// Source: http://stackoverflow.com/questions/3560018/triggering-taskbar-button-flash-from-batch-file

void main(int argc, char **argv)
{
	HWND hWnd = GetConsoleWindow();
	Win7TaskbarProgress tb;

	if (argc > 1)
	{
		if (!strcmp(argv[1], "-progress"))
		{
			if (argc > 2)
			{
				int i = atoi(argv[2]);
				tb.SetProgressValue(hWnd, i, 100);
			}
			else
			{
				fprintf(stderr, "Progress requested but no value specified.\n");
			}
		}
		else if (!strcmp(argv[1], "-error"))
		{
			tb.SetProgressState(hWnd, TBPF_ERROR);
		}
		else if (!strcmp(argv[1], "-indeterminate"))
		{
			tb.SetProgressState(hWnd, TBPF_INDETERMINATE);
		}
		else if (!strcmp(argv[1], "-normal"))
		{
			tb.SetProgressState(hWnd, TBPF_NORMAL);
		}
		else if (!strcmp(argv[1], "-noprogress"))
		{
			tb.SetProgressState(hWnd, TBPF_NOPROGRESS);
		}
		else if (!strcmp(argv[1], "-paused"))
		{
			tb.SetProgressState(hWnd, TBPF_PAUSED);
		}
		else if (!strcmp(argv[1], "-flash"))
		{
			int cnt = 3;
			if (argc > 2)
			{
				cnt = atoi(argv[2]);
			}
			FLASHWINFO info = { sizeof(info), hWnd, FLASHW_TIMER | FLASHW_TRAY, cnt, 0 };
			FlashWindowEx(&info);
		}
		else if (!strcmp(argv[1], "-noflash"))
		{
			FLASHWINFO info = { sizeof(info), hWnd, FLASHW_STOP, 0, 0 };
			FlashWindowEx(&info);
		}
		else if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "/help") || !strcmp(argv[1], "-h") || !strcmp(argv[1], "/?"))
		{
			printf("FlashConsoleWindow tool\n");
			printf("(c) 2013 Yves Goergen, last update 2013-02-24\n");
			printf("http://dev.unclassified.de/apps/flashconsolewindow\n");
			printf("\n");
			printf("Supported options:\n");
			printf("  (default)       Flashes the taskbar item until it is activated.\n");
			printf("  -flash          Flashes the taskbar item until -noflash is set.\n");
			printf("  -flash n        Flashes the taskbar item n times until -noflash is set.\n");
			printf("  -noflash        Stops flashing the taskbar item.\n");
			printf("  -help           Shows this information.\n");
			printf("Only on Windows Vista and later:\n");
			printf("  -progress n     Sets the progress to n percent (0...100).\n");
			printf("  -indeterminate  Changes state to Indeterminate (no progress value).\n");
			printf("  -normal         Changes state to Normal (progress value used).\n");
			printf("  -paused         Changes state to Paused (yellow colour).\n");
			printf("  -error          Changes state to Error (red colour).\n");
			printf("  -noprogress     Clears all progress or state from the taskbar item.\n");
		}
		else
		{
			fprintf(stderr, "Option not recognised.\n");
		}
	}
	else
	{
		FLASHWINFO info = { sizeof(info), hWnd, FLASHW_TIMERNOFG | FLASHW_TRAY, 3, 0 };
		FlashWindowEx(&info);
	}
}
