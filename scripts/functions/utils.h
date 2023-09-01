#include <string.h>

char* stristr(const char* haystack, const char* needle)
{
    const char* pHaystack = haystack;
    const char* pNeedle = needle;
    const char* result = (*pNeedle == '\0') ? haystack : nullptr;

    while (*pHaystack != '\0' && *pNeedle != '\0')
    {
        if (tolower(static_cast<unsigned char>(*pHaystack)) == tolower(static_cast<unsigned char>(*pNeedle)))
        {
            if (result == nullptr)
            {
                result = pHaystack;
            }

            pNeedle++;
        }
        else
        {
            pNeedle = needle;
            if (result != nullptr)
            {
                pHaystack = result + 1;
            }

            if (tolower(static_cast<unsigned char>(*pHaystack)) == tolower(static_cast<unsigned char>(*pNeedle)))
            {
                result = pHaystack;
                pNeedle++;
            }
            else
            {
                result = nullptr;
            }
        }

        pHaystack++;
    }

    return (*pNeedle == '\0') ? const_cast<char*>(result) : nullptr;
}

void cursor (int x)
{
	switch (x) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

// Clear the line
void clreol(int x)
{
	for(int i=0; i < x; i++)
        printf(" ");
	for(int i=0; i < x; i++)
        printf("\b");
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x - 1;
	coord.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}