#include "ghost.h"
#include "pacman.h"
#include "game.h"
#include "options.h"

RedGhost::RedGhost(Game * game, int x, int y, int tmp_x, int tmp_y):
    Ghost(game, x, y, tmp_x, tmp_y)
{
    color = Ghost::Red;
    release_time = GHOST_RELEASE_TIME[Ghost::Red];
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/redright1.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/redright2.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/redup1.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/redup2.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/redleft1.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/redleft2.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/reddown1.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/reddown2.png"));
    setPixmap(anim[Right][0]);
    is_released = true;
}

PinkGhost::PinkGhost(Game * game, int x, int y, int tmp_x, int tmp_y):
    Ghost(game, x, y, tmp_x, tmp_y)
{
    color = Ghost::Pink;
    release_time = GHOST_RELEASE_TIME[Ghost::Pink];
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkright1.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN//game_objects/ghosts/pinkright2.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkup1.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkup2.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkleft1.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkleft2.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkdown1.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/pinkdown2.png"));
    setPixmap(anim[Right][0]);    
    is_released = false;
}

BlueGhost::BlueGhost(Game * game, int x, int y, int tmp_x, int tmp_y):
    Ghost(game, x, y, tmp_x, tmp_y)
{
    color = Ghost::Blue;
    release_time = GHOST_RELEASE_TIME[Ghost::Blue];
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/blueright1.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/blueright2.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/blueup1.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/blueup2.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/blueleft1.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/blueleft2.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/bluedown1.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/bluedown2.png"));
    setPixmap(anim[Right][0]);    
    is_released = false;
}

YellowGhost::YellowGhost(Game * game, int x, int y, int tmp_x, int tmp_y):
    Ghost(game, x, y, tmp_x, tmp_y)
{
    color = Ghost::Yellow;
    release_time = GHOST_RELEASE_TIME[Ghost::Yellow];
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowright1.png"));
    anim[Right].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowright2.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowup1.png"));
    anim[Up].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowup2.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowleft1.png"));
    anim[Left].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowleft2.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowdown1.png"));
    anim[Down].push_back(QPixmap("C:/Users/Diashka/Documents/PACMEN/game_objects/ghosts/yellowdown2.png"));
    setPixmap(anim[Right][0]);    
    is_released = false;

}

//Shadow -- chaser
QPair<int, int> RedGhost::goal_position() {
    return QPair<int, int>(game->pacman->get_x(), game->pacman->get_y());
}



//Speedy -- ambusher
QPair<int, int> PinkGhost::goal_position() {
    auto *pacman = game->pacman;
    int x = pacman->get_x();
    int y = pacman->get_y();
    switch(pacman->get_dir()) {
    case GameObject::Up:
        if (good(y-4, x)) y -= 4;
        if (good(y-3, x)) y -= 3;
        if (good(y-2, x)) y -= 2;
        if (good(y-1, x)) y -= 1;
        break;
    case GameObject::Down:
        if (good(y+4, x)) y += 4;
        if (good(y+3, x)) y += 3;
        if (good(y+2, x)) y += 2;
        if (good(y+1, x)) y += 1;
        break;
    case GameObject::Left:
        if (good(y, x-4)) x -= 4;
        if (good(y, x-3)) x -= 3;
        if (good(y, x-2)) x -= 2;
        if (good(y, x-1)) x -= 1;
        break;
    case GameObject::Right:
        if (good(y, x+4)) x += 4;
        if (good(y, x+3)) x += 3;
        if (good(y, x+2)) x += 2;
        if (good(y, x+1)) x += 1;
        break;
    default:
        break;
    }
    return QPair<int, int>(x, y);
}

//Bashful -- Fickle
QPair<int, int> BlueGhost::goal_position() {
    auto *pacman = game->pacman;
    Ghost *red_ghost = game->ghost[Ghost::Red];
    int dist_x = (pacman->get_x() - red_ghost->get_x());
    int dist_y = (pacman->get_y() - red_ghost->get_y());

    if (dist_x * dist_x + dist_y * dist_y < 64) {
        return QPair<int, int>(-1, -1);
    }

    return QPair<int, int>(pacman->get_x(), pacman->get_y());

}

//Pokey -- feigning ignorance
QPair<int, int> YellowGhost::goal_position() {
    auto *pacman = game->pacman;
    int dist_x = pacman->get_x() - get_x();
    int dist_y = pacman->get_y() - get_y();
    if (dist_x * dist_x + dist_y * dist_y < 64) {
        return QPair<int, int>(-1, -1);
    }
    return QPair<int, int>(pacman->get_x(), pacman->get_y());
}


