//
//  Board.cpp
//  CS32Proj3
//
//  Created by Kaena Kiakona on 5/20/23.
//

#include "Board.h"
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole) : mHoles(nHoles), minitialBeans(nInitialBeansPerHole), mnorthboard(1, nInitialBeansPerHole), msouthboard(1, nInitialBeansPerHole)
{
    if(nHoles < 1)
    {
        mHoles = 1;
    }
    if(nInitialBeansPerHole < 0)
    {
        minitialBeans = 0;
    }
    
    mnorthboard.resize(mHoles + 1, minitialBeans);
    msouthboard.resize(mHoles + 1, minitialBeans);
    
    mnorthboard[0] = 0;
    
    msouthboard[0] = 0;
    
    
}







int Board::holes() const
{
    return mHoles;
}

int Board::totalBeans() const
{
    int totalbeans = 0;
    for(int i = 0; i <= mHoles; i++)
    {
        totalbeans += msouthboard[i];
        totalbeans += mnorthboard[i];

    }
    return totalbeans;
}

int Board::beans(Side s, int hole) const
{
    if(hole > mHoles || hole < 0)
    {
        return -1;
    }
    
    if(s == SOUTH)
    {
        if(hole == 0)
        {
            return msouthboard[0];
        }
        
        return msouthboard[mHoles - hole + 1]; 
    }
    else
    {
        return mnorthboard[hole];
    }
}

int Board::beansInPlay(Side s) const
{
    
    int count = 0;
    if(s == NORTH)
    {
        for(int i = 1; i <= mHoles; i++)
        {
            count += mnorthboard[i];
        }
    }
    
    if(s == SOUTH)
    {
        for(int i = 1; i <= mHoles; i++)
        {
            count += msouthboard[i];
        }
    }
    return count;
}



int Board::sowhelper(vector<int>& startboard, vector<int>& otherboard, int starthole, int& endhole)
{
   int numbeans = startboard[starthole];
   startboard[starthole] = 0;
   int holetracker = starthole;
   while(numbeans > 0)
   {
       holetracker--;
       if(holetracker < -mHoles)
       {
           holetracker = mHoles;
       }
       
       if(holetracker >= 0)
       {
           startboard[holetracker] += 1;
           
       }
       
       if(holetracker < 0 && holetracker >= -mHoles)
       {
           otherboard[mHoles + holetracker+1] += 1;
       }

       numbeans--;
       
       
   }

    endhole = abs(holetracker);

    
    
    if(holetracker >= 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}



bool Board::sow(Side s, int hole, Side &endSide, int &endHole)
{
    

    if(s == NORTH)
    {
        if (hole <= 0 || hole > mHoles || mnorthboard[hole] <= 0 )
        {
            return false;
        }
        

        int ends = sowhelper(mnorthboard, msouthboard, hole, endHole);
        
        if(ends == 0)
        {
            //cout<<"NorthNorth"<<endl;
            endSide = NORTH;
            
        }
        if(ends == -1)
        {
            //cout<<"NorthSouth"<<endl;
            //endHole = mHoles - endHole + 1;
            endSide = SOUTH;
            
        }
        return true;
        
    }
    if(s == SOUTH){
        if (hole == 0 || hole > mHoles || msouthboard[mHoles-hole+1] <= 0 )
        {
            return false;
        }
        
        int ends = sowhelper(msouthboard, mnorthboard, mHoles-hole+1, endHole);
        
        if(ends == 0)
        {
            //cout<<"SouthSouth"<<endl;
            endSide = SOUTH;
            if(endHole != 0)
                endHole = mHoles - endHole + 1;
        }
        if(ends == -1)
        {
            endSide = NORTH;
            endHole = mHoles - endHole + 1;
            //cout<<"SouthNorth"<<endl;

        }
        return true;
    }
    return false;
}

//void Board::display() const
//{
//    cout<<" ";
//    for(int i = 1; i <= mHoles; i++)
//    {
//        cout<<mnorthboard[i]<<" ";
//    }
//    
//    cout<<endl;
//
//    cout<<mnorthboard[0];
//    for(int i = 0; i < mHoles*2 - 1; i++)
//    {
//        cout<<" ";
//    }
//    
//    cout<<msouthboard[0];
//    cout<<endl;
//    cout<<" ";
//    for(int i = mHoles; i >= 1; i--)
//    {
//        cout<<msouthboard[i]<<" ";
//    }
//    cout<<endl;
//    
//}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    int beans = 0;
    if(hole <= 0 || hole > mHoles)
    {
        return false;
    }
    if(s == NORTH)
    {
        beans = mnorthboard[hole];
        mnorthboard[hole] = 0;
    }
    if(s == SOUTH)
    {
        beans = msouthboard[mHoles - hole + 1];
        //cout<<mHoles-hole+1<<endl;
        msouthboard[mHoles - hole + 1] = 0;
    }
    
    if(potOwner == NORTH)
    {
        mnorthboard[0] += beans;
    }
    else
    {
        msouthboard[0] += beans;
    }
    return true;
}
 

bool Board::setBeans(Side s, int hole, int beans)
{
    if(hole < 0 || hole > mHoles || beans<0)
    {
        return false;
    }
    if(s == NORTH)
    {
        mnorthboard[hole] = beans;
    }
    if(s == SOUTH)
    {
        msouthboard[mHoles - hole + 1] = beans;
    }
    return true;
}



