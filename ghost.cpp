#include "ghost.h"
#include "game.h"
#include "options.h"
#include <QRandomGenerator>
#include <QQueue>
#define W (GameObject::Width)

Ghost::Ghost(Game *game, int x, int y, int tmp_x, int tmp_y) : GameObject(
    GameObject::Ghost, QPixmap(), x, y, tmp_x, tmp_y)
{  
    this->game = game;
    anim_index = 0;
    dir = Dir(QRandomGenerator::global()->generate() % 4);
    status = Normal;
    set_score(GHOST_SCORE);
    panic_anim.push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/bl1.png"));
    panic_anim.push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/bl2.png"));
    running_anim.push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/run.png"));
    setZValue(2);

}


Ghost::Color Ghost::get_color()
{
    return color;
}

void Ghost::moveup()
{
    QVector<QPixmap> *ptr;
    switch (status) {
    case Normal:
        ptr = &anim[Up];
        break;
    case Panic:
        ptr = &panic_anim;
        break;
    case Running:
        ptr = &running_anim;
        break;
    }

    anim_index++;
    if (anim_index >= ptr->size()) {
        anim_index = 0;
    }
    setPixmap((*ptr)[anim_index]);
    if (static_cast<int>(y() - 1) < game->geo_y)
        setY((game->geo_y + (map_height - 1) * W));
    else setY(static_cast<int>(y()) - 1);


}

void Ghost::moveleft()
{
    QVector<QPixmap> *ptr;
    switch (status) {
    case Normal:
        ptr = &anim[Left];
        break;
    case Panic:
        ptr = &panic_anim;
        break;
    case Running:
        ptr = &running_anim;
        break;
    }

    anim_index++;
    if (anim_index >= ptr->size()) {
        anim_index = 0;
    }
    setPixmap((*ptr)[anim_index]);
    if (static_cast<int>(x() - 1) < game->geo_x)
        setX((game->geo_x + (map_width- 1) * W));
    else setX(static_cast<int>(x()) - 1);
}

void Ghost::movedown()
{
    QVector<QPixmap> *ptr;
    switch (status) {
    case Normal:
        ptr = &anim[Down];
        break;
    case Panic:
        ptr = &panic_anim;
        break;
    case Running:
        ptr = &running_anim;
        break;
    }

    anim_index++;
    if (anim_index >= ptr->size()) {
        anim_index = 0;
    }
    setPixmap((*ptr)[anim_index]);
    if (static_cast<int>(y() + 1) > game->geo_y + (map_height - 1) * W)
        setY(game->geo_y);
    else setY(static_cast<int>(y()) + 1);
}


void Ghost::moveright()
{
    QVector<QPixmap> *ptr;
    switch (status) {
    case Normal:
        ptr = &anim[Right];
        break;
    case Panic:
        ptr = &panic_anim;
        break;
    case Running:
        ptr = &running_anim;
        break;
    }

    anim_index++;
    if (anim_index >= ptr->size()) {
        anim_index = 0;
    }
    setPixmap((*ptr)[anim_index]);
    if (static_cast<int>(x()) + 1 > game->geo_x + (map_width - 1) * W)
        setX(game->geo_x);
    else setX(static_cast<int>(x()) + 1);
}


bool Ghost::good(int i, int j)
{
   i = (i + map_height)% map_height;
   j = (j + map_width)% map_width;

    switch (game->map[i][j]->get_type()) {
    case Wall:
        return false;
    case Gate:
        if (is_released == false && release_time == 0) {
            return true;
        } else if (status == Running) {
            return true;
        } else {
            return false;
        }
    default:
        return true;
    }
}


void Ghost::setdir_randomly()
{
    QVector<Dir> oklist;
    if (good(_y, _x + 1)) {
        oklist.push_back(Right);
    }
    if (good(_y, _x - 1)) {
        oklist.push_back(Left);
    }
    if (good(_y + 1, _x)) {
        oklist.push_back(Down);
    }
    if (good(_y - 1, _x)) {
        oklist.push_back(Up);
    }
    dir = oklist.at(QRandomGenerator::global()->generate() % oklist.size());
}

void Ghost::go_out_cage()
{
    set_dir(MoveTable[_y][_x][game->gate_y-1][game->gate_x]);
}


void Ghost::chase_pacman()
{

   QPair<int, int> target = goal_position();
   if (target == qMakePair(-1, -1)){
        if (color == Yellow) setdir_randomly();
        if (color == Blue) dodge_pacman();
   }
   else set_dir(MoveTable[_y][_x][target.second][target.first]);


}


void Ghost::dodge_pacman()
{
    // false if the adjacent block is a wall
    bool okdir[5] = {false, false, false, false, false};
    QVector<Dir> oklist;
    if (good(_y, _x + 1)) {
        okdir[Right] = true;
        oklist.push_back(Right);
    }
    if (good(_y, _x - 1)) {
        okdir[Left] = true;
        oklist.push_back(Left);
    }
    if (good(_y + 1, _x)) {
        okdir[Down] = true;
        oklist.push_back(Down);
    }
    if (good(_y - 1, _x)) {
        okdir[Up] = true;
        oklist.push_back(Up);
    }

    Dir backward_dir;
    switch (dir) {
    case Up:
        backward_dir = Down;
        break;
    case Down:
        backward_dir = Up;
        break;
    case Left:
        backward_dir = Right;
        break;
    case Right:
        backward_dir = Left;
        break;
    case Stop:
        backward_dir = Stop;
        break;
    }


    if (oklist.size() > 2) {
        int dist_x = game->pacman->get_x() - _x;
        int dist_y = game->pacman->get_y() - _y;
        if (dist_y < 0) {
            if (okdir[Down] && dir != Up) {
                dir = Down;
            } else {
                if (dist_x >= 0) {
                    if (okdir[Left]) {
                        dir = Left;
                    } else if (okdir[Right]) {
                        dir = Right;
                    }
                } else {
                    if (okdir[Right]) {
                        dir = Right;
                    } else if (okdir[Left]) {
                        dir = Left;
                    }
                }
            }
        } else if (dist_y > 0) {
            if (okdir[Up] && dir != Down) {
                dir = Up;
            } else {
                if (dist_x >= 0) {
                    if (okdir[Left]) {
                        dir = Left;
                    } else if (okdir[Right]) {
                        dir = Right;
                    }
                } else {
                    if (okdir[Right]) {
                        dir = Right;
                    } else if (okdir[Left]) {
                        dir = Left;
                    }
                }
            }
        } else if (dist_x < 0) {
            if(okdir[Right] && dir != Left) {
                dir = Right;
            } else {
                if (okdir[Up]) {
                    dir = Up;
                } else if(okdir[Down]) {
                    dir = Down;
                }
            }
        } else if (dist_x > 0) {
            if(okdir[Left] && dir != Right) {
                dir = Left;
            } else {
                if (okdir[Up]) {
                    dir = Up;
                } else if(okdir[Down]) {
                    dir = Down;
                }
            }
        }
    } else if (oklist.size() == 2) {
        if (okdir[dir] == false) {
            // ghost is on a corner
            if (oklist[0] == backward_dir) {
                dir = oklist[1];
            } else {
                dir = oklist[0];
            }
        }
    }
}

void Ghost::go_to_cage()
{
    set_dir(MoveTable[_y][_x][game->gate_y+1][game->gate_x]);

}


void Ghost::move()
{

    if (status != Running && release_time > 0) {
        release_time--;
    } else if (status == Panic) {
        panic_time--;
        if (panic_time <= 0) {
            status = Normal;
            game->ghost_timer[color]->setInterval(NORMAL_INTERVAL);
        }
    }

    int gh_x = static_cast<int>(x());
    int gh_y = static_cast<int>(y());
    int __x = (gh_x - game->geo_x) / W;           // block x coordinate in map
    int __y = (gh_y - game->geo_y) / W;           // block y coordinate in map
    int x_remainder = (gh_x - game->geo_x) % W;   // remainder x pixel to fit a block
    int y_remainder = (gh_y - game->geo_y) % W;   // remainder y pixel to fit a block


    if (x_remainder == 0 && y_remainder == 0) {
        _x = __x;
        _y = __y;
        if (is_released) {
            switch (status) {
            case Normal:
                chase_pacman();
                break;
            case Panic:
                dodge_pacman();
                break;
            default:
                break;
            }
        } else {
            if (release_time == 0) {
                // Time to go out the cage.
                go_out_cage();
                if (game->map[_y][_x]->get_type() == Gate) {
                    // If arriving at gate, turn into release.
                    is_released = true;
                }
            } else {
                if (status == Running) {
                    if (_x == game->gate->get_x() && _y == game->gate->get_y() + 1) {
                        status = Normal;
                        game->ghost_timer[color]->setInterval(NORMAL_INTERVAL);
                    } else {
                        // Go back to cage
                        go_to_cage();
                    }
                } else {
                    // Keep staying in the cage.
                    setdir_randomly();
                }
            }
        }
    }

    switch (dir) {
    case Stop:
        break;
    case Up:
        moveup();
        break;
    case Down:
        movedown();
        break;
    case Left:
        moveleft();
        break;
    case Right:
        moveright();
        break;
    }

    /* Test if hitting pacman */
    if (collidesWithItem(game->pacman, Qt::IntersectsItemShape)){
        if (status == Normal && game->stat != Game::Safe)
            game->pacman_death_handler();
        else if (status == Panic) {
            setPixmap(QPixmap(":/rsc2/run.png"));
            game->score += score;
            status = Running;
            release_time = 200;
            is_released = false;
            game->ghost_timer[color]->setInterval(RUNNING_INTERVAL);
        }
    }
}

void Ghost::bfs(int s_i, int s_j){
    if (game->map[s_i][s_j]->type == Wall) return;

    QQueue<QPair<int,int> > q;
    q.push_back(qMakePair(s_i, s_j));


    for (int i = 0; i < map_height; ++i)
        for (int j = 0; j < map_width; ++j)
            MoveTable[s_i][s_j][i][j] = Stop;
    MoveTable[s_i][s_j][s_i][s_j] = Up;

    while(!q.empty()){
        int i = q.head().first;
        int j = q.head().second;
        q.pop_front();

        int nxt_i = (i-1 + map_height)%map_height;
        int nxt_j = j;

        if (game->map[nxt_i][nxt_j]->type != Wall && MoveTable[s_i][s_j][nxt_i][nxt_j] == Stop){

            if (i == s_i && j == s_j) MoveTable[s_i][s_j][nxt_i][nxt_j] = Up;
            else MoveTable[s_i][s_j][nxt_i][nxt_j] = MoveTable[s_i][s_j][i][j];

            q.push_back(qMakePair(nxt_i, nxt_j));
        }

        nxt_i = (i+1)%map_height;
        if (game->map[nxt_i][nxt_j]->type != Wall && MoveTable[s_i][s_j][nxt_i][nxt_j] == Stop){

            if (i == s_i && j == s_j) MoveTable[s_i][s_j][nxt_i][nxt_j] = Down;
            else MoveTable[s_i][s_j][nxt_i][nxt_j] = MoveTable[s_i][s_j][i][j];

            q.push_back(qMakePair(nxt_i, nxt_j));
        }

        nxt_i = i;
        nxt_j = (j-1 + map_width)%map_width;
        if (game->map[nxt_i][nxt_j]->type != Wall && MoveTable[s_i][s_j][nxt_i][nxt_j] == Stop){

            if (i == s_i && j == s_j) MoveTable[s_i][s_j][nxt_i][nxt_j] = Left;
            else MoveTable[s_i][s_j][nxt_i][nxt_j] = MoveTable[s_i][s_j][i][j];

            q.push_back(qMakePair(nxt_i, nxt_j));
        }

        nxt_j = (j+1)% map_width;
        if (game->map[nxt_i][nxt_j]->type != Wall && MoveTable[s_i][s_j][nxt_i][nxt_j] == Stop){

            if (i == s_i && j == s_j) MoveTable[s_i][s_j][nxt_i][nxt_j] = Right;
            else MoveTable[s_i][s_j][nxt_i][nxt_j] = MoveTable[s_i][s_j][i][j];

            q.push_back(qMakePair(nxt_i, nxt_j));
        }
    }

}
