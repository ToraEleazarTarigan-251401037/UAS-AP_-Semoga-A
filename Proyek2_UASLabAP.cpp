#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int logicBoard[10][10];
    char viewBoard[10][10];
    int size;
    int totalBombs;
    int flagsPlaced;
    time_t startTime;
    bool isGameOver;

    void placeBombs() {
        int bombsPlanted = 0;
        while (bombsPlanted < totalBombs) {
            int r = rand() % size;
            int c = rand() % size;

            if (logicBoard[r][c] != -1) {
                logicBoard[r][c] = -1;
                bombsPlanted++;
            }
        }
    }

    void calculateNeighbors() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (logicBoard[r][c] == -1) continue;

                int bombCount = 0;
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < size && nc >= 0 && nc < size) {
                            if (logicBoard[nr][nc] == -1) {
                                bombCount++;
                            }
                        }
                    }
                }
                logicBoard[r][c] = bombCount;
            }
        }
    }

    void floodFill(int r, int c) {
        if (r < 0 || r >= size || c < 0 || c >= size) return;
        if (viewBoard[r][c] != '#') return;

        viewBoard[r][c] = '0' + logicBoard[r][c];

        if (logicBoard[r][c] > 0) return;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr != 0 || dc != 0) {
                    floodFill(r + dr, c + dc);
                }
            }
        }
    }

public:
    void initGame(int n, int bombs) {
        size = n;
        totalBombs = bombs;
        flagsPlaced = 0;
        isGameOver = false;
        startTime = time(0);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                logicBoard[i][j] = 0;
                viewBoard[i][j] = '#';
            }
        }

        placeBombs();
        calculateNeighbors();
    }

    void displayBoard() {
        cout << "\n=== MINESWEEPER ++ ===\n";
        cout << "Sisa Bom/Flag: " << totalBombs - flagsPlaced << "\n\n";

        cout << "    ";
        for (int j = 1; j <= size; j++) {
            cout << j << " ";
        }
        cout << "\n   " << string(size * 2, '-') << "\n";

        for (int i = 0; i < size; i++) {
            cout << i + 1 << " | ";
            for (int j = 0; j < size; j++) {
                cout << viewBoard[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void toggleFlag(int r, int c) {
        if (viewBoard[r][c] == '#') {
            viewBoard[r][c] = 'F';
            flagsPlaced++;
        } else if (viewBoard[r][c] == 'F') {
            viewBoard[r][c] = '#';
            flagsPlaced--;
        }
    }

    void openCell(int r, int c) {
        if (viewBoard[r][c] != '#') return;

        if (logicBoard[r][c] == -1) {
            isGameOver = true;
            return;
        }

        if (logicBoard[r][c] > 0) {
            viewBoard[r][c] = '0' + logicBoard[r][c];
            return;
        }

        if (logicBoard[r][c] == 0) {
            floodFill(r, c);
        }
    }

    bool checkWin() {
        if (flagsPlaced != totalBombs) return false;

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (logicBoard[r][c] == -1 && viewBoard[r][c] != 'F') return false;
                if (logicBoard[r][c] != -1 && viewBoard[r][c] == 'F') return false;
            }
        }
        return true;
    }

    bool getGameOverStatus() {
        return isGameOver;
    }

    void showMines() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (logicBoard[r][c] == -1) {
                    viewBoard[r][c] = '*';
                }
            }
        }
        displayBoard();
    }

    void printTime() {
        time_t endTime = time(0);
        long totalTime = endTime - startTime;
        cout << "Waktu bermain: " << totalTime << " detik.\n";
    }
};

int main() {
    srand(time(0));
    Minesweeper game;
    int menuPilihan;

    do {
        cout << "=== MENU UTAMA MINESWEEPER++ ===\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilih opsi (1/2): ";
        cin >> menuPilihan;

        if (menuPilihan == 1) {
            int n, bombs;
            do {
                cout << "Masukkan ukuran papan (N x N, skala 4-10): ";
                cin >> n;
                if (n < 4 || n > 10) {
                    cout << "Ukuran papan harus antara 4 dan 10. Silakan coba lagi.\n";
                }
            } while (n < 4 || n > 10);

            do {
                cout << "Masukkan jumlah bom (1 sampai " << (n * n) - 1 << "): ";
                cin >> bombs;

                if (bombs < 1 || bombs >= n * n) {
                    cout << "Jumlah bom tidak valid! Silakan coba lagi.\n";
                }
            } while (bombs < 1 || bombs >= n * n);

            game.initGame(n, bombs);
            game.displayBoard();

            while (!game.getGameOverStatus() && !game.checkWin()) {
                int pilihan, inputR, inputC;

                cout << "Aksi Pemain:\n";
                cout << "1. Buka Kotak (Open)\n";
                cout << "2. Tandai Bom (Flag/Unflag)\n";
                cout << "Pilih aksi (1/2): ";
                cin >> pilihan;

                cout << "Masukkan koordinat Baris Kolom (contoh: 2 3): ";
                cin >> inputR >> inputC;

                if (inputR < 1 || inputR > n || inputC < 1 || inputC > n) {
                    cout << "Koordinat di luar jangkauan papan! Silakan coba lagi.\n";
                    continue;
                }

                int r = inputR - 1;
                int c = inputC - 1;

                if (pilihan == 1) {
                    game.openCell(r, c);
                } else if (pilihan == 2) {
                    game.toggleFlag(r, c);
                } else {
                    cout << "Pilihan aksi tidak valid!\n";
                }

                if (!game.getGameOverStatus() && !game.checkWin()) {
                    game.displayBoard();
                }
            }

            if (game.getGameOverStatus()) {
                cout << "\n====================================\n";
                cout << " BOOM!! Kamu menginjak bom. Game Over!\n";
                cout << "====================================\n";
                game.showMines();
                game.printTime();
            } else if (game.checkWin()) {
                cout << "\n====================================\n";
                cout << " SELAMAT! Kamu berhasil menjinakkan semua bom!\n";
                cout << "====================================\n";
                game.printTime();
            }
        }
    } while (menuPilihan != 2);

    return 0;
}