//
//  Game.cpp
//  CS32Proj3
//
//  Created by Kaena Kiakona on 5/20/23.
//

#include "Game.h"
using namespace std;
Game::Game(const Board& b, Player* south, Player* north) : mboard(b), southplayer(south), northplayer(north)
{
    ;
}

void Game::display() const
{
    for(int i = 0; i < mboard.holes()/2; i++)
    {
        cout<<" ";
    }
    cout<<northplayer->name()<<endl;
    cout<<" ";
    for(int i = 1; i <= mboard.holes(); i++)
    {
        cout<<beans(NORTH, i)<<" ";
    }
    
    cout<<endl;

    cout<<beans(NORTH, POT);
    for(int i = 0; i < mboard.holes()*2 - 1; i++)
    {
        cout<<" ";
    }
    
    cout<<beans(SOUTH, POT);
    cout<<endl;
    cout<<" ";
    for(int i = 1; i <= mboard.holes(); i++)
    {
        cout<<beans(SOUTH, i)<<" ";
    }
    cout<<endl;
    for(int i = 0; i < mboard.holes()/2; i++)
    {
        cout<<" ";
    }
    cout<<southplayer->name()<<endl;
}



void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if(mboard.beansInPlay(SOUTH) > 0 && mboard.beansInPlay(NORTH) > 0)
    {
//        cout<<mboard.beansInPlay(SOUTH)<<endl;
//        cout<<mboard.beansInPlay(NORTH)<<endl;
        over = false;
        return;
    }
    over = true;
    int northpoints = mboard.beans(NORTH, 0);
    int southpoints = mboard.beans(SOUTH, 0);
    if(northpoints == southpoints)
    {
        hasWinner = false;
        return;
    }
    hasWinner = true;
    if(northpoints > southpoints)
    {
        winner = NORTH;
    }
    if(northpoints < southpoints)
    {
        winner = SOUTH;
    }
    
}

bool Game::move(Side s) //need to make recursive calls for if player does 2 captures in a row or if player makes capture then ends on their pot or ends on their pot twice in a row
{
    //display();
//    Side other;
//    if(s == NORTH)
//    {
//        other = SOUTH;
//    }
//    else
//    {
//        other = NORTH;
//    }d
    Side endSide;
    int endHole;
    if(s == NORTH)
    {
        if(mboard.beansInPlay(NORTH) == 0) //if north has no more beans, end game
        {
            for(int i = 1; i < mboard.holes() + 1; i++)
            {
                mboard.moveToPot(SOUTH, i, SOUTH); //sweeping into pots
            }
            return false;
        }
        int dir = northplayer->chooseMove(mboard, NORTH); //pick move
        mboard.sow(NORTH, dir, endSide, endHole);
        
        
        while(endSide == NORTH && endHole == 0) //if ends in own pot
        {
            
//            if(!northplayer->isInteractive() && !southplayer->isInteractive())
//            {
//                cout<<"Press enter to continue for "<<northplayer->name()<<": ";
//                cin.ignore();
//            }
            display();
            return move(NORTH); //call move again on the same side
            
        }
        
        if(endSide == NORTH && mboard.beans(NORTH, endHole) == 1 && mboard.beans(SOUTH, endHole) > 0 && endHole != 0)
        {
            
        
            mboard.moveToPot(SOUTH, endHole, NORTH); //moving to pot
            mboard.moveToPot(NORTH, endHole, NORTH);
            
        }
    }
    //same as above
    if(s == SOUTH)
    {
        if(mboard.beansInPlay(SOUTH) == 0)
        {

            for(int i = 1; i < mboard.holes() + 1; i++)
            {
                mboard.moveToPot(NORTH, i, NORTH);
            }
            return false;
        }
        
        int dir = southplayer->chooseMove(mboard, SOUTH);
        mboard.sow(SOUTH, dir, endSide, endHole);
        
        while(endSide == SOUTH && endHole == 0)
        {
//            if(!southplayer->isInteractive() && !northplayer->isInteractive())
//            {
//                cout<<"Press enter to continue for "<<southplayer->name()<<": ";
//                cin.ignore();
//            }
//            
            display();
            return move(SOUTH);
            
        }
        
        if(endSide == SOUTH && mboard.beans(SOUTH, endHole) == 1 && mboard.beans(NORTH, endHole) > 0 && endHole != 0)
        {
//            cout<<"Capture!"<<endl;
            mboard.moveToPot(NORTH, endHole, SOUTH);
            mboard.moveToPot(SOUTH, endHole, SOUTH);
            
        }
    }
    return true;
}

void Game::play()
{
    bool over = false;
    bool hasWinner = false;
    Side winner;
    bool southmove = true;
    bool northmove = true;
    
    if(!northplayer->isInteractive() && !southplayer->isInteractive())
    {
        display();
        cout<<endl;
        while(true)
        {
            southmove = move(SOUTH);
            status(over, hasWinner, winner);
            if(!southmove)
            {
                break;
            }
            cout<<"Press enter to continue for " << southplayer->name()<< ": ";
            cin.ignore();
            cout<<endl;
            display();
            cout<<endl;
            
            
            
            
            northmove = move(NORTH);
            status(over, hasWinner, winner);
            if(!northmove)
            {
                break;
            }
            cout<<"Press enter to continue for "<<northplayer->name()<<": ";
            cin.ignore();
            display();
            cout<<endl;
            
            
            
        }
    }
    
    while(northmove == true)
    {
        display();
        southmove = move(SOUTH);
        cout<<endl;
        status(over, hasWinner, winner);
        if(!southmove)
        {
            break;
        }
        
        display();
        northmove = move(NORTH);
        cout<<endl;
        status(over, hasWinner, winner); //put this line in move function cus when game ends on south dude putting something in his own pot, will keep going infinitely
    }
    cout<<endl;
    display();
    
    if(hasWinner && winner == NORTH)
    {
        cout<<northplayer->name()<<" wins!"<<endl;
    }
    else if(hasWinner && winner == SOUTH)
    {
        cout<<southplayer->name()<<" wins!"<<endl;
    }
    else
    {
        cout<<"It's a tie!"<<endl;
    }
    
}



int Game::beans(Side s, int hole) const
{
    return mboard.beans(s, hole);
}
