#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <ctype.h>

#define BOARD_SIZE 9
#define SHM_KEY 0x1234

typedef struct {
    char board[BOARD_SIZE];
    int turn;
    int game_over;
    int winner;
} game_state_t;

void print_board(char board[BOARD_SIZE]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        char c = board[i];
        if (c == ' ') c = '1' + i;
        printf(" %c ", c);
        if (i % 3 != 2) printf("|");
        else if (i != BOARD_SIZE - 1) printf("\n---+---+---\n");
    }
    printf("\n\n");
}

int check_winner(char board[BOARD_SIZE]) {
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; i++) {
        int a = wins[i][0], b = wins[i][1], c = wins[i][2];
        if (board[a] != ' ' && board[a] == board[b] && board[b] == board[c])
            return (board[a] == 'X') ? 0 : 1;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') return -1;
    }
    return 2;
}

int main(int argc, char *argv[]) {
    char player = toupper(argv[1][0]);
    int shmid = shmget(SHM_KEY, sizeof(game_state_t), IPC_CREAT | 0666);
    game_state_t *state = (game_state_t *)shmat(shmid, NULL, 0);

    if (state->board[0] == '\0') {
        for (int i = 0; i < BOARD_SIZE; i++) state->board[i] = ' ';
        state->turn = 0;
        state->game_over = 0;
        state->winner = -1;
    }

    while (!state->game_over) {
        if ((state->turn == 0 && player == 'X') || (state->turn == 1 && player == 'O')) {
            print_board(state->board);
            printf("Your turn (%c). Enter cell number (1-9): ", player);

            int move = 0;
            while (1) {
                char buf[10];
                fgets(buf, sizeof(buf), stdin);
                sscanf(buf, "%d", &move);
                move--;
                if (move >= 0 && move < BOARD_SIZE && state->board[move] == ' ') break;
                printf("Invalid or taken. Try again: ");
            }

            state->board[move] = player;
            int w = check_winner(state->board);
            if (w != -1) {
                state->game_over = 1;
                state->winner = w;
            } else {
                state->turn = 1 - state->turn;
            }
        } else {
            printf("Waiting for opponent (%c) to move...\n", (state->turn == 0) ? 'X' : 'O');
            sleep(1);
        }
    }

    print_board(state->board);
    if (state->winner == 2) printf("Game over: Draw!\n");
    else if (state->winner == (player == 'X' ? 0 : 1)) printf("Game over: You win!\n");
    else printf("Game over: You lose!\n");

    shmdt(state);
    return 0;
}
