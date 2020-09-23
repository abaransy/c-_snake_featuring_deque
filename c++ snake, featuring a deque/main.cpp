//
//  main.cpp
//  c++ snake, featuring a deque
//
//  Created by Aatef Baransy on 9/21/20.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class SnakeGame {
private:
    int height = 0;
    int width = 0;
    int score = 0;
    int length = 0;
    int foodPointer = 0;
    vector<vector<int>> grid;
    vector<vector<int>> f;
    deque<pair<int, int>> snake;
public:
//
//        @param width - screen width
//        @param height - screen height
//        @param food - A list of food positions
//        E.g food = [[1,1], [1,0]] means the first food is positioned at         [1,1], the second is at [1,0].
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        width = width;
        height = height;
        grid = vector<vector<int>>(height, vector<int>(width, 0));
        f = food;
        grid[0][0] = INT_MAX;
        pair<int, int> initial = {0, 0};
        snake.push_back(initial);
    }
    
    void updateFood() {
        if (foodPointer >= f.size())
            return;
        vector<int> currFood = f[foodPointer];
        if (invalidPosition(currFood[0], currFood[1]))
            return;
        grid[currFood[0]][currFood[1]] = 1;
        foodPointer++;
    }
    
//     Moves the snake.
//        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
//        @return The game's score after the move. Return -1 if game over.
//        Game over when snake crosses the screen boundary or bites its           body.
    bool invalidPosition(int i, int j) {
        //check boundary
        return (i >= grid.size() || i < 0 || j >= grid[i].size() || j < 0);
    }
    
    bool didEatSelf(int i, int j, int xTail, int yTail) {
        //if the snake wants to move to a spot that is already occupied
        //by itself, it can only do so if it is tail
        //this returns true if it moved to a spot that is occupied
        //by itself, and is NOT the tail.
        return grid[i][j] == INT_MAX && !(i == xTail && j == yTail);
    }
    
    int move(string direction) {
        if (foodPointer == 0)
            updateFood();
        
        pair<int, int> head = snake.back();
        int i = NULL;
        int j = NULL;
   
        switch(direction[0]) {
            case 'U' : {
                i = head.first - 1;
                j = head.second;
                break;
            }
            case 'R' : {
                i = head.first;
                j = head.second + 1;
            
                break;
            }
            case 'D' : {
                i = head.first + 1;
                j = head.second;
                break;
            }
            case 'L' :  {
                i = head.first;
                j = head.second - 1;
                break;
            }
       }
        
        pair<int, int> tail = snake.front();
        int xTail = tail.first;
        int yTail = tail.second;
     
        if (invalidPosition(i, j) || didEatSelf(i, j, xTail, yTail))
                return -1;
        
        if (grid[i][j] == 1) { //if there is food at up
            updateFood();
            length++;
            score++;
        } else if (grid[i][j] == 0 || grid[i][j] == INT_MAX) { // if there is a blank space
            //get rid of previous tail on grid and in deque
            pair<int, int> prevTail = snake.front();
            snake.pop_front();
            grid[prevTail.first][prevTail.second] = 0;
        }
        
        //update snake deque
        pair<int, int> newHead = {i, j};
        snake.push_back(newHead);
        // add new snake node at correct position in grid
        grid[i][j] = INT_MAX;
        
        return score;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
