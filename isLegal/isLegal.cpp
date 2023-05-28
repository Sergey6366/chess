#include <iostream>
using namespace std;


int CheckPos(const char* w, const char* b) {  // is position from string legal? 0 - yes, 1 - no, 2 - bad syntax
	// format of w, b: "Kd2; Qa1; Nh7; Rg8; Pc3; Bf5; Bf4"

	int i1 = 0, i2 = 0, board[8][8] = { 0 }, kw = 0, kb = 0, kww, kwh, kbw, kbh;
	char w1, w2;
	while (w[i1] != '\0') {
		if (w[i1] == ';') i1 += 2;
		if (w[i1] == 'K') {
			if (kw != 0) return 1;  // two kings
			kw = 1;
			kww = w[i1 + 1] - 'a';
			kwh = w[i1 + 2] - '1';
		}
		else if (!(w[i1] == 'N' || w[i1] == 'B' || w[i1] == 'R' || w[i1] == 'Q' || w[i1] == 'P')) return 2;

		w1 = w[i1 + 1];  w2 = w[i1 + 2];
		if (w1 >= 'a' && w1 <= 'h' && w2 >= '1' && w2 <= '8') {
			if (board[w1 - 'a'][w2 - '1'] == 1) return 1;
			if (w[i2] == 'P' && w2 == '8') return 1;  // pawn is on a promotion square
			board[w1 - 'a'][w2 - '1'] = 1;
		}
		else return 1;  // out from the board
		i1 += 3;
	}
	while (b[i2] != '\0') {
		if (b[i2] == ';') i2 += 2;
		if (b[i2] == 'K') {
			if (kb != 0) return 1;  // two kings
			kb = 1;
			kbw = b[i2 + 1] - 'a';
			kbh = b[i2 + 2] - '1';
		}
		else if (!(b[i2] == 'N' || b[i2] == 'B' || b[i2] == 'R' || b[i2] == 'Q' || b[i2] == 'P')) return 2;

		w1 = b[i2 + 1];  w2 = b[i2 + 2];
		if (w1 >= 'a' && w1 <= 'h' && w2 >= '1' && w2 <= '8') {
			if (board[w1 - 'a'][w2 - '1'] == 1) return 1;
			if (b[i2] == 'P' && w2 == '1') return 1;  // pawn is on a promotion square
			board[w1 - 'a'][w2 - '1'] = 1;
		}
		else return 1;  // out from the board  
		i2 += 3;
	}
	if (kw != 1 || kb != 1 || (std::max(abs(kww - kbw), abs(kwh - kbh)) <= 1)) return 1;
	return 0;
}


/*
void cPawn(int board[8][8], int color, int i, int j) {  // color = 0 or 1 (white or black) - for pieces ranges
	int color1 = -2 * color + 1;  // for moving
	for (int k = -1; k <= 1; k += 2) {
		if ((0 <= i + k) && (i + k <= 7) && (0 <= j + color1) && (j + color1 <= 7)) {
			if (board[i + k][j + color1] == 0) board[i + k][j + color1] = 13 + color;  // 13 - white, 14 - black
			if ((color * 6 + 1 <= board[i + k][j + color1]) &&
				(board[i + k][j + color1] <= color * 6 + 5)) board[i + k][j + color1] = 15 + color;
		}
	}
}


void cKnight(int board[8][8], int color, int i, int j) {  // color = 0 or 1 (white or black) - for pieces ranges
	for (int k = 1; k <= 2; k++) {
		for (int l = -1; l <= 1; l += 2) {  // for multiplying with k
			for (int m = -1; m <= 1; m += 2) {  // for multiplying with (3-k)

				if ((0 <= i + l * k) && (i + l * k <= 7) &&
					(0 <= j + m * (3 - k)) && (j + m * (3 - k) <= 7)) {
					if ()
				}
			}
		}
	}
}

//..........................MAKE COLORING FOR OTHER PIECES......................................

void colorBoard(int board[8][8], int piece, int i, int j) { // piece = 1 ... 12; i, j = 0 ... 7


	switch (piece) {
	case 1:

	}
}


int CheckMate(int board[8][8], char move) {  // 0 - nothing, 1 - check, 2 - mate
	// assuming the position is LEGAL: only 2 kings (b and w), they aren't together,
	// pawns aren't on a promotion squares
	// ......................................
	// board[a-h][1-8]:
	// 0 - empty
	// white: 1 - pawn, 2 - knight, 3 - bishop, 4 - rook, 5 - queen, 6 - king
	// black: 7 - pawn, 8 - knight, 9 - bishop, 10 - rook, 11 - queen, 12 - king
	// 13 - attacked by white, 14 - attacked by black
	// 15 - defended piece by white, 16 - defended piece by black
	// ......................................
	// move - who moved: 'w' or 'b'

	int whoMoved = 1, whoTarget = 7, kingMovedx = 0, kingMovedy = 0, kingTargetx = 0, kingTargety = 0,
		counter = 0;

	// counter counts the number f checks (0, 1, 2), 0 means return 0, double check means king has to move

	if (move == 'b') {
		whoMoved = 7;
		whoTarget = 1;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == whoTarget + 5) {  // getting info about kings' positions
				kingTargetx = i;
				kingTargety = j;
			}
			if (board[i][j] == whoMoved + 5) {
				kingMovedx = i;
				kingMovedy = j;
			}
			// coloring the attacked squares and checking for a check:
			if (whoMoved <= board[i][j] && board[i][j] <= whoMoved + 5) {
				colorBoard(board, board[i][j], i, j);
			}
		}
	}
}
*/

int CheckMate(Board board, char move) {  // in this position it is: 0 - nothing, 1 - check, 2 - mate
	// assuming the position is LEGAL: only 2 kings (b and w), they aren't together,
	// pawns aren't on a promotion squares
	// ......................................
	// board[a-h][1-8]:
	// 0 - empty
	// white: 1 - pawn, 2 - knight, 3 - bishop, 4 - rook, 5 - queen, 6 - king
	// black: 7 - pawn, 8 - knight, 9 - bishop, 10 - rook, 11 - queen, 12 - king
	// 13 - attacked by white, 14 - attacked by black
	// 15 - defended piece by white, 16 - defended piece by black
	// ......................................
	// move - who moved: 'w' or 'b'

	int whoMoved = 1, whoTarget = 7, kingMovedx = 0, kingMovedy = 0, kingTargetx = 0, kingTargety = 0,
		counter = 0;

	// counter counts the number f checks (0, 1, 2), 0 means return 0, double check means king has to move

	if (move == 'b') {
		whoMoved = 7;
		whoTarget = 1;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			/*if (board[i][j] == whoTarget + 5) {  // getting info about kings' positions
				kingTargetx = i;
				kingTargety = j;
			}
			if (board[i][j] == whoMoved + 5) {
				kingMovedx = i;
				kingMovedy = j;
			}
			// coloring the attacked squares and checking for a check:
			if (whoMoved <= board[i][j] && board[i][j] <= whoMoved + 5) {
				colorBoard(board, board[i][j], i, j);
			}*/
		}
	}
	return 0;
}



int main() {

	return 0;
}
