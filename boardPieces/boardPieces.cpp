#include <iostream>
using namespace std;

// COMPLETE "Move", "Shift"

class Piece {  // is a square by default
public:
	char type = '0', color = 0;  // type from { P, N, B, R, Q, K }; color: { B, W }
	int x = 0, y = 0, attacked[2] = { 0, 0 };  // x, y = 0..7; attacked[0] - by WHITE, [1] - BLACK
	Piece(int x1, int y1) {
		x = x1;
		y = y1;
	}
};

class Board {
private:
	Piece*** rBoard;  // real board; white pawns goes to [...][7], black to [...][0]
	int isScanned = 0;  // 0 - no, 1 - yes

public:
	Board() {
		rBoard = new Piece * *[8];
		for (int i = 0; i <= 7; i++) {
			rBoard[i] = new Piece * [8];
		}
		for (int i = 0; i <= 7; i++) {
			for (int j = 0; j <= 7; j++) {
				rBoard[i][j] = new Piece(i, j);
				
			}
		}
	}

	int PutPiece(char piece, int x, int y, char color);  // 0 if everything is OK, 1 if something wrong

	void RemovePiece(int x, int y);

	void PrintBoard();  // prints from white's perspective, 1-rank is down

	void PrintAttackes();  // prints attackes of every square (white+black)

	int Scan();  // gives attackes and defends to pieces and squares

	int Shift(Piece* piece, int x, int y);  // moves any piece to any square. 0 if x,y are normal, 1 if not

	int Move(Piece* piece, int x, int y);  // moves piece where it can go. 0 if correct move, 1 if not

	~Board() {
		for (int i = 0; i <= 7; i++) {
			for (int j = 0; j <= 7; j++) {
				delete[] rBoard[i][j];

			}
		}
		for (int i = 0; i <= 7; i++) {
			delete[] rBoard[i];
		}
		delete[] rBoard;
	}
};

class Pawn : public Piece {
public:
	Pawn(int xb, int yb, char col) : Piece(xb, yb) {
		x = xb;
		y = yb;
		if (col == 'B') color = col;
		else color = 'W';
		type = 'P';
	}
};

class Knight : public Piece {
public:
	Knight(int xb, int yb, char col) : Piece(xb, yb) {
		x = xb;
		y = yb;
		if (col == 'B') color = col;
		else color = 'W';
		type = 'N';
	}
};

class Bishop : public Piece {
public:
	Bishop(int xb, int yb, char col) : Piece(xb, yb) {
		x = xb;
		y = yb;
		if (col == 'B') color = col;
		else color = 'W';
		type = 'B';
	}
};

class Rook : public Piece {
public:
	Rook(int xb, int yb, char col) : Piece(xb, yb) {
		x = xb;
		y = yb;
		if (col == 'B') color = col;
		else color = 'W';
		type = 'R';
	}
};

class Queen : public Piece {
public:
	Queen(int xb, int yb, char col) : Piece(xb, yb) {
		x = xb;
		y = yb;
		if (col == 'B') color = col;
		else color = 'W';
		type = 'Q';
	}
};

class King : public Piece {
public:
	King(int xb, int yb, char col) : Piece(xb, yb) {
		x = xb;
		y = yb;
		if (col == 'B') color = col;
		else color = 'W';
		type = 'K';
	}
};


int Board::PutPiece(char piece, int x, int y, char color) {  // 0 if everything is OK, 1 if something wrong
	if (0 > x || x > 7 || 0 > y || y > 7 || (color != 'W' && color != 'B')) return 1;
	delete[] rBoard[x][y];
	switch (piece) {
	case 'P': { rBoard[x][y] = new Pawn(x, y, color); break; }
	case 'N': {rBoard[x][y] = new Knight(x, y, color); break; }
	case 'B': {rBoard[x][y] = new Bishop(x, y, color); break; }
	case 'R': {rBoard[x][y] = new Rook(x, y, color); break; }
	case 'Q': {rBoard[x][y] = new Queen(x, y, color); break; }
	case 'K': {rBoard[x][y] = new King(x, y, color); break; }
	default: return 1;
	}
	return 0;
}


void Board::RemovePiece(int x, int y) {
	delete[] rBoard[x][y];
	rBoard[x][y] = new Piece(x, y);
}


void Board::PrintBoard() {  // prints from white's perspective, 1-rank is down
	for (int j = 7; j >= 0; j--) {
		for (int i  = 0; i <= 7; i++) {
			std::cout << rBoard[i][j]->type << ' ';
		}
		std::cout << endl;
	}
}


void Board::PrintAttackes() {  // prints attackes of every square (white+black)
	for (int j = 7; j >= 0; j--) {
		for (int i = 0; i <= 7; i++) {
			std::cout << rBoard[i][j]->attacked[0] + rBoard[i][j]->attacked[1] << ' ';
		}
		std::cout << endl;
	}
}


int Board::Scan() {  // gives attackes and defends to pieces and squares, returns -1 already scanned
	if (isScanned == 1) return -1;  // 0, neither king under check, 1 - white king, 2 - black
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			int color = 0;  // color  0 or 1 - white or black
			if (rBoard[i][j]->color == 'B') color = 1;
			switch (rBoard[i][j]->type) {

			case 'P': {
				int color1 = -2 * color + 1;  // = -1 or 1, for moving
				for (int k = -1; k <= 1; k += 2) {
					if ((0 <= i + k) && (i + k <= 7) && (0 <= j + color1) && (j + color1 <= 7)) {
						rBoard[i + k][j + color1]->attacked[color] += 1;
					}
				}
				break;
			}
			case 'N': {
				for (int k = 1; k <= 2; k++) {
					for (int l = -1; l <= 1; l += 2) {  // for multiplying with k
						for (int m = -1; m <= 1; m += 2) {  // for multiplying with (3-k)
							if ((0 <= i + l * k) && (i + l * k <= 7) &&
								(0 <= j + m * (3 - k)) && (j + m * (3 - k) <= 7)) {
								rBoard[i + l * k][j + m * (3 - k)]->attacked[color] += 1;
							}
						}
					}
				}
				break;
			}
			case 'B': {
				for (int l = -1; l <= 1; l+=2) {
					for (int m = -1; m <= 1; m += 2) {
						for (int k = 1; k <= 7; k++) {
							if ((i + l * k <= 7) && (j + m * k <= 7) &&
								(i + l * k >= 0) && (j + m * k >= 0)) {
								rBoard[i + l * k][j + m * k]->attacked[color] += 1;
								if (rBoard[i + l * k][j + m * k]->type != '0') break;
							}
							else break;
						}

					}
				}
				break;
			}
			case 'R': {
				for (int l = 0; l <= 1; l += 1) {
					for (int m = -1; m <= 1; m += 2) {
						for (int k = 1; k <= 7; k++) {
							if ((i + l * m * k <= 7) && (j + (1 - l) * m * k <= 7) &&
								(i + l * m * k >= 0) && (j + (1 - l) * m * k >= 0)) {
								rBoard[i + l * m * k][j + (1 - l) * m * k]->attacked[color] += 1;
								if (rBoard[i + l * m * k][j + (1 - l) * m * k]->type != '0') break;
							}
							else break;
						}
					}
				}
				break;
			}
			case 'Q': {
				for (int l = -1; l <= 1; l += 2) {  // bishop code
					for (int m = -1; m <= 1; m += 2) {
						for (int k = 1; k <= 7; k++) {
							if ((i + l * k <= 7) && (j + m * k <= 7) &&
								(i + l * k >= 0) && (j + m * k >= 0)) {
								rBoard[i + l * k][j + m * k]->attacked[color] += 1;
								if (rBoard[i + l * k][j + m * k]->type != '0') break;
							}
							else break;
						}

					}
				}
				for (int l = 0; l <= 1; l += 1) {  // rook code
					for (int m = -1; m <= 1; m += 2) {
						for (int k = 1; k <= 7; k++) {
							if ((i + l * m * k <= 7) && (j + (1 - l) * m * k <= 7) &&
								(i + l * m * k >= 0) && (j + (1 - l) * m * k >= 0)) {
								rBoard[i + l * m * k][j + (1 - l) * m * k]->attacked[color] += 1;
								if (rBoard[i + l * m * k][j + (1 - l) * m * k]->type != '0') break;
							}
							else break;
						}
					}
				}
				break;
			}
			case 'K': {
				for (int k = -1; k <= 1; k++) {
					for (int m = -1; m <= 1; m++) {
						if (m == k && m == 0) continue;
						if (i + k >= 0 && i + k <= 7 && j + m >= 0 && j + m < 7) {
							rBoard[i + k][j + m]->attacked[color] += 1;
						}
					}
				}
				break;
			}
			default: {}
			}
		}
	}
	isScanned = 1;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int opColor = 1, color = 0;  // opposite color  1 or 0 - white or black
			if (rBoard[i][j]->color == 'B') {
				opColor = 0;
				color = 1;
			}

			if (rBoard[i][j]->type == 'K') {
				if (rBoard[i][j]->attacked[opColor] != 0) return color + 1;
			}
		}
	}
	return 0;
}

//////////////////////////////////////////////////////
int Board::Shift(Piece* piece, int x, int y) {
	piece->x = x;
	piece->y = y;

}


int main() {
	Board b;
	b.PrintBoard();
	cout << endl << endl;
	b.PutPiece('K', 3, 1, 'W');
	b.PutPiece('Q', 3, 5, 'B');
	cout << endl << endl;
	b.PrintBoard();
	b.Scan();
	cout << endl << endl;
	b.PrintAttackes();
}
