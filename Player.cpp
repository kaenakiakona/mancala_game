//
//  Player.cpp
//  CS32Proj3
//
//  Created by Kaena Kiakona on 5/20/23.
//

#include "Player.h"
#include <climits>
const int INF = 2147483646;

int HumanPlayer::chooseMove(const Board &b, Side s) const
{
    if(s != SOUTH && s != NORTH)
    {
        return -1;
    }
    int hole = 0;
    if(b.beansInPlay(s) == 0)
    {
        return -1;
    }
    while (hole == 0 || hole > b.holes() || b.beans(s, hole) == 0)
    {
        cout<<"Please enter a move, "<<name()<<": ";
        cin>>hole;
    }
    
    return hole;
}

int BadPlayer::chooseMove(const Board &b, Side s) const
{
    for(int i = 1; i <= b.holes(); i++)
    {
        if(b.beans(s, i) != 0)
        {
            return i;
        }
    }
    return -1;
}


int SmartPlayer::eval(const Board &b, Side s, Side originalside) const
{
//    b.display();
    Side other;
    if(s == NORTH)
    {
        other = SOUTH;
    }
    else
    {
        other = NORTH;
    }
    int num = 0;
    int beansinplay = b.beansInPlay(originalside);
    if(s == originalside)
    {
        num = b.beans(s, 0) - b.beans(other, 0);
//        beansinplay = b.beansInPlay(s);
    
        if(num > 0 && beansinplay == 0)
        {
            return INF;
        }
        if(num < 0 && beansinplay == 0)
        {
            return -INF;
        }
    }
    else
    {
        num = b.beans(other, 0) - b.beans(s, 0);
        
        if(num > 0 && beansinplay == 0)
        {
            return INF;
        }
        if(num < 0 && beansinplay == 0)
        {
            return -INF;
        }
    }
    
    return num;
}
//
////eval can either be constant and favor one side or another or be absolute and find the error
//
void SmartPlayer::chooseMovehelper(Side s, Board &b, int &bestHole, int& value, int currdepth, Side originalside) const
{
//    b.display();
//    cout<<endl;
//    if(s == NORTH)
//    {
//        cout<<"NORTH"<<endl;
//    }
//    else
//    {
//        cout<<"SOUTH"<<endl;
//    }
    
    
    if(b.beansInPlay(s) == 0)
    {
        bestHole = -1;
        value = eval(b, s, originalside);
        return;
    }

    if(currdepth == 8)
    {
        bestHole = -1;
        value = eval(b, s, originalside);
//        cout<<"Basecase: "<<value<<endl;

        return;
    }
    Side other;
    if(s == NORTH)
    {
        other = SOUTH;
    }
    else
    {
        other = NORTH;
    }

    Board copyboard(b);
    Side endSide;
    int endHole;
    if(s == originalside)
    {
//        cout<<"Maximizer"<<endl;
        value = INT_MIN;
        for(int i = 1; i <= copyboard.holes(); i++)
        {
    //        cout<<"Hole: "<< i<<endl;
            int h2;
            int v2 = INT_MIN;
            if(copyboard.beans(s, i) > 0) //here
            {
    //            cout<<"it sees this at least"<<endl;
                copyboard.sow(s, i, endSide, endHole);
                //chooseMovehelper(other, b, h2, v2, currdepth + 1);
                if(endSide == s && copyboard.beans(s, endHole) == 1 && copyboard.beans(other, endHole) != 0 && endHole != 0)
                {
                    
                    copyboard.moveToPot(s, endHole, s);
                    copyboard.moveToPot(other, endHole, s);
    //                bestHole = i;
                }
                
                if(endSide == s && endHole == 0)
                {
    //                bestHole = i;
    //                break;
    //                cout<<"I went twice"<<endl;
                    chooseMovehelper(s, copyboard, h2, v2, currdepth + 1, originalside);
                    //break;
                }
                
                else
                {
                    chooseMovehelper(other, copyboard, h2, v2, currdepth + 1, originalside);
                }
                
                if(v2 >= value)
                {
        //            cout<<"V2: "<<v2<<endl;
        //            cout<<"Value: "<<value<<endl;
                    bestHole = i;
                    value = v2;
                }
            }
//

            copyboard = b;
    //
        }
    }
    else
    {
//        cout<<"Minimizer"<<endl;
        value = INT_MAX;
        for(int i = 1; i <= copyboard.holes(); i++)
        {
    //        cout<<"Hole: "<< i<<endl;
            int h2;
            int v2 = INT_MAX;
            if(copyboard.beans(s, i) > 0) //here
            {
    //            cout<<"it sees this at least"<<endl;
                copyboard.sow(s, i, endSide, endHole);
                //chooseMovehelper(other, b, h2, v2, currdepth + 1);
                if(endSide == s && copyboard.beans(s, endHole) == 1 && copyboard.beans(other, endHole) != 0 && endHole != 0)
                {
                    
                    copyboard.moveToPot(s, endHole, s);
                    copyboard.moveToPot(other, endHole, s);
    //                bestHole = i;
                }
                
                if(endSide == s && endHole == 0)
                {
    //                bestHole = i;
    //                break;
    //                cout<<"I went twice"<<endl;
                    chooseMovehelper(s, copyboard, h2, v2, currdepth + 1, originalside);
                    //break;
                }
                
                else
                {
                    chooseMovehelper(other, copyboard, h2, v2, currdepth + 1, originalside);
                }
                if(v2 <= value)
                {
        //            cout<<"V2: "<<v2<<endl;
        //            cout<<"Value: "<<value<<endl;
                    bestHole = i;
                    value = v2;
                }
            }

            copyboard = b;
//            cout<<"Current depth: "<<currdepth<<endl;
//            cout<<"v2: "<<v2<<endl;
//            cout<<endl;

            
    //        cout<<"Choosemovehelper: ";
    //        cout<<value<<endl;
    ////        cout<<endl;
    //        cout<<"Best hole: "<<bestHole<<endl;
    //        cout<<endl;
        }
    }

    

    return;
}

//need to instantiate value to be something so that it picks a value when its losing

int SmartPlayer::chooseMove(const Board &b, Side s) const
{
    if(s != SOUTH && s != NORTH)
    {
        return -1;
    }
    int bestHole = 0;
    int value;
    Board tester(b);
    if(b.beansInPlay(s) == 0)
    {
        return -1;
    }
    chooseMovehelper(s, tester, bestHole, value, 0, s);
    



    return bestHole;
}


//need to update board for captures and ending the games
