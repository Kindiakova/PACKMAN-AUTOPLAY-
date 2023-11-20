#include "game.h"
#include "options.h"
#include <QQueue>
#include <QPair>
#include <queue>
#include <QRandomGenerator>
#define W (GameObject::Width)

Pacman::Pacman(Game *game, int x, int y, int tmp_x, int tmp_y) : GameObject(
    GameObject::Pacman, QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a3.png"),
    x, y, tmp_x, tmp_y)
{
    this->game = game;
    safe_time = 0;
    _x = x;
    _y = y;
    lives = PACMAN_LIFES;
    setZValue(2);
    dir = Stop;
    next_dir = Stop;
    anim_index = 2;
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a1.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a2.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a3.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a4.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a5.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a6.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a5.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a4.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a3.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a2.png"));

    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a1.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b2.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b3.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b4.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b5.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b6.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b5.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b4.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b3.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/b2.png"));

    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a1.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c2.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c3.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c4.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c5.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c6.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c5.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c4.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c3.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/c2.png"));

    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/a1.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d2.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d3.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d4.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d5.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d6.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d5.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d4.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d3.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/pacman/d2.png"));

}



void Pacman::moveup()
{
    anim_index++;
    if (anim_index == anim[Up].size()) {
        anim_index = 0;
    }
    setPixmap(anim[Up][anim_index]);
    if (static_cast<int>(y() - 1) < game->geo_y)
        setY((game->geo_y + (map_height - 1) * W));
    else setY(static_cast<int>(y()) - 1);
}

void Pacman::moveleft()
{
    anim_index++;
    if (anim_index == anim[Left].size()) {
        anim_index = 0;
    }
    setPixmap(anim[Left][anim_index]);
    if (static_cast<int>(x() - 1) < game->geo_x)
        setX((game->geo_x + (map_width- 1) * W));
    else setX(static_cast<int>(x()) - 1);
}

void Pacman::movedown()
{
    anim_index++;
    if (anim_index == anim[Down].size()) {
        anim_index = 0;
    }
    setPixmap(anim[Down][anim_index]);
    if (static_cast<int>(y() + 1) > game->geo_y + (map_height - 1) * W)
        setY(game->geo_y);
    else setY(static_cast<int>(y()) + 1);
}

void Pacman::moveright()
{
    anim_index++;
    if (anim_index == anim[Right].size()) {
        anim_index = 0;
    }
    setPixmap(anim[Right][anim_index]);
    if (static_cast<int>(x()) + 1 > game->geo_x + (map_width - 1) * W)
        setX(game->geo_x);
    else setX(static_cast<int>(x()) + 1);
}


void Pacman::eat_ball(int __y, int __x)
{
    GameObject *obj = game->map[__y][__x];
    switch (obj->get_type()) {
    case Ball:
        game->score += obj->get_score();
        game->ball_num--;
        break;
    case PowerBall:
        game->score += obj->get_score();
        game->ball_num--;
        for (int i = 0; i < game->powerball.size(); i++) {
            if (game->powerball.at(i) == obj) {
                game->powerball.remove(i);
                break;
            }
        }

        for (int i = 0; i < Ghost::GhostNum; i++) {
            if (game->ghost[i]->status != Ghost::Running) {
                game->ghost[i]->status = Ghost::Panic;
                game->ghost[i]->panic_time = PANNIC_TIME;
                game->ghost_timer[i]->setInterval(PANNIC_INTERVAL);
            }
        }
        break;
    default:
        return;
    }

    QPixmap blankpix;
    game->map[_y][_x] = new GameObject(GameObject::Blank, blankpix, _x, _y);
    game->map[__y][__x] = this;
    delete obj;
}


bool Pacman::good(int i, int j)
{
    i = (i + map_height) % map_height;
    j = (j + map_width) % map_width;
    switch (game->map[i][j]->get_type()) {
    case Wall:
    case Gate:
        return false;
    default:
        return true;
    }

}

void Pacman::move()
{
    int pac_x = static_cast<int>(x());
    int pac_y = static_cast<int>(y());
    int __x = (pac_x - game->geo_x) / W;            // x coordinate in map
    int __y = (pac_y - game->geo_y) / W;            // y coordinate in map
    int x_remainder = (pac_x - game->geo_x) % W;    // remainder x pixel to fit a block
    int y_remainder = (pac_y - game->geo_y) % W;    // remainder y pixel to fit a block

    if (x_remainder == 0) {
        if (y_remainder == 0) {
            eat_ball(__y, __x);
            // update pacman's coordinate in map
            _x = __x;
            _y = __y;

            if (game->ball_num == 0) {
                game->stat = Game::Win;
                return;
            }

            autoPlay();
        }

        switch (next_dir) {
        case Stop:
            dir = next_dir;
            break;
        case Up:        // test if it can turn upward
            if (good(_y - 1, _x)) {
                dir = next_dir;
            }
            break;
        case Down:      // test if it can turn downward
            if (good(_y + 1, _x)) {
                dir = next_dir;
            }
            break;
        case Left:      // test if it can turn left
            if (y_remainder == 0 && good(_y, _x - 1)) {
                dir = next_dir;
            }
            break;
        case Right:      // test if it can turn right
            if (y_remainder == 0 && good(_y, _x + 1)) {
                dir = next_dir;
            }
            break;
        }
    } else if (y_remainder == 0) {
        switch (next_dir) {
        case Stop:
            dir = next_dir;
            break;
        case Left:      // test if it can turn left
            if (good(_y, _x - 1)) {
                dir = next_dir;
            }
            break;
        case Right:     // test if it can turn right
            if (good(_y, _x + 1)) {
                dir = next_dir;
            }
            break;
        default:                    // decide when x_remainder = 0
            break;
        }
    }


    switch (dir) {
    case Stop:
        break;
    case Up:
        if (y_remainder == 0 && !good(_y - 1, _x)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            moveup();
        }
        break;
    case Down:
        if (y_remainder == 0 && !good(_y + 1, _x)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            movedown();
        }
        break;
    case Left:
        if (x_remainder == 0 && !good(_y, _x - 1)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            moveleft();
        }
        break;
    case Right:
        if (x_remainder == 0 && !good(_y, _x + 1)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            moveright();
        }
        break;
    }
}

bool Pacman::great(int i, int j){
    if (!good(i, j)) return false;
    //if (game->stat == Game::Safe) return true;

    i = (i + map_height) % map_height;
    j = (j + map_width) % map_width;

    for (int t = 0; t < 4; ++t)
    {
        if (game->ghost[t]->status == Ghost::Panic ||
                game->ghost[t]->status == Ghost::Running) continue;
        int gj = game->ghost[t]->get_x();
        int gi = game->ghost[t]->get_y();
        if (abs(gj - j) < 3 && abs(gi - i) < 3)
            return false;

    }
    return true;
}

void Pacman::bfs(int s_i, int s_j){
    path.clear();
    MoveList.clear();

    QQueue<QPair<int,int> > q;
    q.push_back(qMakePair(s_i, s_j));

    Dir p[map_height][map_width];
    QVector<QVector<int> > dist(map_height, QVector<int>(map_width, -1));


    dist[s_i][s_j] = 0;
    p[s_i][s_j] = Stop;

    QPair<int, int> ball(-1, -1);
    while(!q.empty()){
        int i = q.head().first;
        int j = q.head().second;
        q.pop_front();
        int nxt_i = (i-1 + map_height)%map_height;
        int nxt_j = j;

        if (great(nxt_i, nxt_j) &&  dist[nxt_i][nxt_j] == -1){

            dist[nxt_i][nxt_j] = dist[i][j] + 1;
            p[nxt_i][nxt_j] = Up;
            if(game->map[nxt_i][nxt_j]->get_type() == ObjectType::Ball ||
                    game->map[nxt_i][nxt_j]->get_type() == ObjectType::PowerBall){
                ball = qMakePair(nxt_i, nxt_j);
                break;
            }

            q.push_back(qMakePair(nxt_i, nxt_j));
        }

        nxt_i = (i+1)%map_height;
        if (great(nxt_i, nxt_j) &&  dist[nxt_i][nxt_j] == -1){
            dist[nxt_i][nxt_j] = dist[i][j] + 1;
            p[nxt_i][nxt_j] = Down;
            if(game->map[nxt_i][nxt_j]->get_type() == ObjectType::Ball ||
                    game->map[nxt_i][nxt_j]->get_type() == ObjectType::PowerBall){
                ball = qMakePair(nxt_i, nxt_j);
                break;
            }

            q.push_back(qMakePair(nxt_i, nxt_j));
        }

        nxt_i = i;
        nxt_j = (j-1 + map_width)%map_width;
        if (great(nxt_i, nxt_j) &&  dist[nxt_i][nxt_j] == -1){
            dist[nxt_i][nxt_j] = dist[i][j] + 1;
            p[nxt_i][nxt_j] = Left;
            if(game->map[nxt_i][nxt_j]->get_type() == ObjectType::Ball ||
                    game->map[nxt_i][nxt_j]->get_type() == ObjectType::PowerBall){

                ball = qMakePair(nxt_i, nxt_j);
                break;
            }

            q.push_back(qMakePair(nxt_i, nxt_j));
        }

        nxt_j = (j+1)% map_width;
        if (great(nxt_i, nxt_j) &&  dist[nxt_i][nxt_j] == -1){
            dist[nxt_i][nxt_j] = dist[i][j] + 1;
            p[nxt_i][nxt_j] = Right;
            if(game->map[nxt_i][nxt_j]->get_type() == ObjectType::Ball ||
                    game->map[nxt_i][nxt_j]->get_type() == ObjectType::PowerBall){
                ball = qMakePair(nxt_i, nxt_j);
                break;
            }

            q.push_back(qMakePair(nxt_i, nxt_j));
        }
    }

    if (ball != qMakePair(-1, -1)){
        Dir tmp_dir = p[ball.first][ball.second];
        while(tmp_dir != Stop){
            MoveList.push_back(tmp_dir);
            path.push_back(ball);
            switch (tmp_dir) {
            case Up:
                ball.first = (ball.first + 1)%map_height;
                break;
            case Down:
                ball.first = (ball.first - 1 + map_height)%map_height;
                break;
            case Left:
                ball.second = (ball.second + 1)%map_width;
                break;
            case Right:
                ball.second = (ball.second - 1 + map_width)%map_width;
                break;
            }
            tmp_dir = p[ball.first][ball.second];
        }
    }
    else MoveList.push_back(get_random_dir());


}

GameObject::Dir Pacman::get_random_dir()
{
    int tries = 10;
    while(!great(escape_point.first, escape_point.second) && tries){
        tries--;
        escape_point.first = (QRandomGenerator::global()->generate() % map_height);
        escape_point.second = (QRandomGenerator::global()->generate() % map_width);
    }
    if (great(escape_point.first, escape_point.second))
        return game->ghost[0]->MoveTable[_y][_x][escape_point.first][escape_point.second];

    QVector<Dir> oklist;
    if (great(_y, _x + 1)) oklist.push_back(Right);
    if (great(_y, _x - 1)) oklist.push_back(Left);
    if (great(_y + 1, _x)) oklist.push_back(Down);
    if (great(_y - 1, _x)) oklist.push_back(Up);

    if (oklist.size() == 0) {
        if (good(_y, _x + 1)) oklist.push_back(Right);
        if (good(_y, _x - 1)) oklist.push_back(Left);
        if (good(_y + 1, _x)) oklist.push_back(Down);
        if (good(_y - 1, _x)) oklist.push_back(Up);
    }

    return oklist.at(QRandomGenerator::global()->generate() % oklist.size());
}

bool Pacman::checkPath(){
    if (path.empty()) return false;
    for (QPair<int, int> p : path){
        if (!great(p.first, p.second)) return false;
    }
    return true;
}

void Pacman::autoPlay(){
    if (!checkPath()) bfs(_y, _x);
    set_next_dir(MoveList.back());

    MoveList.pop_back();
    if (path.size() > 0) path.pop_back();


}
