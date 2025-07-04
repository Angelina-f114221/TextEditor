#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

struct termios original;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &original);
    atexit(disableRawMode);

    struct termios raw = original;

    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d (%c)\n", c, c);
        }
    }
    return 1;
}

