#include <iostream>
#include "Item.h"

using namespace std;

namespace sdds
{
    class PosApp
    {
        char file_name[128];
        Item *Iptr[MAX_NO_ITEMS]{};
        int nptr;

    protected:
        void action(const char *title) const;
        void empty();
        void deallIptr();

    public:
        // Constructor
        PosApp(const char *fileName);
        PosApp(const PosApp &copy) = delete;
        ~PosApp();

        // Operator Overloading
        PosApp &operator=(const PosApp &copy) = delete;

        // Other Functions
        int menu();

        int selectItem();

        void listItems();
        void addItem();
        void removeItem();
        void stockItem();
        void POS();

        void saveRecs();
        void loadRecs();

        void run();

        // Other Functions
        double printItems();
    };
} // namespace sdds
