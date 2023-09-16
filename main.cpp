//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doBoardTests()
//{
//    Board b(3, 2);
//    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
//                    b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
//
//    b.setBeans(SOUTH, 1, 1);
//
//
//
//
//    b.moveToPot(SOUTH, 2, SOUTH);
//
//    assert(b.totalBeans() == 11);
//    assert(b.beans(SOUTH, 1) == 1);
//    assert(b.beans(SOUTH, 2) == 0);
//    assert(b.beans(SOUTH, POT) == 2);
//    assert(b.beansInPlay(SOUTH) == 3);
//    Side es;
//    int eh;
////    b.display();
////    cout<<endl;
//    b.sow(SOUTH, 3, es, eh);
//
//    assert(es == NORTH);
//    assert(eh == 3);
//    assert(b.beans(SOUTH, 3) == 0);
//    assert(b.beans(NORTH, 3) == 3);
//    assert(b.beans(SOUTH, POT) == 3);
//    assert(b.beansInPlay(SOUTH) == 1);
//    assert(b.beansInPlay(NORTH) == 7);
//}
//
//int main()
//{
//    doBoardTests();
//    cout << "Passed all tests" << endl;
//}
//
//  main.cpp
//  CS32Proj3
//
//  Created by Kaena Kiakona on 5/20/23.
//

#include <iostream>
#include <queue>
using namespace std;
#include "Board.h"
#include "Player.h"
#include "Game.h"

int main()
{
    Board b(6, 4);
//
//    cout<<b.beans(SOUTH, 0)<<endl;
    Player* p1 = new SmartPlayer("Smart");
    Player* p2 = new BadPlayer("Dumb");
    Game g(b, p2, p1);
    g.play();
}

//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 0);
//    b.setBeans(SOUTH, 1, 2);
//    b.setBeans(NORTH, 2, 1);
//    b.setBeans(NORTH, 3, 2);
//    Game g(b, &bp1, &bp2);
//    bool over;
//    bool hasWinner;
//    Side winner;
//      //    Homer
//      //   0  1  2
//      // 0         0
//      //   2  0  0
//      //    Bart
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//    g.move(SOUTH);
//    cout<<"got here 1"<<endl;
//      //   0  1  0
//      // 0         3
//      //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    cout<<"got here 2"<<endl;
//    g.move(NORTH);
//      //   1  0  0
//      // 0         3
//      //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//    cout<<"got here 3"<<endl;
//
//
//    g.move(SOUTH);
//      //   1  0  0
//      // 0         3
//      //   0  0  1
//    cout<<"got here 4"<<endl;
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//    cout<<"got here 5"<<endl;
//
//
//    g.move(NORTH);
//      //   0  0  0
//      // 1         4
//      //   0  0  0
//    cout<<"got here 6"<<endl;
//    g.status(over, hasWinner, winner);
//    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
//    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//    assert(hasWinner && winner == SOUTH);
//    cout<<"got here 7"<<endl;
//}
//
//int main()
//{
//    doGameTests();
//    cout << "Passed all tests" << endl;
//}

//123456p
//123456p

//#include "Player.h"
//    #include "Board.h"
//    #include "Side.h"
//    #include <iostream>
//    #include <cassert>
//    using namespace std;
//
//    void doPlayerTests()
//    {
//        HumanPlayer hp("Marge");
//        assert(hp.name() == "Marge"  &&  hp.isInteractive());
//        BadPlayer bp("Homer");
//        assert(bp.name() == "Homer"  &&  !bp.isInteractive());
//        SmartPlayer sp("Lisa");
//        assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
//        Board b(3, 2);
//        b.setBeans(SOUTH, 2, 0);
//        cout << "=========" << endl;
//        int n = hp.chooseMove(b, SOUTH);
//        cout << "=========" << endl;
//        assert(n == 1  ||  n == 3);
//        n = bp.chooseMove(b, SOUTH);
//        assert(n == 1  ||  n == 3);
//        n = sp.chooseMove(b, SOUTH);
//        assert(n == 1  ||  n == 3);
//    }
//
//    int main()
//    {
//        doPlayerTests();
//        cout << "Passed all tests" << endl;
//    }
