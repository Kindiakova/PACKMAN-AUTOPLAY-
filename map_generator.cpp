#include <iostream>
#include <QVector>
#include <random>
#include <QFile>
#include <QQueue>
#include <QTextStream>
#include <algorithm>
#include "options.h"
#include "qdebug.h"


#define OPT_BALL_COUNT 400
#define MIN_BALL_COUNT 200

enum Direction { UP, RIGHT, DOWN, LEFT };
int balls_counter = 0;
QVector<QVector<int>> maze;

QVector<int> dx = {0, 1, 0, -1};
QVector<int> dy = {-1, 0, 1, 0};

void generateRandomMaze(int y, int x) {
    QQueue<QPair<int, int> > q;
    q.push_front(qMakePair(x, y));

    QVector<int> directions = {UP, RIGHT, DOWN, LEFT};

    std::random_device rd;
    std::mt19937 g(rd());


    while(!q.empty()) {

        x = q.head().first;
        y = q.head().second;
        q.pop_front();


        int num = rand()%3 + 2;
        if (balls_counter >= OPT_BALL_COUNT) num = 2;
        std::shuffle(directions.begin(), directions.end(), g);

        for (int i = 0; i < 4; ++i){
            int nx = (x + dx[directions[i]] + map_width)% map_width;
            int ny = (y + dy[directions[i]] + map_height) % map_height;

            if (maze[ny][nx] != 1) num--;
        }

        for (int i = 0; i < 4; ++i){
            int nx = (x + dx[directions[i]] + map_width)% map_width;
            int ny = (y + dy[directions[i]] + map_height) % map_height;

            if (maze[ny][nx] == 1 && num > 0){
                q.push_front(qMakePair(nx, ny));
                maze[ny][nx] = 4;
                balls_counter++;
                num--;
            }
        }
    }
}


void printMaze() {
    QFile outputFile("C:/Users/Diashka/Documents/PACMEN/game_objects/map_objects/map.txt");

   if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() <<  "Error opening file for map generation";
      return;
   }

    QTextStream out(&outputFile);

    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_width; ++j) {
            if (maze[i][j] == -1) out << 'r';
            else if (maze[i][j] == -2) out << 'p';
            else if (maze[i][j] == -3) out << 'b';
            else if (maze[i][j] == -4) out << 'y';
            else if (maze[i][j] == -5) out << 'P';
            else out << maze[i][j];
        }
        out << '\n';
    }
    outputFile.close();
}

void build_ghost_box(){
    maze[8][14] = -1;
    maze[9][14] = 3;
    maze[9][12] = maze[9][13] = maze[9][15] = maze[9][16] = 8;
    maze[10][13] = maze[10][14] = maze[10][15] = 0;
    maze[11][13] = -2; maze[11][14] = -3; maze[11][15] = -4;
    maze[12][12] = maze[12][13] = maze[12][14] = maze[12][15] = maze[12][16] = 8;
    maze[10][12] = maze[11][12] =  maze[10][16] = maze[11][16] = 8;
}

bool isWall(int i, int j){
    if (i < 0 || j < 0) return false;
    if (i >= map_height || j >= map_width) return false;

    int x = maze[i][j];
    return (x == 1 || x == 2 || x == 8);
}

void rebuild_walls(){
    maze[0][0] = maze[0][map_width-1] = maze[map_height-1][0] = maze[map_height-1][map_width - 1] = 1;
    for (int i = 0; i < map_height; ++i){
        for (int j = 0; j < map_width; ++j){
            if (isWall(i, j)){

                if (isWall(i+1, j)) maze[i][j] = 1;
                else maze[i][j] = 2;
            }
        }
    }
}

void insert_pacman_and_superballs(){
     QVector<QPair<int,int> > postions;
     for (int i = 1; i < map_height-1; ++i){
         for (int j = 1; j < map_width-1; ++j)
             if (i >= 7 && i <= 12 && j >= 12 && j <= 16) continue;
             else if (maze[i][j] == 4) postions.append(QPair<int, int>(i, j));
     }

     std::random_device rd;
     std::mt19937 g(rd());
     std::shuffle(postions.begin(), postions.end(), g);
     maze[postions[0].first][postions[0].second] = -5;

     maze[postions[1].first][postions[1].second] = 5;
     maze[postions[2].first][postions[2].second] = 5;
     maze[postions[3].first][postions[3].second] = 5;
     maze[postions[4].first][postions[4].second] = 5;

}

void generate_map() {

    while(balls_counter < MIN_BALL_COUNT){
        balls_counter = 0;
        maze.resize(map_height, QVector<int>(map_width, 1));


        build_ghost_box();
        generateRandomMaze(8, 14);
    }
    if (maze[8][12] == 4) maze[8][12] = 0;
    if (maze[8][13] == 4) maze[8][13] = 0;
    if (maze[8][15] == 4) maze[8][15] = 0;
    if (maze[8][16] == 4) maze[8][16] = 0;
    insert_pacman_and_superballs();
    rebuild_walls();
    printMaze();
}
