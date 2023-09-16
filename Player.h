//
//  Player.hpp
//  CS32Proj3
//
//  Created by Kaena Kiakona on 5/20/23.
//

#ifndef Player_h
#define Player_h
#include <iostream>
#include <string>
#include "Board.h"
class Player //base class
{
public:
    Player(std::string name) : mname(name){};
    std::string name() const
    {
        return mname;
    }
    
    virtual bool isInteractive() const
    {
        return false;
    }
//    Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    
    virtual int chooseMove(const Board& b, Side s) const = 0;
//    Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    
    virtual ~Player(){}
//    Since this class is designed as a base class, it should have a virtual destructor.

private:
    std::string mname;
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name) : Player(name){}
    virtual bool isInteractive() const
    {
        return true;
    }
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer(){}
};



class BadPlayer : public Player
{
public:
    BadPlayer(std::string name) : Player(name){}
    virtual int chooseMove(const Board& b, Side s) const;
//    virtual ~BadPlayer(){}
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name) : Player(name){}
    virtual int chooseMove(const Board& b, Side s) const;
//    virtual ~SmartPlayer(){}
    
private:
    int eval(const Board& b, Side s, Side originalside) const;
    void chooseMovehelper(Side s, Board& b, int& bestHole, int& value, int currdepth, Side originalside) const;
   
};


#endif /* Player_hpp */
