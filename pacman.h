#ifndef PACMAN_H
#define PACMAN_H

#include "gameobject.h"
#include "imoveable.h"
#include <QVector>

class Pacman : IMoveable, public GameObject
{
public:
    Pacman(Game *, int, int, int, int);
    void move();
    Game *game;

    friend class Game;

private:
    void moveup() override;
    void movedown() override;
    void moveleft() override;
    void moveright() override;
    bool good(int, int) override;
    bool great(int, int);
    void bfs(int, int);
    bool checkPath();
    void autoPlay();
    GameObject::Dir get_random_dir();


    void eat_ball(int, int);
    int safe_time;

    QVector<QPixmap> anim[4];   // animations
    int anim_index;
    int lives;
    QVector<Dir> MoveList;
    QVector<QPair<int,int> > path;
     QPair<int, int> escape_point;

};


#endif // PACMAN_H
