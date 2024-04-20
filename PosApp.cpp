#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>
#include "PosApp.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Bill.h"
#include "Utils.h"
using namespace sdds;
using namespace std;

namespace sdds
{
	// Constructor
	PosApp::PosApp(const char* fileName)
	{
		empty();
		if (fileName != nullptr && fileName[0] != '\0')
		{
			strcpy(file_name, fileName);
		}
	}

	PosApp::~PosApp()
	{
		deallIptr();
	}
	void PosApp::action(const char* title) const
	{
		cout << ">>>> "
			<< left
			<< setw(72)
			<< setfill('.')
			<< title
			<< endl;
	}

	void PosApp::empty()
	{
		deallIptr();
		nptr = 0;
		file_name[0] = '\0';
	}

	void PosApp::deallIptr()
	{
		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			if (Iptr[i] != nullptr)
			{
				delete Iptr[i];
			}
			Iptr[i] = nullptr;
		}
	}

	// Other Functions
	int PosApp::menu()
	{
		int input; // user-input
		bool flag;

		cout << "The Convenience Corner" << endl
			<< "----------------------" << endl;
		cout << "1- List items" << endl
			<< "2- Add item" << endl
			<< "3- Remove item" << endl
			<< "4- Stock item" << endl
			<< "5- POS" << endl
			<< "0- exit program" << endl
			<< "> ";
		do
		{
			cin >> input;
			if (cin.fail()) // Checking if the input matches the input variable type
			{
				cin.clear(); // clearing Error Flags
				cout << "Invalid Integer, try again: ";
				flag = false;
			}
			else if (input < 0 || input > 5)
			{
				cin.clear(); // clearing Error Flags
				cout << "[0<=value<=5], retry: > ";
				flag = false;
			}
			else // Valid Input
			{
				flag = true;
			}
			cin.ignore(1000, '\n'); // Clearing Input Buffer

		} while (!flag);

		return input;
	}

	void PosApp::run()
	{

		bool main_flag = true; // true - keep going : false - exit

		loadRecs();

		do
		{
			// Load the menu
			int input = menu();

			// Calling functions based on input
			switch (input)
			{
			case 1:
				listItems();
				break;
			case 2:
				addItem();
				break;
			case 3:
				removeItem();
				break;
			case 4:
				stockItem();
				break;
			case 5:
				POS();
				break;
			case 0:
				saveRecs();
				main_flag = false;
				break;
			}

		} while (main_flag);

		cout << "Goodbye!" << endl;
	}

	int PosApp::selectItem()
	{
		action("Item Selection by row number");
		cout << "Press <ENTER> to start....";
		cin.ignore();

		printItems();
		bool flag = false;
		int rowNum = -1;

		cout << "Enter the row number: ";
		do
		{
			cin >> rowNum;
			if (cin.fail())
			{
				cout << "Invalid Integer, try again: ";
				flag = false;
			}
			else if (rowNum < 1 || rowNum > nptr)
			{
				cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
				flag = false;
			}
			else
			{
				flag = true;
			}
			clearInputBuffer();
		} while (!flag);

		return rowNum;
	}

	void PosApp::listItems()
	{
		double total = printItems();
		cout << "                               Total Asset: $  |"
			<< setw(14)
			<< setfill(' ')
			<< right
			<< setprecision(2)
			<< total
			<< "|"
			<< left << endl;
		cout << "-----------------------------------------------^--------------^" << endl
			<< endl;
	}

	void PosApp::addItem()
	{
		action("Adding Item to the store");

		if (nptr == MAX_NO_ITEMS)
		{
			cout << "Inventory Full!" << endl;
		}
		else
		{
			Item* temp = nullptr;
			char input;
			bool flag = false;

			cout << "Is the Item perishable? (Y)es/(N)o: ";
			do
			{

				cin >> input;
				if (cin.good())
				{
					if (toupper(input) == 'Y')
					{
						clearInputBuffer();
						temp = new Perishable();
						cin >> *temp;

					}
					else if (toupper(input) == 'N')
					{
						clearInputBuffer();
						temp = new NonPerishable();
						cin >> *temp;
					}
					else
					{
						flag = true;
						cout << "Wrong Input!! \nPlease Try again >>";
					}
				}
				else
				{
					flag = true;
				}
				clearInputBuffer();

			} while (flag);

			if (temp)
			{
				Iptr[nptr] = temp;
				Iptr[nptr]->displayType(POS_LIST);
				action("DONE!");
				nptr++;
			}
		}
	}

	void PosApp::removeItem()
	{
		action("Remove Item");

		int selection = selectItem() - 1;

		cout << "Removing...." << endl;
		Iptr[selection]->displayType(POS_FORM);
		cout << *Iptr[selection];

		delete Iptr[selection];
		Iptr[selection] = nullptr;

		for (int i = selection; i < nptr; i++)
		{
			Iptr[i] = Iptr[i + 1];
		}

		nptr--;

		action("DONE!");
	}

	void PosApp::stockItem()
	{
		int addQnt = 0;
		bool flag = false;
		int rowNum;

		action("Select an item to stock");
		rowNum = selectItem() - 1; // Row number in index

		cout << "Selected Item:" << endl;

		//Checking if the Qnt limit is reached.
		if (Iptr[rowNum]->quantity() == 99)
		{
			cout << "\n!!!!! You have reached the MAXIMUM NO. OF QUANTITY (" << MAX_STOCK_NUMBER << ") for the above Product. !!!\n" << endl;
			return;
		}

		//If not reached: Change the display type and print the details.
		Iptr[rowNum]->displayType(POS_FORM);
		cout << *Iptr[rowNum];

		cout << "Enter quantity to add: ";
		do
		{
			cin >> addQnt;
			if (cin.fail())
			{
				cout << "Invalid Integer, try again: ";
				flag = true;
			}
			else if (addQnt < 1 || (MAX_STOCK_NUMBER - Iptr[rowNum]->quantity()) < addQnt)
			{
				cout << "[1<=value<=" << (MAX_STOCK_NUMBER - Iptr[rowNum]->quantity()) << "], retry.\n >> ";
				flag = true;
			}
			else
			{
				flag = false;
			}
			clearInputBuffer();
		} while (flag);

		Iptr[rowNum]->operator+=(addQnt);
		Iptr[rowNum]->displayType(POS_LIST);

		action("DONE!");
	}

	void PosApp::POS()
	{
		// bool flag = true;
		Bill bTotal;
		char skuInp[MAX_SKU_LEN];
		int iFound = -1;
		bool mainFlag = true;
		bool flag = false;

		action("Starting Point of Sale");

		do
		{
			mainFlag = false;
			iFound = -1;
			flag = false;

			cout << "Enter SKU or <ENTER> only to end sale..." << endl
				<< "> ";
			cin.getline(skuInp, MAX_SKU_LEN, '\n');
			if (cin.good())
			{
				if (skuInp[0] != '\0')
				{
					// Search for the Item
					for (int i = 0; i < nptr && !flag; i++)
					{
						if (Iptr[i]->operator==(skuInp))
						{
							iFound = i;
							flag = true;
						}
					}

					if (flag)
					{
						Iptr[iFound]->operator-=(1);
						Iptr[iFound]->displayType(POS_FORM);
						cout << *Iptr[iFound];
						Iptr[iFound]->displayType(POS_LIST);

						// Adding to the bill
						if (Iptr[iFound]->operator bool())
						{
							bTotal.add(Iptr[iFound]);
							cout << endl
								<< ">>>>> Added to bill" << endl
								<< ">>>>> Total: " << fixed << setprecision(2) << bTotal.total() << endl;
						}
						else
						{
							Iptr[iFound]->clear();
						}
					}
					else
					{
						cout << "!!!!! Item Not Found !!!!!" << endl;
					}
				}
				else
				{
					mainFlag = true;
				}
			}
			else
			{
				cin.ignore(1000, '\n');
				cout << "SKU too long" << endl;
				fflush(stdin);
			}

		} while (!mainFlag);

		bTotal.print(cout);
	}

	void PosApp::saveRecs()
	{
		action("Saving Data");

		ofstream ifs(file_name);

		for (int i = 0; i < nptr; i++)
		{
			if (Iptr[i] != nullptr)
			{
				ifs << *Iptr[i];
			}
		}
	}

	void PosApp::loadRecs()
	{
		action("Loading Items");
		ifstream ifs(file_name);

		if (ifs.fail())
		{
			ofstream ofs("Output.csv");
			ofs.close();
		}
		else
		{
			bool flag = true;
			deallIptr();

			while (ifs.good() && nptr < MAX_NO_ITEMS && flag)
			{
				char typeOfItem;
				Item* temp = nullptr;

				ifs >> typeOfItem;
				ifs.ignore();

				if (ifs.fail())
				{
					if (ifs.eof())
					{
						flag = false;
					}
					else
					{
						cout << "Invalid Data";
					}
				}
				else if (typeOfItem == 'P')
				{
					temp = new Perishable();
					if (temp->load(ifs))
					{
						Iptr[nptr] = temp;
						Iptr[nptr]->displayType(POS_LIST);
						nptr++;
					}
				}
				else if (typeOfItem == 'N')
				{
					temp = new NonPerishable();
					if (temp->load(ifs))
					{
						Iptr[nptr] = temp;
						Iptr[nptr]->displayType(POS_LIST);
						nptr++;
					}
				}
				temp = nullptr;
			}
		}
	}

	double PosApp::printItems()
	{
		double total = 0;
		action("Listing Items");

		// Sorting
		for (int turn = 0; turn < nptr - 1; turn++)
		{
			for (int j = 0; (j < nptr - 1 - turn); j++)
			{

				if (Iptr[j]->operator>(*Iptr[j + 1]))
				{
					Item* temp = nullptr;
					temp = Iptr[j];
					Iptr[j] = Iptr[j + 1];
					Iptr[j + 1] = temp;
				}
			}
		}

		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl
			<< "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		for (int i = 0; i < nptr; i++)
		{
			cout << setw(4)
				<< right
				<< setfill(' ')
				<< i + 1
				<< " | ";
			if (Iptr[i] != nullptr)
			{
				Iptr[i]->write(cout);
				total += (Iptr[i]->cost()) * (Iptr[i]->quantity());
			}
			cout << endl;
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		return total;
	}
}