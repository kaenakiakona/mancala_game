//
//  Side.h
//  CS32Proj3
//
//  Created by Kaena Kiakona on 5/20/23.
//

#ifndef Side_h
#define Side_h
enum Side { NORTH, SOUTH };
//            0      1

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

#endif /* Side_h */
