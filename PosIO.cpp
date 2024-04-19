#include <iostream>

#include "PosIO.h"

using namespace std;
using namespace sdds;

namespace sdds
{
    PosIO::~PosIO()
    {
        // Do Nothing
    }

    ostream &operator<<(ostream &os, const PosIO &rOp)
    {
        return rOp.write(os);
    }

    ofstream &operator<<(ofstream &ofs, PosIO &rOp)
    {
        return rOp.save(ofs);
    }

    istream &operator>>(istream &is, PosIO &rOp)
    {
        return rOp.read(is);
    }

    ifstream &operator>>(ifstream &ifs, PosIO &rOp)
    {
        rOp.load(ifs);
        return ifs;
    }

} // namespace sdds
