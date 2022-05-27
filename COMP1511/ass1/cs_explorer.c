// CS Explorer
// cs_explorer.c
//
// This program was written by Liren Ding (z5369144)
// on 2022-3-11
//
// Version 1.0.0 (2022-03-08): Assignment Released.
//
// cs explorer-------ass 1

#include <stdio.h>

// Additional libraries here


// Provided constants 
#define SIZE 8
#define PLAYER_STARTING_ROW (SIZE - 1)
#define PLAYER_STARTING_COL 0
#define EMPTY_POINTS 0
#define EMPTY_TYPE 'E'
#define PLAYER_TYPE 'P'
#define MONSTER_TYPE 'M'
#define HEALING_TYPE 'H'
#define BOULDER_TYPE 'B'

// Your constants here

// Provided struct
struct location {
    char occupier;
    int points;
};

// Your structs here
struct player {
    int x;
    int y;
    int health;
    int count_of_monster;
    char mv_direction;
};

struct monsters {
    int x[SIZE * SIZE];
    int y[SIZE * SIZE];
    int lived_num;
    int total_num;
};



// Provided functions use for game setup
// You do not need to use these functions yourself.
void init_map(struct location map[SIZE][SIZE]);
void place_player_on_starting_location(struct location map[SIZE][SIZE]);

// You will need to use these functions for stage 1.
void print_cheat_map(struct location map[SIZE][SIZE]);
void print_game_play_map(struct location map[SIZE][SIZE]);



// Your functions prototypes here
void init_player(struct player* player);
void init_monster(struct monsters* monster);
void init_game_piece(struct location map[SIZE][SIZE], struct player* player, struct monsters* monster);

void player_move(struct location map[SIZE][SIZE], struct player* player, struct monsters* monster);
void player_crash_obj(struct location map[SIZE][SIZE], struct player* player, struct monsters* monster);
void count_in_square(struct location map[SIZE][SIZE]);
int won_or_lost(struct location map[SIZE][SIZE], struct player* player, struct monsters* monster);
int boulder_surrouding(struct player* player, struct location map[SIZE][SIZE]);
void falling_boulder(struct location map[SIZE][SIZE], struct player* player);
int clamping_value(int value);
void count_in_rectangle(struct location map[SIZE][SIZE]);
int max(int val_1, int val_2);
int min(int val_1, int val_2);
int self_defined_count(int r_min, int r_max, int c_min, int c_max, char type, struct location map[SIZE][SIZE]);
void recommended_move(struct location map[SIZE][SIZE], struct player* player);
int count_danger_quotient(int r_min, int r_max, int c_min, int c_max, struct location map[SIZE][SIZE], int size);
void monster_move(struct location map[SIZE][SIZE], struct player* player, struct monsters* monster);
int distance(int val_1, int val_2);
void monster_left(int i, struct monsters* monster, struct location map[SIZE][SIZE], struct player* player);
void monster_right(int i, struct monsters* monster, struct location map[SIZE][SIZE], struct player* player);
void monster_down(int i, struct monsters* monster, struct location map[SIZE][SIZE], struct player* player);
void monster_up(int i, struct monsters* monster, struct location map[SIZE][SIZE], struct player* player);
int cal_distance(int val_1, int val_2);
void monster_decrease(int i, struct monsters* monster);

int main(void) {
    // variable defined
    struct location map[SIZE][SIZE];
    struct player player;
    struct monsters monster;
    char command;
    
    // Welcome Speech
    printf("Welcome Explorer!!\n");

    // initial three struct
    init_map(map);
    // Passing in actual argument makes it easier to change the player's position
    init_player(&player);
    init_monster(&monster);
    // initial game piece
    // Confirm the number of pieces and the type of pieces
    init_game_piece(map, &player, &monster);

    // After the game pieces have been added to the map print out the map.
    print_game_play_map(map);
    printf("\nEXPLORE!\n");
    printf("Enter command: ");
    // sustained input
    // scanf(" %c") --- the space before %c is to read off space
    while (scanf(" %c", &command) != EOF) {
        // printf("%c %d\n", command, command);
        // pirnt cheat map and the normal map
        if (command == 'c') {
            // Packaging function
            print_cheat_map(map);
            // read off line break;
            getchar();
            // printf("%c %d\n", command, command);

        }
        else if (command == 'q') {
            // exit the game
            //getchar();
            printf("Exiting Program!\n");
            return 0;
        }
        else if (command == 'm') {
            // Packaging function
            player_move(map, &player, &monster);
        }
        else if (command == 'h') {
            // print player health
            printf("Your player is at (%d, %d) with a health of %d.\n",
                player.y, player.x, player.health);
            getchar();
        }
        else if (command == 's') {
            // count the sum of a kind of tpye points in a square
            count_in_square(map);
        }
        else if (command == 'b') {
            // falling boulder
            falling_boulder(map, &player);
        }
        else if (command == 'r') {
            // count points in a rectangle
            count_in_rectangle(map);
        }
        else if (command == 'n') {
            recommended_move(map, &player);
        }
        else if (command == 'a') {
            monster_move(map, &player, &monster);
        }
        player_crash_obj(map, &player, &monster);
        print_game_play_map(map);
        // if win or lose
        if (won_or_lost(map, &player, &monster) == 1) {
            return 0;
        }
        // read off line break
        //getchar();
        printf("Enter command: ");
    }

    return 0;
}




////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------
// --------------------   initial functions    ------------------
// --------------------------------------------------------------

// initial the player
void init_player(struct player *player) {
    player->x = PLAYER_STARTING_COL;
    player->y = PLAYER_STARTING_ROW;
    player->health = 10;
    player->mv_direction = 0;
}

// initial the monster
void init_monster(struct monsters *monster) {
    monster->total_num = 0;
    monster->lived_num = 0;
    for (int i = 0; i < SIZE * SIZE; i++) {
        monster->x[i] = -1;
        monster->y[i] = -1;
    }
}

// input how many number piece
// and distinguish each coordinates and type
void init_game_piece(struct location map[SIZE][SIZE]
, struct player *player, struct monsters *monster) {
    int number_piece;
    int obj_type;
    int point_y, point_x;

    printf("How many game pieces are on the map?\n");
    // input the total number of game piece
    // consider case input is ctrl+d
    if (scanf("%d", &number_piece) == EOF) {
        return;
    }

    printf("Enter the details of game pieces:\n");
    for (int i = 0; i < number_piece; i++) {
        // input the tpye of game piece points and its coordinates
        if (scanf("%d %d %d", &obj_type, &point_y, &point_x) == EOF) {
            return;
        }

        // distinguish if the point is on the map(0~7) and
        // if the input coordinates is on player's position
        if (point_y >= 0 && point_y < 8 && point_x >= 0
            && point_x < 8 && (point_y != 7 || point_x != 0)) {
            // distinguish the game points is valid or not
            // convert the points into the type of game piece
            // import piece tpye into original structure called map
            if (obj_type > 0 && obj_type <= 9) {
                map[point_y][point_x].occupier = HEALING_TYPE;
            }
            else if (obj_type < 0 && obj_type >= -9) {
                map[point_y][point_x].occupier = MONSTER_TYPE;
                // record the M coordinates into struct monsters
                monster->x[monster->lived_num] = point_x;
                monster->y[monster->lived_num] = point_y;
                monster->lived_num++;
                monster->total_num++;
            }
            else if (obj_type == 0) {
                map[point_y][point_x].occupier = BOULDER_TYPE;
            }
            // import points into original structure called map
            map[point_y][point_x].points = obj_type;
        }
    }
}

// --------------------------------------------------------------
// -----------------------   Command 'm'   ----------------------
// --------------------------------------------------------------

// Achieve the player up and down left and right movement function

// pre input is m
// input has to be u, d, r, l
void player_move(struct location map[SIZE][SIZE]
, struct player *player, struct monsters *monster) {
    char direction;
    scanf(" %c", &direction);
    //read off line break
    getchar();
    if (direction == 'u' && player->y - 1 >= 0
        && map[player->y - 1][player->x].occupier != BOULDER_TYPE) {
        player->mv_direction = 'u';
        map[player->y][player->x].occupier = EMPTY_TYPE;
        // should auto - decreasing operators in the left instead of player_y--
        // we need the already decreased number 
        map[player->y - 1][player->x].occupier = PLAYER_TYPE;
        player->y--;
    }
    else if (direction == 'd' && player->y + 1 < SIZE
        && map[player->y + 1][player->x].occupier != BOULDER_TYPE) {
        player->mv_direction = 'd';
        map[player->y][player->x].occupier = EMPTY_TYPE;
        map[player->y + 1][player->x].occupier = PLAYER_TYPE;
        player->y++;
    }
    else if (direction == 'l' && player->x - 1 >= 0
        && map[player->y][player->x - 1].occupier != BOULDER_TYPE) {
        player->mv_direction = 'l';
        map[player->y][player->x].occupier = EMPTY_TYPE;
        map[player->y][player->x - 1].occupier = PLAYER_TYPE;
        player->x--;
    }
    else if (direction == 'r' && player->x + 1 < SIZE
        && map[player->y][player->x + 1].occupier != BOULDER_TYPE) {
        player->mv_direction = 'r';

        map[player->y][player->x].occupier = EMPTY_TYPE;
        map[player->y][player->x + 1].occupier = PLAYER_TYPE;
        player->x++;
    }
}



// --------------------------------------------------------------
// -----------------------   Command 's'   ----------------------
// --------------------------------------------------------------

// count the sum of a kind of tpye points in a square
// find the start col , row and end col , row and type
// use self_defined count

// pre input is s
// input is row, col, size, type 
void count_in_square(struct location map[SIZE][SIZE]) {
    int row;
    int col;
    int size;
    char type;
    int col_max;
    int row_max;
    // seperate written is because of the special case 
    // like too many space between r 1 1 100 and M
    scanf("%d %d %d", &row, &col, &size);
    scanf(" %c", &type);
    getchar();
    //printf("%c %d", type, type);
    row = clamping_value(row);
    col = clamping_value(col);
    row_max = clamping_value(row + size);
    col_max = clamping_value(col + size);
    int sum = self_defined_count(row, row_max - 1, col, col_max - 1, type, map);
    if (type == MONSTER_TYPE) {
        printf("Monsters in this section could apply %d health points.\n", sum);
    }
    else if (type == HEALING_TYPE) {
        printf("Healing Potions in this section could apply %d health points.\n", sum);
    }
}

// --------------------------------------------------------------
// ---------------   distinguish win or lose   ------------------
// --------------------------------------------------------------

// win ----> no monster
// lose ----> health == 0 or player can't move
int won_or_lost(struct location map[SIZE][SIZE]
, struct player *player, struct monsters *monster) {
    // lose
    int count = boulder_surrouding(player, map);
    if (count == 0 || player->health <= 0) {
        printf("GAME LOST!\n");
        return 1;
        // win
    }
    else if (monster->lived_num == 0) {
        printf("GAME WON!\n");
        return 1;
    }
    else {
        // game continue
        return 2;
    }
}

// Determine if the player can move to the four squares around the player
// array out of index
// if (((map[player->y][player->x + 1].occupier == 'B' || player->x + 1 >= SIZE) 
// && (map[player->y][player->x - 1].occupier == 'B' || player->x - 1 < 0)
// && (map[player->y + 1][player->x].occupier == 'B' || player->y + 1 >= SIZE)
// && (map[player->y - 1][player->x].occupier == 'B' || player->y - 1 < 0))
int boulder_surrouding(struct player *player, struct location map[SIZE][SIZE]) {
    int count = 4;
    int x = player->x;
    int y = player->y;
    if (x + 1 >= SIZE) {
        count--;
    }
    else if (map[y][x + 1].occupier == BOULDER_TYPE) {
        count--;
    }

    if (x - 1 < 0) {
        count--;
    }
    else if (map[y][x - 1].occupier == BOULDER_TYPE) {
        count--;
    }

    if (y + 1 >= SIZE) {
        count--;
    }
    else if (map[y + 1][x].occupier == BOULDER_TYPE) {
        count--;
    }

    if (y - 1 < 0) {
        count--;
    }
    else if (map[y - 1][x].occupier == BOULDER_TYPE) {
        count--;
    }
    return count;
}

// --------------------------------------------------------------
// -----------------------   Command 'b'   ----------------------
// --------------------------------------------------------------
// input the coordinates and prodece a boulder
// pre input is b
// input is row and col
void falling_boulder(struct location map[SIZE][SIZE], struct player *player) {
    int row;
    int col;
    scanf("%d %d", &row, &col);
    row = clamping_value(row);
    col = clamping_value(col);
    // printf("%d %d\n", row, col);

    map[row][col].points = 0;
    if (row == player->y && col == player->x) {
        player->health = 0;
    }
    else {
        map[row][col].occupier = BOULDER_TYPE;
    }
}


// --------------------------------------------------------------
// -----------------------   Command 'r'   ----------------------
// --------------------------------------------------------------

// find the start col , row and end col , row and type
// use self_defined count
void count_in_rectangle(struct location map[SIZE][SIZE]) {
    int start_r, end_r;
    int start_c, end_c;
    char type;
    int row_min, row_max;
    int col_min, col_max;
    // seperate written is because of the special case 
    // like too many space between r 1 1 100 100 and M
    scanf("%d %d %d %d", &start_r, &start_c, &end_r, &end_c);
    scanf(" %c", &type);
    getchar();
    // printf("%d %d %d %d %c\n", start_r, start_c, end_r, end_c, type);
    // clamping
    start_r = clamping_value(start_r);
    start_c = clamping_value(start_c);
    end_r = clamping_value(end_r);
    end_c = clamping_value(end_c);
    // min and max
    row_min = min(start_r, end_r);
    row_max = max(start_r, end_r);
    col_min = min(start_c, end_c);
    col_max = max(start_c, end_c);
    int sum = self_defined_count(row_min, row_max, col_min, col_max, type, map);
    if (type == MONSTER_TYPE) {
        printf("Monsters in this section could apply %d health points.\n", sum);
    }
    else if (type == HEALING_TYPE) {
        printf("Healing Potions in this section could apply %d health points.\n", sum);
    }
}



// --------------------------------------------------------------
// -----------------------   Command 'n'   ----------------------
// --------------------------------------------------------------
// next step hint
// pre input is n
// input is size
void recommended_move(struct location map[SIZE][SIZE], struct player *player) {
    int size;
    int danger_quotient[4];
    int min_danger;
    scanf("%d", &size);
    // left up
    danger_quotient[0] = count_danger_quotient(player->y - size, player->y - 1
    , player->x - size, player->x - 1, map, size);
    // left down
    danger_quotient[1] = count_danger_quotient(player->y + size, player->y + 1
    , player->x - size, player->x - 1, map, size);
    // right up
    danger_quotient[2] = count_danger_quotient(player->y - size, player->y - 1
    , player->x + size, player->x + 1, map, size);
    // right down
    danger_quotient[3] = count_danger_quotient(player->y + size, player->y + 1
    , player->x + size, player->x + 1, map, size);
    // compare each one and find the min one
    min_danger = danger_quotient[0];
    for (int i = 1; i < 4; i++) {
        min_danger = min(min_danger, danger_quotient[i]);
    }
    // left up > left down > right up > right down
    if (min_danger == danger_quotient[0]) {
        printf("The recommended move is: Left Up\n");
    }
    else if (min_danger == danger_quotient[1]) {
        printf("The recommended move is: Left Down\n");
    }
    else if (min_danger == danger_quotient[2]) {
        printf("The recommended move is: Right Up\n");
    }
    else if (min_danger == danger_quotient[3]) {
        printf("The recommended move is: Right Down\n");
    }
}


// count the danger quotient
// use the self_defined_count to calculate monster, healing and boulder
// I use the return value type (int) instead of (double) is because
// double cant be compared directly like if (a == b), if (a > b), if (a < b)
// double should be compared like if (abs(a - b) < EPS) , EPS is an accuracy
// const double EPS = 1e-6
// using int can distinguish the quotient because of priority 
int count_danger_quotient(int r_min, int r_max, int c_min, int c_max
, struct location map[SIZE][SIZE], int size) {
    int monster;
    int healing;
    int boulder;
    if (r_max < 0 || r_max >= SIZE) {
        return SIZE * SIZE;
    }
    if (c_max < 0 || c_max >= SIZE) {
        return SIZE * SIZE;
    }
    r_min = clamping_value(r_min);
    c_min = clamping_value(c_min);
    monster = -1 * self_defined_count(r_min, r_max, c_min, c_max, MONSTER_TYPE, map);
    healing = self_defined_count(r_min, r_max, c_min, c_max, HEALING_TYPE, map);
    boulder = self_defined_count(r_min, r_max, c_min, c_max, BOULDER_TYPE, map);
    return (monster - healing) / (size * size - boulder);
}


// --------------------------------------------------------------
// -----------------------   Command 'a'   ----------------------
// --------------------------------------------------------------
// monster move function
void monster_move(struct location map[SIZE][SIZE], struct player *player
, struct monsters *monster) {
    int y_distance;
    int x_distance;
    int m_y;
    int m_x;
    // get each monster coordinates and distinguish if they need to 
    // move left right or up down
    for (int i = 0; i < monster->total_num; i++) {
        m_y = monster->y[i];
        m_x = monster->x[i];
        // consider the case that the monster is on the player coordinates
        if (monster->y[i] <= -1 || monster->x[i] <= -1) {
            continue;
        }

        y_distance = cal_distance(m_y, player->y);
        x_distance = cal_distance(m_x, player->x);

        // 3 vertical condition
        // 
        if (y_distance > x_distance || ((player->mv_direction == 'u'
            || player->mv_direction == 'd' || player->mv_direction == 0
            || (m_x + 1 >= SIZE && map[m_y][m_x - 1].occupier == BOULDER_TYPE)
            || (m_x - 1 < 0 && map[m_y][m_x + 1].occupier == BOULDER_TYPE))
            && y_distance == x_distance)) {
            // vertical
            // up or down

            if (monster->y[i] > player->y) {
                // actual argumenets
                monster_up(i, monster, map, player);

            } else {
                monster_down(i, monster, map, player);
            }
            // horizontal
        } else {
            // left or right
            if (monster->x[i] > player->x) {
                monster_left(i, monster, map, player);
            } else {
                monster_right(i, monster, map, player);
            }
        }
    }
}




// calculate the distance between two points on the same line
int cal_distance(int val_1, int val_2) {
    int min_val;
    int max_val;
    min_val = min(val_1, val_2);
    max_val = max(val_1, val_2);
    return max_val - min_val;
}

// let monster move up
void monster_up(int i, struct monsters *monster, struct location map[SIZE][SIZE]
, struct player *player) {
    int y = monster->y[i];
    int x = monster->x[i];
    // case : on the player
    if (map[y - 1][x].occupier == PLAYER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {
        map[y][x].occupier = EMPTY_TYPE;
        player->health += map[y][x].points;
        map[y][x].points = 0;
        monster->lived_num--;
    }
    else if (map[y - 1][x].occupier != BOULDER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {
        // consider the case combine two monster to one
        if (map[y - 1][x].occupier == MONSTER_TYPE) {
            monster_decrease(i, monster);
        }
        map[y][x].occupier = EMPTY_TYPE;
        // case : on the healthy point or monster point
        map[y - 1][x].points += map[y][x].points;
        map[y][x].points = 0;
        // Recalculated at the change point type
        if (map[y - 1][x].points < 0) {
            map[y - 1][x].occupier = MONSTER_TYPE;
        }
        else if (map[y - 1][x].points == 0) {
            map[y - 1][x].occupier = BOULDER_TYPE;
            monster_decrease(i, monster);
        }
        else {
            map[y - 1][x].occupier = HEALING_TYPE;
            monster_decrease(i, monster);
        }
    }
    if (map[y - 1][x].occupier != BOULDER_TYPE) {
        clamping_value(--monster->y[i]);
    }
}
// let monster move down
void monster_down(int i, struct monsters *monster, struct location map[SIZE][SIZE]
, struct player *player) {
    int y = monster->y[i];
    int x = monster->x[i];
    if (map[y + 1][x].occupier == PLAYER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {

        map[y][x].occupier = EMPTY_TYPE;
        player->health += map[y][x].points;
        map[y][x].points = 0;
        monster_decrease(i, monster);
    }
    else if (map[y + 1][x].occupier != BOULDER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {

        if (map[y + 1][x].occupier == MONSTER_TYPE) {
            monster_decrease(i, monster);
        }
        map[y][x].occupier = EMPTY_TYPE;
        map[y + 1][x].points += map[y][x].points;
        map[y][x].points = 0;
        // Recalculated at the change point type
        if (map[y + 1][x].points < 0) {
            map[y + 1][x].occupier = MONSTER_TYPE;
        }
        else if (map[y + 1][x].points == 0) {
            map[y + 1][x].occupier = BOULDER_TYPE;
            monster_decrease(i, monster);
        }
        else {
            map[y + 1][x].occupier = HEALING_TYPE;
            monster_decrease(i, monster);
        }
    }
    if (map[y + 1][x].occupier != BOULDER_TYPE) {
        clamping_value(++monster->y[i]);
    }
}
// let monster move right
void monster_right(int i, struct monsters *monster, struct location map[SIZE][SIZE]
, struct player *player) {
    int y = monster->y[i];
    int x = monster->x[i];
    if (map[y][x + 1].occupier == PLAYER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {
        map[y][x].occupier = EMPTY_TYPE;
        player->health += map[y][x].points;
        map[y][x].points = 0;
        monster_decrease(i, monster);
    }
    else if (map[y][x + 1].occupier != BOULDER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {
        if (map[y][x + 1].occupier == MONSTER_TYPE) {
            monster_decrease(i, monster);
        }
        map[y][x].occupier = EMPTY_TYPE;
        map[y][x + 1].points += map[y][x].points;
        map[y][x].points = 0;
        // Recalculated at the change point type
        if (map[y][x + 1].points < 0) {
            map[y][x + 1].occupier = MONSTER_TYPE;
        }
        else if (map[y][x + 1].points == 0) {
            map[y][x + 1].occupier = BOULDER_TYPE;
            monster_decrease(i, monster);
        }
        else {
            map[y][x + 1].occupier = HEALING_TYPE;
            monster_decrease(i, monster);
        }
    }
    if (map[y][x + 1].occupier != BOULDER_TYPE) {
        clamping_value(++monster->x[i]);
    }
}
// let monster move left
void monster_left(int i, struct monsters *monster, struct location map[SIZE][SIZE]
, struct player *player) {
    int y = monster->y[i];
    int x = monster->x[i];
    if (map[y][x - 1].occupier == PLAYER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {
        map[y][x].occupier = EMPTY_TYPE;
        player->health += map[y][x].points;
        map[y][x].points = 0;
        monster_decrease(i, monster);
    }
    else if (map[y][x - 1].occupier != BOULDER_TYPE 
    && map[y][x].occupier == MONSTER_TYPE) {
        if (map[y][x - 1].occupier == MONSTER_TYPE) {
            monster_decrease(i, monster);
        }
        map[y][x].occupier = EMPTY_TYPE;
        map[y][x - 1].points += map[y][x].points;
        map[y][x].points = 0;
        // Recalculated at the change point type
        if (map[y][x - 1].points < 0) {
            map[y][x - 1].occupier = MONSTER_TYPE;
        }
        else if (map[y][x - 1].points == 0) {
            map[y][x - 1].occupier = BOULDER_TYPE;
            monster_decrease(i, monster);
        }
        else {
            map[y][x - 1].occupier = HEALING_TYPE;
            monster_decrease(i, monster);
        }
    }
    if (map[y][x - 1].occupier != BOULDER_TYPE) {
        clamping_value(--monster->x[i]);
    }
}



// --------------------------------------------------------------
// ---------------   other important functions   ----------------
// --------------------------------------------------------------


// Reduce the number of monsters in struct monsters  
void monster_decrease(int i, struct monsters *monster) {
    monster->lived_num--;
    monster->x[i] = -1;
    monster->y[i] = -1;
}

// Achieve the player collision object function
// Determine if the player should lose health or add health
// Determine if the monster has been destroyed
void player_crash_obj(struct location map[SIZE][SIZE]
, struct player *player, struct monsters *monster) {
    player->health += map[player->y][player->x].points;
    map[player->y][player->x].points = 0;
    for (int i = 0; i < monster->total_num; i++) {
        if (monster->y[i] == player->y && monster->x[i] == player->x) {
            monster_decrease(i, monster);
        }
    }
}

// Clamping
// Clamping is changing a number so that it fits within the bounds of a range.
int clamping_value(int value) {
    if (value >= SIZE) {
        value = SIZE - 1;
    }
    else if (value < 0) {
        value = 0;
    }
    return value;
}


// for the use of same part in square and rectangle count 
// and recommended move and danger quotient
// can calculates the area of a custom rectangle
int self_defined_count(int r_min, int r_max, int c_min, int c_max
, char type, struct location map[SIZE][SIZE]) {
    int sum = 0;
    int begin_c = c_min;
    for (; r_min <= r_max; r_min++) {
        for (c_min = begin_c; c_min <= c_max; c_min++) {
            // extra function for count num of boulders
            // Highest Priority First
            if (type == BOULDER_TYPE && map[r_min][c_min].occupier == BOULDER_TYPE) {
                sum++;
            }
            else if (type == map[r_min][c_min].occupier) {
                sum += map[r_min][c_min].points;
            }
        }
    }
    return sum;
}

// find max value
int max(int val_1, int val_2) {
    if (val_1 > val_2) {
        return val_1;
    } else {
        return val_2;
    }
}

// find min value
int min(int val_1, int val_2) {
    if (val_1 < val_2) {
        return val_1;
    } else {
        return val_2;
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
/////////////////////////// (DO NOT EDIT BELOW HERE) ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided Function
// Initalises all elements on the map to be empty to prevent access errors.
void init_map(struct location map[SIZE][SIZE]) {
    int row = 0;
    while (row < SIZE) {
        int col = 0;
        while (col < SIZE) {
            struct location curr_loc;
            curr_loc.occupier = EMPTY_TYPE;
            curr_loc.points = EMPTY_POINTS;
            map[row][col] = curr_loc;
            col++;
        }
        row++;
    }

    place_player_on_starting_location(map);
}

// Provided Function
// Places the player in the bottom left most location.
void place_player_on_starting_location(struct location map[SIZE][SIZE]) {
    map[PLAYER_STARTING_ROW][PLAYER_STARTING_COL].occupier = PLAYER_TYPE;
}

// Provided Function
// Prints out map with alphabetic values. Monsters are represented with 'M',
// healing potions in 'H', boulders with 'B' and the player with 'P'.
void print_game_play_map(struct location map[SIZE][SIZE]) {
    printf(" -----------------\n");
    int row = 0;
    while (row < SIZE) {
        printf("| ");
        int col = 0;
        while (col < SIZE) {
            if (map[row][col].occupier == EMPTY_TYPE) {
                printf("- ");
            }
            else {
                printf("%c ", map[row][col].occupier);
            }
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(" -----------------\n");
}

// Provided Function
// Prints out map with numerical values. Monsters are represented in red,
// healing potions in blue, boulder in green and the player in yellow.
//
// We use some functionality you have not been taught to make sure that
// colours do not appear during testing.
void print_cheat_map(struct location map[SIZE][SIZE]) {

    printf(" -----------------\n");
    int row = 0;
    while (row < SIZE) {
        printf("| ");
        int col = 0;
        while (col < SIZE) {
            if (map[row][col].occupier == PLAYER_TYPE) {
                // print the player in purple
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
#ifndef NO_COLORS
                printf("\033[1;35m");
#endif
                // ----------------------------------------
                printf("%c ", PLAYER_TYPE);
            }
            else if (map[row][col].occupier == HEALING_TYPE) {
                // print healing potion in green
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
#ifndef NO_COLORS
                printf("\033[1;32m");
#endif
                // ----------------------------------------
                printf("%d ", map[row][col].points);
            }
            else if (map[row][col].occupier == MONSTER_TYPE) {
                // print monsters in red
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
#ifndef NO_COLORS
                printf("\033[1;31m");
#endif
                // ----------------------------------------
                printf("%d ", -map[row][col].points);
            }
            else if (map[row][col].occupier == BOULDER_TYPE) {
                // print boulder in blue
                // ----------------------------------------
                // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
#ifndef NO_COLORS
                printf("\033[1;34m");
#endif
                // ----------------------------------------
                printf("%d ", map[row][col].points);
            }
            else {
                // print empty squares in the default colour
                printf("- ");
            }
            // ----------------------------------------
            // YOU DO NOT NEED TO UNDERSTAND THIS CODE.
            // reset the colour back to default
#ifndef NO_COLORS
            printf("\033[0m");
#endif
            // ----------------------------------------
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(" -----------------\n");
}
