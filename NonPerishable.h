#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H

#include "Item.h"

namespace sdds
{
    class NonPerishable : public Item
    {
    public:
        // defining base class virtual function
        char itemType() const;

        // Overwriting base class input function
        ostream &write(ostream &os) const;
        ofstream &save(ofstream &ofs);
    };
} // namespace sdds

#endif