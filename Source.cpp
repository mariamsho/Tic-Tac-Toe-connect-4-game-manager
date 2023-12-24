#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Player {
private:
	string name;
	string symbol;

public:
	Player() {}
	Player(string n, string sym) {
		name = n, symbol = sym;
	}

	void setName(string n) { name = n; }
	void setSymbol(string s) { symbol = s; }
	string getName() { return name; }
	string getSymbol(){return symbol;}

	friend ostream& operator<<(ostream& os, Player& player) {
		os << "Name: " << player.name << ", Symbol: " << player.symbol;
		return os;
	}

	
};

class BoardGame {
private:
	int score1=0, score2=0;				//scores for each game
	bool player = false;		//true indicated 1st plaer is using x or red, false indicated player is o or blue
	string game;
	vector<vector<string>> grid;
	Player p1, p2;
	string player1, player2, symbol1, symbol2;
	

public:
	
	BoardGame() {
		

	}

	void SetPlayerss() {
		string name;
		cout << "Enter player 1 name \n";
		cin >> name;
		p1.setName(name); p1.setSymbol("x"); player1 = name;		//set player name and symbol to default xo, when playing connect four the constructor will switch player symbols to red and blue
		cout << "Enter player 2 name \n";
		cin >> name;
		p2.setName(name); p2.setSymbol("o"); player2 = name;
	}

	string getPlayer1() { return player1; }
	string getPlayer2() { return player2; }
	void setSymbol1(string s) { p1.setSymbol(s); }
	void setSymbol2(string s) { p2.setSymbol(s); }


	void setGridSize(int rows, int cols) {
		grid.assign(rows, vector<string>(cols, " "));
	}

	void setPlayer(bool ply) {
		player = ply;
	}

	void setGame(string name) {
		game = name;
	}

	void setMove(int row, int col, string x) {
		grid[row][col] = x;
	}

	void setScore(string player) {
		if (player == "x" || player == "red") {
			score1 ++;
		}
		else if (player == "o" || player == "blue") {
			score2 ++;
		}
	}

	void clearScore() { score1 = 0, score1 = 0; }

	bool getPlayer() { return player; }

	string getGame() { return game;}

	string getspace(int row, int col) {
		return grid[row][col];
	}

	
	virtual void printBoard() {
		for (int i = grid.size() - 1; i >= 0; i--) { 
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j].empty()) {
					grid[i][j] = " ";
				}
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
	}

	 virtual void makeMove() {};
	 virtual bool isGameOver() { return true; };


	 void restartGame() {
		 cout << "New game and scoreboard?";
		 string ans;
		 cin >> ans;
		 if (ans == "yes") {
			 score1 = 0, score2 = 0;
		 }
		 grid.clear();
		 
	 }

};


class TicTacToe : public BoardGame {

public:
	TicTacToe() {		
		setGame("Tic-Tac-Toe");
		setGridSize(3, 3);

	}



	void printBoard() {
		BoardGame::printBoard();
	}

	bool checkWin() {
		for (int i = 0; i < 3; i++) {
			// Check rows
			if (getspace(i, 0) == "x" && getspace(i, 1) == "x" && getspace(i, 2) == "x") {
				cout << "Player 'x' wins!" << endl;
				setScore("x");
				return true;
			}
			if (getspace(i, 0) == "o" && getspace(i, 1) == "o" && getspace(i, 2) == "o") {
				cout << "Player 'o' wins!" << endl;
				setScore("o");
				return true;
			}

			// Check columns
			if (getspace(0, i) == "x" && getspace(1, i) == "x" && getspace(2, i) == "x") {
				cout << "Player 'x' wins!" << endl;
				setScore("x");
				return true;
			}
			if (getspace(0, i) == "o" && getspace(1, i) == "o" && getspace(2, i) == "o") {
				cout << "Player 'o' wins!" << endl;
				setScore("o");
				return true;
			}
		}

		// Check diagonals
		if ((getspace(0, 0) == "x" && getspace(1, 1) == "x" && getspace(2, 2) == "x") ||
			(getspace(0, 2) == "x" && getspace(1, 1) == "x" && getspace(2, 0) == "x")) {
			cout << "Player 'x' wins!" << endl;
			setScore("x");
			return true;
		}
		if ((getspace(0, 0) == "o" && getspace(1, 1) == "o" && getspace(2, 2) == "o") ||
			(getspace(0, 2) == "o" && getspace(1, 1) == "o" && getspace(2, 0) == "o")) {
			cout << "Player 'o' wins!" << endl;
			setScore("o");
			return true;
		}

		return false; // No win found
	}

	bool checkDraw() {
		
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (getspace(i, j) == " ") {
						return false; // At least one space is empty
					}
				}
			}
			return true; // All spaces are filled
		
	}

	bool isGameOver() {
		if (checkWin()) {
			return true;
		}
		else if (!checkWin()) {
			if (checkDraw()) {
				cout << "Draw!\n";
				return true;
			}
			else {
				return false;
			}
		}

	}

	void makeMove(int row, int col) {
		setPlayer(!getPlayer());					// Switch the player's turn

		string space = getspace(row, col);
		if (row < 0 || row >= 3 || col < 0 || col >= 3 || space != " ") {
			cout << "Invalid move. Try again." << endl;
			return;
		}
		if (getPlayer()) {
			setMove(row, col, "x");
		}
		else if(!getPlayer()){
			setMove(row, col, "o");
		}


		if (getPlayer()) {
			cout << "next turn: " << getPlayer1() << endl;
		}
		else {
			cout << "next turn: " << getPlayer2() << endl;
		}

		if (isGameOver()) {
			cout << "Game Over!" << endl;
		}
	}
};


class ConnectFour : public BoardGame {

public:
	ConnectFour() {
		setGame("Connect Four");
		setGridSize(6, 7);
		setSymbol1("red");
		setSymbol2("blue");
	}


	void printBoard() {
		BoardGame::printBoard();
	}

	bool checkWin() {
		// Check for horizontal wins
		for (int row = 0; row < 6; row++) {
			for (int col = 0; col < 4; col++) {
				if (getspace(row, col) == "red" &&
					getspace(row, col + 1) == "red" &&
					getspace(row, col + 2) == "red" &&
					getspace(row, col + 3) == "red") {
					setScore("red");
					cout << "Red wins!\n";
					return true; // Red wins horizontally
				}

				if (getspace(row, col) == "blue" &&
					getspace(row, col + 1) == "blue" &&
					getspace(row, col + 2) == "blue" &&
					getspace(row, col + 3) == "blue") {
					setScore("blue");
					cout << "Blue wins!\n";
					return true; // Blue wins horizontally
				}
			}
		}

		// Check for vertical wins
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 7; col++) {
				if (getspace(row, col) == "red" &&
					getspace(row + 1, col) == "red" &&
					getspace(row + 2, col) == "red" &&
					getspace(row + 3, col) == "red") {
					setScore("red");
					cout << "Red wins!\n";
					return true; // Red wins vertically
				}

				if (getspace(row, col) == "blue" &&
					getspace(row + 1, col) == "blue" &&
					getspace(row + 2, col) == "blue" &&
					getspace(row + 3, col) == "blue") {
					setScore("blue");
					cout << "Blue wins!\n";
					return true; // Blue wins vertically
				}
			}
		}
	

		// Check diagonal wins (bottom left to top right)
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 4; col++) {
				if (getspace(row, col) == "red" &&
					getspace(row + 1, col + 1) == "red" &&
					getspace(row + 2, col + 2) == "red" &&
					getspace(row + 3, col + 3) == "red") {
					setScore("red");
					cout << "Red wins!\n";
					return true; // Red wins diagonally
				}

				if (getspace(row, col) == "blue" &&
					getspace(row + 1, col + 1) == "blue" &&
					getspace(row + 2, col + 2) == "blue" &&
					getspace(row + 3, col + 3) == "blue") {
					setScore("blue");
					cout << "Blue wins!\n";
					return true; // Blue wins diagonally
				}
			}
		}

		// Check diagonal wins (bottom right to top left)
		for (int row = 0; row < 3; row++) {
			for (int col = 3; col < 7; col++) {
				if (getspace(row, col) == "red" &&
					getspace(row + 1, col - 1) == "red" &&
					getspace(row + 2, col - 2) == "red" &&
					getspace(row + 3, col - 3) == "red") {
					setScore("red");
					cout << "Red wins!\n";
					return true; // Red wins diagonally
				}

				if (getspace(row, col) == "blue" &&
					getspace(row + 1, col - 1) == "blue" &&
					getspace(row + 2, col - 2) == "blue" &&
					getspace(row + 3, col - 3) == "blue") {
					setScore("blue");
					cout << "Blue wins!\n";
					return true; // Blue wins diagonally
				}
			}
		}

		return false; // No win found
	}

	bool checkDraw() {
		for (int row = 0; row < 6; row++) {
			for (int col = 0; col < 7; col++) {
				if (getspace(row, col) == " ") {
					return false; // At least one empty slot, not a draw
				}
			}
		}
		cout << "No winner\n";
		return true; // All slots are filled, it's a draw 
	}

	bool isGameOver() {
		if (checkWin()) {
			return true;
		}
		else if (!checkWin()) {
			if (checkDraw()) {
				return true;
			}
			else {
				return false;
			}
		}

	}


	void makeMove(int col) {
		if (col < 0 || col >= 7) {
			cout << "Invalid move. Try again." << endl;
			return;
		}

		// Find an empty slot from the bottom up in the selected column
		int row = 5;
		while (row >= 0 && getspace(row,col) != " ") {
			row--;
		}

		if (row >= 0) {
			if (getPlayer()) {
				setMove(row, col, "red");
			}
			else {
				setMove(row, col, "blue");
			}

			// Switch the player's turn
			setPlayer(!getPlayer());
			if (isGameOver()) {
				cout << "Game Over!" << endl;
			}
			if (getPlayer()) {
				cout << "next turn: " << BoardGame::getPlayer1() << endl;
			}
			else {
				cout << "next turn: " << BoardGame::getPlayer2() << endl;
			}
		}
		else {
			cout << "Column is full. Try another column." <<endl;
		}

	}
	

};



int main() {



	BoardGame game;
	Player p1("jo", "x"), p2("of", "o");
	cout << p1 << endl;
	cout << p2 << endl;


	game.SetPlayerss();


	vector<TicTacToe*> TicVector;
	vector<ConnectFour*> ConnectVector;

	TicTacToe tic;
	tic.makeMove(0, 0);  tic.makeMove(1, 1);  tic.makeMove(0, 2); tic.makeMove(1, 2);
	 tic.makeMove(1, 0);

	TicVector.push_back(&tic);


	

	tic.printBoard();


	//ConnectFour connect, connect2, connect3;
	//connect.makeMove(0); connect.makeMove(0);
	//connect.printBoard();
	

	//ConnectVector.push_back(&connect); ConnectVector.push_back(&connect2); ConnectVector.push_back(&connect3);


	//for (auto it = ConnectVector.begin(); it != ConnectVector.end(); ++it) {
	//	(*it)->printBoard();
	//}




}
