#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

//^^ MapElement
MapElement::MapElement(ElementType in_type) : type(in_type) {}
MapElement::~MapElement() {}
ElementType MapElement::getType() const{
    return type;
}

//^^ Path
Path::Path() : MapElement(PATH) {}

//^^ Wall
Wall::Wall() : MapElement(WALL) {}

//^^ FakeWall
FakeWall::FakeWall() : MapElement(FAKE_WALL) {}

//^^ Map
Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls) : num_rows(num_rows), num_cols(num_cols) {
    map = new int *[num_rows];
    //*Create dynamic array
    for (int i = 0; i < num_cols; i++){
        map[i] = new int [num_cols];
    }
    //*Value input
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            bool isntWall = true;
            for (int count = 0; count < num_walls; count++){
                if (array_walls[count].getRow() == i && array_walls[count].getCol() == j){
                    map[i][j] = 1;
                    isntWall = false;
                    break;;
                }
            }
            for (int count = 0; count < num_fake_walls; count++){
                if (array_fake_walls[count].getRow() == i && array_fake_walls[count].getCol() == j){
                    map[i][j] = 2;
                    isntWall = false;
                    break;;
                }
            }
            if (isntWall)
                map[i][j] = 0;
        }
    }
};

Map::~Map(){
    for (int j = 0; j < num_rows; j++){
        delete [] map[j];
    }
};

//! bool isValid is missing!!!!!!!!!!!!!!!!!!
bool Map::isValid(const Position &pos , MovingObject *mv_obj) const{     //! ????????????????????????????????????????????????????
    if (pos.getRow() >= num_rows || pos.getCol() >= num_cols)
        return false;

    if (mv_obj->getName() == "Watson")  //! 
        return map[pos.getRow()][pos.getCol()] != 2;

    return true;
};

    /// Unofficial
int Map::getNumRows(){
        return num_rows;
}

int Map::getNumCols(){
    return num_cols;
}

//^^ Position
Position::Position(int r = 0, int c = 0) : r(r), c(c) {}

Position::Position(const string &str_pos){    //* Constructor; str_pos = "(r, c)" Ex: (1, 15)
    int *coor = nullptr;
    int counter = 0;    // Determine whether manipulate r or c (0 or 1)
    for (int i = 0; i < str_pos.length(); i++){
        counter == 0? coor =& r : coor =& c;
        switch(str_pos[i]){
            case '0' ... '9':
                *coor = (*coor)*10 + (str_pos[i] - '0');
                break;
            case ',':
                counter = 1;
            default:
                break;
        }
    }
}

int Position::getRow() const{
    return r;
}

int Position::getCol() const{
    return c;
}

void Position::setRow(int r){
    this->r = r;
}

void Position::setCol(int c){
    this->c = c;
}

string Position::str() const{
    return  "(" + to_string(r) + "," + to_string(c) + ")";
}

bool Position::isEqual(int in_r, int in_c) const{
    return (in_r == r && in_c == c);
}

    /// Unofficial
bool Position::isEqual(Position pos) const{
    return (pos.getRow() == r && pos.getCol() == c);
}

//^^ MovingObject
MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name = "") : index(index), pos(pos), map(map), name(name) {}

MovingObject::~MovingObject() {}

Position MovingObject::getCurrentPosition() const{
    return pos;
}

    /// Unofficial
string MovingObject::getName(){
    return name;
}

int MovingObject::getindex(){
    return index;
}

//^^ SherlockCharacter
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) : Character(index, init_pos, map, "Sherlock"), hp(init_hp), exp(init_exp), moving_rule(moving_rule) {}

Position Sherlock::getNextPosition(){
    Position temp(pos.getCol(),pos.getRow());

    //*　Predicting
    switch(moving_rule[0]){
        case 'U':
            temp.setRow(temp.getRow() - 1);
            break;

        case 'D':
            temp.setRow(temp.getRow() + 1);
            break;

        case 'L':
            temp.setCol(temp.getCol() - 1);
            break;

        case 'R':
            temp.setCol(temp.getCol() + 1);
            break;
    }

    //*String modify
    moving_rule += moving_rule[0];
    moving_rule.erase(moving_rule.begin());
    
    if (map->isValid(temp, this)){     // this = sherlock
        return temp;
    }
    
    return npos;
}

void Sherlock::move(){
    if (!getNextPosition().isEqual(-1,-1))
        pos = getNextPosition();
}

string Sherlock::str() const{
    return "Sherlock [index = " + to_string(index) + "; pos = " + pos.str() + "; moving_rule = " + moving_rule + "]";
}

//^^ Watson
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) : Character(index, init_pos, map, "Watson"), hp(init_hp), exp(init_exp), moving_rule(moving_rule) {}

Position Watson::getNextPosition(){
    Position temp(pos.getCol(),pos.getRow());

    //*　Predicting
    switch(moving_rule[0]){
        case 'U':
            temp.setRow(temp.getRow() - 1);
            break;

        case 'D':
            temp.setRow(temp.getRow() + 1);
            break;

        case 'L':
            temp.setCol(temp.getCol() - 1);
            break;

        case 'R':
            temp.setCol(temp.getCol() + 1);
            break;
    }

    //*String modify
    moving_rule += moving_rule[0];
    moving_rule.erase(moving_rule.begin());
    
    if (map->isValid(temp, this)){     // this = sherlock
        return temp;
    }
    
    return npos;
}

void Watson::move(){
    if (!getNextPosition().isEqual(-1,-1))
        pos = getNextPosition();
}

string Watson::str() const{
    return "Watson [index = " + to_string(index) + "; pos = " + pos.str() + "; moving_rule = " + moving_rule + "]";
}

//^^ Criminal
Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson) : Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson) {}

Position Criminal::getNextPosition(){
    float max;
    Position maxPos;
    for (int i = 0; i < map->getNumRows(); i++){
        for (int j = 0; i < map->getNumCols(); j++){
            if (max < (abs(sherlock->getCurrentPosition().getCol() - this->getCurrentPosition().getCol()) + abs(sherlock->getCurrentPosition().getRow() - this->getCurrentPosition().getRow()) + abs(watson->getCurrentPosition().getCol() - this->getCurrentPosition().getCol()) + abs(watson->getCurrentPosition().getRow() - this->getCurrentPosition().getRow()))){
                max = (abs(sherlock->getCurrentPosition().getCol() - this->getCurrentPosition().getCol()) + abs(sherlock->getCurrentPosition().getRow() - this->getCurrentPosition().getRow()) + abs(watson->getCurrentPosition().getCol() - this->getCurrentPosition().getCol()) + abs(watson->getCurrentPosition().getRow() - this->getCurrentPosition().getRow()));
                maxPos = Position(i,j);
            }; //* |x - x| + |y - y| + |x - x| +|y - y|
        }
    }
}

void Criminal::move(){
if (!getNextPosition().isEqual(-1,-1))
    pos = getNextPosition();
}

string Criminal::str() const{
    return "Criminal [index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

//^^ ArrayMovingObject
ArrayMovingObject::ArrayMovingObject(int capacity) : capacity() {}

ArrayMovingObject::~ArrayMovingObject() {}

bool ArrayMovingObject::isFull() const{
    return count == capacity;
}

bool ArrayMovingObject::add(MovingObject *mv_obj){ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (isFull()){
        //TODO
    }

    return false;
}

MovingObject *ArrayMovingObject::get(int index) const{
    //TODO 
}

int ArrayMovingObject::size() const{
    //TODO
}

string ArrayMovingObject::str() const{
    string result;
    result = "Array[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
    for (int i = 0; i < count; i++){
        result += (arr_mv_objs + i)->str();
        if (i != count - 1)
            result += ";";
    }
    result += "]";
    return result;
}

//^^ Configuration
Configuration::Configuration(const string &filepath){
    string str;
    ifstream fin ("sa_tc_02_config");
    while (fin.eof() == false){
        getline(fin, str);
        cout << str << endl;
        size_t equalpos = str.find('=');
        size_t length = str.length();
        string type = str.substr(0, equalpos);

        if (type == "MAP_NUM_ROWS"){
            map_num_rows = stoi(str.substr(equalpos + 1, length));
        }
        if (type == "MAP_NUM_COLS"){
            map_num_cols = stoi(str.substr(equalpos + 1, length));
        }
        if (type == "MAX_NUM_MOVING_OBJECTS"){
            max_num_moving_objects = stoi(str.substr(equalpos + 1, length));
        }
        if (type == "NUM_WALLS"){
            num_walls = stoi(str.substr(equalpos + 1, length));
        }
        if (type == "ARRAY_WALLS"){
            string substr = str.substr(equalpos + 2, num_walls*5 + num_walls - 1);
            arr_walls = new Position[num_walls];
            for (int i = 0; i < num_walls; i++){
                static size_t semicolonpos = -1;
                *(arr_walls + i) = Position(stoi(substr.substr(semicolonpos + 2, 1)), stoi(substr.substr(semicolonpos + 4, 1)));
                semicolonpos = substr.find(';', semicolonpos + 1);
            }
        }
        if (type == "NUM_FAKE_WALLS"){
            num_fake_walls = stoi(str.substr(equalpos + 1, length)); 
        }
        if (type == "ARRAY_FAKE_WALLS"){
            string substr = str.substr(equalpos + 2, num_fake_walls*5 + num_fake_walls - 1);
            arr_fake_walls = new Position[num_fake_walls];
            for (int i = 0; i < num_fake_walls; i++){
                static size_t semicolonpos = -1;
                *(arr_fake_walls + i) = Position(stoi(substr.substr(semicolonpos + 2, 1)), stoi(substr.substr(semicolonpos + 4, 1)));
                semicolonpos = substr.find(';', semicolonpos + 1);
            }
        }
        if (type == "SHERLOCK_MOVING_RULE"){
            sherlock_moving_rule = str.substr(equalpos + 1, length);
        }
        if (type == "SHERLOCK_INIT_POS"){
            sherlock_init_pos = Position(stoi(str.substr(equalpos + 2, 1)), stoi(str.substr(equalpos + 4, 1)));
        }
        if (type == "SHERLOCK_INIT_HP"){
            sherlock_init_hp = stoi(str.substr(equalpos + 1, length));
        }
        if (type == "SHERLOCK_INIT_EXP"){
            sherlock_init_exp = stoi(str.substr(equalpos + 1, length)); 
        }
        if (type == "WATSON_MOVING_RULE"){
            watson_moving_rule = str.substr(equalpos + 1, length);
        }
        if (type == "WATSON_INIT_POS"){
            watson_init_pos = Position(stoi(str.substr(equalpos + 2, 1)), stoi(str.substr(equalpos + 4, 1)));
        }
        if (type == "WATSON_INIT_HP"){
            watson_init_hp = stoi(str.substr(equalpos + 1, length)); 
        }
        if (type == "WATSON_INIT_EXP"){
            watson_init_exp = stoi(str.substr(equalpos + 1, length)); 
        }
        if (type == "CRIMINAL_INIT_POS"){
            criminal_init_pos = Position(stoi(str.substr(equalpos + 2, 1)), stoi(str.substr(equalpos + 4, 1)));
        }
        if (type == "NUM_STEPS"){
            num_steps = stoi(str.substr(equalpos + 1, length)); 
        }
    }
    fin.close();
}

Configuration::~Configuration() {
    //TODo
}

string Configuration::str() const{
    string result;
    result =    "Configuration["
                "\nMAP_NUM_ROWS=" + to_string(map_num_rows) + 
                "\nMAP_NUM_COLS=" + to_string(map_num_cols) +
                "\nMAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) +
                "\nNUM_WALLS=" + to_string(num_walls) +
                "\nARRAY_WALLS="; //[(1,2);(2,3);(3,4)]
                    result += "[";
                    for(int i = 0; i < num_walls; i++){
                        result += (arr_walls + i)->str();
                        i != num_walls - 1? result += ";" : result = result;
                    }
                    result += "]";
    result +=   "\nNUM_FAKE_WALLS=" + to_string(num_fake_walls) +
                "\nARRAY_FAKE_WALLS=";//[(4,5)]
                    result += "[";
                    for(int i = 0; i < num_fake_walls; i++){
                        result += (arr_fake_walls + i)->str();
                        i != num_fake_walls - 1? result += ";" : result = result;
                    }
                    result += "]";
    result +=   "\nSHERLOCK_MOVING_RULE=" + sherlock_moving_rule +
                "\nSHERLOCK_INIT_POS=" + sherlock_init_pos.str() +
                "\nSHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) +
                "\nSHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) +
                "\nWATSON_MOVING_RULE=" + watson_moving_rule +
                "\nWATSON_INIT_POS=" + watson_init_pos.str() +
                "\nWATSON_INIT_HP=" + to_string(watson_init_hp) +
                "\nWATSON_INIT_EXP=" + to_string(watson_init_exp) +
                "\nCRIMINAL_INIT_POS=" + criminal_init_pos.str() +
                "\nNUM_STEPS=" + to_string(num_steps) +
                "\n]";
}

//^^ Robot
Robot::Robot(int index, const Position &init_pos, Map *map, RobotType type) : MovingObject(index, init_pos, map), robot_type(type) {}

//^^ RobotC
RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal) : Robot(index, init_pos, map, RobotType::C), criminal(criminal) {}

Position RobotC::getNextPosition(){
    //TODO
}

void RobotC::move(){
    //TODO
}

string RobotC::str() const{
    //TODO
}

//^^ RobotS
RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock) : Robot(index, init_pos, map, RobotType::S), criminal(criminal), sherlock(sherlock) {}

Position RobotS::getNextPosition(){
    //TODO
}

void RobotS::move(){
    //TODO
}

string RobotS::str() const{
    //TODO
}

//^^ RobotW
RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson) : Robot(index, init_pos, map, RobotType::W), criminal(criminal), watson(watson) {}

Position RobotW::getNextPosition(){
    //TODO
}

void RobotW::move(){
    //TODO
}

string RobotW::str() const{
    //TODO
}

//^^ RobotSW
RobotSW::RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson)  : Robot(index, init_pos, map, RobotType::SW), criminal(criminal), sherlock(sherlock), watson(watson) {};

Position RobotSW::getNextPosition(){
    //TODO
}

void RobotSW::move(){
    //TODO
}

string RobotSW::str() const{
    //TODO
}

//^^ Character
Character::Character(int index, const Position pos, Map*map, string name) : MovingObject(index, pos, map, name) , name(name) {}

//^^ BaseItem
BaseItem::BaseItem(ItemType item_type) : item_type(item_type){}

//^^ MagicBook
MagicBook::MagicBook() : BaseItem(ItemType::MAGIC_BOOK){}

bool MagicBook::canUse(Character *obj, Robot *robot){
    //TODO
}

void MagicBook::use(Character *obj, Robot *robot){
    //TODO
}

//^^ EnergyDrink
EnergyDrink::EnergyDrink() : BaseItem(ItemType::ENERGY_DRINK){}

bool EnergyDrink::canUse(Character *obj, Robot *robot){
    //TODO
}

void EnergyDrink::use(Character *obj, Robot *robot){
    //TODO
}

//^^ FirstAid
FirstAid::FirstAid() : BaseItem(ItemType::FIRST_AID){}

bool FirstAid::canUse(Character *obj, Robot *robot){
    //TODO
}

void FirstAid::use(Character *obj, Robot *robot){
    //TODO
}

//^^ ExcemptionCard
ExcemptionCard::ExcemptionCard() : BaseItem(ItemType::EXCEMPTION_CARD){}

bool ExcemptionCard::canUse(Character *obj, Robot *robot){
    //TODO
}

void ExcemptionCard::use(Character *obj, Robot *robot){
    //TODO
}

//^^ PassingCard
PassingCard::PassingCard() : BaseItem(ItemType::PASSING_CARD){}

bool PassingCard::canUse(Character *obj, Robot *robot){
    //TODO
}

void PassingCard::use(Character *obj, Robot *robot){
    //TODO
}





////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////