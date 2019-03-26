/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: joaop
 *
 * Created on 26 de Março de 2019, 14:44
 */

#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;

//map
const int width = 20;
const int height = 20;

//set snake position and points
int x,y, fruitX, fruitY, score;

//controls
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//for snake tail
int tailX[100], tailY[100];
int nTail; //length of the tail

void Setup(){
    gameOver = false;
    dir = STOP;
    
    //center on map
    x = width/2;
    y = height/2;

    //put fruits on the map
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void Draw(){
    //Draw map
    system("cls"); //clear screen
    
    for(int i = 0; i<width+2; i++){
        cout << "#";
    }
    cout << endl;    
    
    for(int i = 0; i<width; i++){
        for(int j = 0 ; j<height; j++){
            if( j == 0){
                cout << "#";
            }
            
            if(i == y && j == x){
                //print the head of snake
                cout << "O";
            }else if ( i == fruitY && j == fruitX){
                //print the fruit
                cout << "F";
            }else{
                bool print = false;
                for(int k=0; k<nTail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        //if the snake eat the fruit, increase the tail
                        cout << "o";
                        print = true;
                    }
                }
                if(!print){
                    cout << " ";
                }
            }
            
            if(j == width - 1){
                cout << "#";
            }
        }
        cout << endl;
    }
    
    for(int i = 0; i<height+2; i++){
        cout << "#";
    }
    cout << endl;
    
    //print the game score
    cout << "Score : " << score << endl;
    
}

void Input(){
    if(_kbhit()){
        //if keyboard is press - return boolean
        switch(_getch()){
            //w-a-s-d -> controls snake
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                //end the game
                gameOver = true;
                break;
        }
    }
}

void Logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i<nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    
//    if(x > width || x < 0 || y > height || y < 0){
//        gameOver = true;
//    }
    
    if(x >= width){
        x = 0;
    }else if(x < 0){
        x = width - 1;
    }

    if(y >= height){
        y = 0;
    }else if(y < 0){
        y = height - 1;
    }    
    
    for(int i = 0; i<nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    
    if(x == fruitX && y == fruitY){
        //increase the score and the snake tail
        nTail++;
        score+= 10;
        //put the fruit in other place
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    
    while(!gameOver){
        Draw();
        Input(); 
        Logic();
        Sleep(15);
    }
    
    return 0;
}

