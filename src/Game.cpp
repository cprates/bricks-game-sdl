
#include <string>
#include <iostream>
#include "GameMatrix.h"

using namespace std;

int main() {
    GameMatrix *gm = new GameMatrix(0, 0, 10, 10);

    gm->genColumn(6);
    gm->genColumn(6);
    gm->genColumn(6);
    //gm->getElement(1, 4)->getColour()->print();
    vector<MatrixElement*> adjacentTwins;
    gm->getAdjacentTwins(1, 5, &adjacentTwins);

    gm->print();
    cout << "Score: " << gm->reallocElements() << endl;
    cout << endl << endl;
    gm->print();
    delete gm;
}
