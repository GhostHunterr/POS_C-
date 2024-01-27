#include <iostream>
#include <fstream>
#include "NonPerishable.h"

using namespace sdds;
using namespace std;

namespace sdds
{
    // defining base class virtual function
    char NonPerishable::itemType() const
    {
        return 'N';
    }

    // Overwriting base class input function
    ostream &NonPerishable::write(ostream &os) const
    {
        Item::write(os);

        if (!err)
        {
            if (i_displayType == POS_FORM)
            {
                os << "=============^" << endl;
            }
            else if (i_displayType == POS_LIST)
            {
                os << "     N / A   |";
            }
        }
        return os;
    }

    ofstream &NonPerishable::save(ofstream &ofs)
    {
        Item::save(ofs);
        if (ofs.good())
        {
            ofs << endl;
        }
        return ofs;
    }

} // namespace sdds
