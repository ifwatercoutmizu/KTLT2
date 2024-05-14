/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
public:
    Path();
};

class Wall : public MapElement {
public:
    Wall();
};

class FakeWall : public MapElement {
public:
    FakeWall();
};

class Map {
private:
    int num_rows, num_cols;
    int **map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid (const Position &pos, MovingObject *mv_obj) const;

    /// Unofficial
    int getNumRows();

    int getNumCols();
};

class Position{
private:
    int r, c;

public:
    static const Position npos;

    Position(int r, int c);

    Position(const string & str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    string str() const;

    bool isEqual(int in_r, int in_c) const;

    /// Unofficial
    bool isEqual(Position pos) const;
};

static const Position npos(-1,-1);

class MovingObject {
protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name);
    
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    
    Position getCurrentPosition() const;
    
    virtual void move() = 0;
    virtual string str() const = 0;

    /// Unofficial
    string getName();
    int getindex();
};

class Character : public MovingObject{
private:
    string name;
public:
    Character(int index, const Position pos, Map*map, string name);
};

class Sherlock : public Character{
private:
    int hp;
    int exp;
    string moving_rule;

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    
    Position getNextPosition();
    void move();
    string str() const;
    // ...
};

class Watson : public Character{
private:
    int hp;
    int exp;
    string moving_rule;

public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    
    Position getNextPosition();
    void move();
    string str() const;
    // ...
};

class Criminal : public Character{
private:
    Sherlock *sherlock;
    Watson *watson;

public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    
    Position getNextPosition();
    void move();
    string str() const;
    // ...
};

class ArrayMovingObject {
private:
    MovingObject *arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject();

    bool isFull() const;
    bool add(MovingObject *mv_obj);
    MovingObject *get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;
};

class Robot : public MovingObject{
private:
    RobotType robot_type;
    BaseItem* item;

public:
    Robot(int index, const Position& init_pos, Map* map, RobotType type);
};

class RobotC : public Robot{
private:
    Criminal *criminal;

public:
    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal);
    
    Position getNextPosition();
    void move();
    string str() const;
};

class RobotS : public Robot{
private:
    Criminal *criminal;
    Sherlock *sherlock;

public:
    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock);
    
    Position getNextPosition();
    void move();
    string str() const;
};

class RobotW : public Robot{
private:
    Criminal *criminal;
    Watson * watson;

public:
    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson);
    
    Position getNextPosition();
    void move();
    string str() const;
};

class RobotSW : public Robot{
private:
    Criminal *criminal;
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    
    Position getNextPosition();
    void move();
    string str() const;
};

class BaseItem{
private:
    ItemType item_type;

public:
    BaseItem(ItemType item_type);

    virtual bool canUse(Character *obj, Robot *robot) = 0;
    virtual void use(Character *obj, Robot *robot) = 0;
};

class MagicBook : public BaseItem{
private:
    int req_exp = 350;

public:
    MagicBook();
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
};

class EnergyDrink : public BaseItem{
private:
    int req_hp = 100;

public:
    EnergyDrink();
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
};

class FirstAid : public BaseItem{
private:
    int req_exp = 350;
    int req_hp = 100;

public:
    FirstAid();
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
};

class ExcemptionCard : public BaseItem{
private:
    string req_obj = "Sherlock";
    int req_hp = 2; //? hp%2 == 1

public:
    ExcemptionCard();
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
};

class PassingCard : public BaseItem{
private:
    string req_obj = "Watson";
    int req_hp = 2; //? hp%2 == 0

public:
    PassingCard();
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
};
// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration *config;
    
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    
    Map *map;
    ArrayMovingObject *arr_mv_objs;


public:
    StudyPinkProgram(const string &config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
