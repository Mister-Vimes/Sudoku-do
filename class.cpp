#include <iostream>
#include <fstream>
#include <vector>

class Sudoku {

public:
    int data[9][9];
    int frame[9][9];

    std::vector<int> collision_check(int x, int y) {
        std::vector<int> result(10, 0);
        for(int i = 0; i < 9; i++) {
            if(i != y) {
                result[this->data[x][i]] = 1;
            }
            if(i != x) {
                result[this->data[i][y]] = 1;
            }
        }

        int xx = 3 * (x / 3);
        int yy = 3 * (y / 3);
        for(int i = xx; i < xx + 3; i++) {
            for(int j = yy; j < yy + 3; j++) {
                if(i != x || j != y) {
                    result[this->data[i][j]] = 1;
                }
            }
        }
        return result;
    }

    void write(int x, int y, int v){
        this->data[x][y] = v;
    }
    void display() {
        std::cout << "=======================\n";
        for(int i = 0; i < 9; i++) {
        std::cout << "||";
            for(int j = 0; j < 9; j++) {
                std::cout << this->data[i][j] << (((j + 1) % 3 == 0)? "||" : "|");
            }
            std::cout << "\n" << (((i + 1) % 3 == 0)? "=======================" : "-----------------------") << "\n";
        }
    }

    bool scan(int x, int y) {
        if(this->frame[x][y] != 0){
            if(x > 7 && y > 7) { // Edge case for pre-filled se corner
                return this->victory();
            } else {
                return this->scan((x + ((y + 1) / 9)), (y + 1) % 9);
            }
        }
        for(int v = 1; v < 10; v++){
            if(collision_check(x, y)[v] == 0) {
                this->write(x, y, v);
                if(this->victory()) {
                    this->display();
                    return true;
                }
                if(scan((x + ((y + 1) / 9)) % 9, (y + 1) % 9)) {
                    return true;
                } else {
                    write(x, y, 0);
                }
            }
        }
        return this->victory();
    }

    bool victory() {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(data[i][j] == 0 || collision_check(i, j)[data[i][j]] == 1) {
                    return false;
                }
            }
        }
        return true;
    }

    Sudoku() {
        std::ifstream grids("data.txt");
        int i = 0;
        std::string row;
        while(getline(grids, row) && i < 9){
            int j = 0;
            for(int k = 0; k <= row.size() && j < 9; k++){
                if(row[k] >= '0' && row[k] <= '9') {
                    this->data[i][j] = int(row[k] - '0');
                    this->frame[i][j] = int(row[k] - '0');
                    j++;
                }
            }
            i++;
        }
        grids.close();
    }
};
