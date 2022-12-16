	/***********************************************************/
	/*                      Vending Use-case                   */
	/***********************************************************/
	
	#include <iostream>

	using namespace std;

	#include "conio.h"
	#include <string.h>

	#include "vending_mgt.h"
	#include "vending_user.h"

	/***********************************************************/
	/*                      Vending Installation               */
	/***********************************************************/

	#define PRODUCTS	4

	Slot* slot_Preparation() 
	{
		Slot* slot;
		Product* product;

		slot = new_Slot(PRODUCTS);
		product = new_Product(Product_Code::Mars);
		add_Product(slot, product);
		product = new_Product(Product_Code::Bounty);
		add_Product(slot, product);
		product = new_Product(Product_Code::Snickers);
		add_Product(slot, product);
		return slot;
	};

	/***********************************************************/

	#define SLOTS	4

	Vending* Vending_Installation() 
	{
		Slot* slot;
		Vending* machine = new_Vending(SLOTS);
		for (short i = 0; i < SLOTS; i++) 
		{
			slot = slot_Preparation();
			add_Slot(machine, slot);
		};
		return machine;
	};

	/***********************************************************/
	/*              Vending Human-Machine Interface            */
	/***********************************************************/

	void show_Line(const char* line, short maxsize)		// supplementary
	{
		short size = strlen(line);
		if (size < maxsize)
		{
			cout << line;
			for (short i = 0; i < maxsize - size; i++)cout << " ";
		}
		else
		{
			for (short i = 0; i < maxsize - 3; i++)cout << line[i];
			cout << "...";
		};
	};

	/***********************************************************/

	void show_Bar()										// supplementary
	{
		for (short i = 0; i < 40; i++)cout << "-";
		cout << endl;
	};

	/***********************************************************/

	void show_Assortment()	// show the list of products
	{
		short maxsize = 0;
		short size = 0;
		const char* name;

		show_Bar();
		cout << " название        стоимость" << endl;
		show_Bar();

		for (short i = 0; i < NUMPRODUCTS; i++)
		{
			cout << " ";
			name = assortment[i].name;
			show_Line(name, 15);
			cout << " ";
			cout << assortment[i].price;
			cout << endl;
		};
		show_Bar();
	};

	/***********************************************************/
 
	bool no_Products(short* availability) 
	{
		short total = 0;
		for (short i = 0; i < NUMPRODUCTS; i++)total += availability[i];
		if (total == 0)
		{
			cout << " к сожалению, продукты отсутствуют" << endl;
			return true;
		};
		return false;
	};

	/***********************************************************/

	void show_Availability(Vending* machine)	// show product availability
	{
		short maxsize = 0;
		short size = 0;
		const char* name;

		short* availability = product_Availability(machine);

		show_Bar();

		if (no_Products(availability)) 
		{
			show_Bar();
			return;
		};

		cout << " название      стоимость  шт  " << endl;
		show_Bar();

		for (short i = 0; i < NUMPRODUCTS; i++)
		{
			if (availability[i] != 0)
			{
				cout << " ";
				name = assortment[i].name;
				show_Line(name, 15);
				show_Line(assortment[i].price.to_String(), 10);
				cout << availability[i];
				cout << endl;
			};
		};
		show_Bar();
	};

	/***********************************************************/

	char choose_Code() 
	{
		while (1)
		{
			char c;
			c = _getch();
			if (c == 'c')return c;
			if ((c >= 48) && (c < 48 + NUMPRODUCTS))
			{
				cout << c << endl;
				return c;
			};
		};
	};

	/***********************************************************/

	void choose_Product(Vending* machine)
	{
		short code;
		Product* product = nullptr;
		const char* name;
		short* availability = product_Availability(machine);

		if (no_Products(availability))
		{
			show_Bar();
			return;
		};

		cout << " выбор продукта" << endl;
		show_Bar();
		for (short i = 0; i < NUMPRODUCTS; i++)
		{
			cout << " ";
			name = assortment[i].name;
			show_Line(name, 15);
			cout << i << endl;
		};
		cout << " отказ          c" << endl;
		show_Bar();
		cout << " продукт : ";
		char c = choose_Code();
		show_Bar();
		if (c == 'c')
		{ 
			cout << " отказ от покупки"<< endl; 
			return;
		}
	
		code = c - 48;

		if (availability[code] == 0)	// check availability
		{
			cout << " у сожалению, этот продукт временно отсутствует " << endl;
				return;
		};
	
		product = buy_Product(machine, (Product_Code)code);

		name = assortment[code].name;
		cout << " пожалуйста, возмите ваш " << name << endl;
		delete product;	// it should be eaten!
	};

	/***********************************************************/

	char get_Operation() 
	{
		while (1)
		{
			char c;
			c = _getch();
			switch (c) 
			{
			case '0' : return c;
			case '1' : return c;
			case 27  : return c;
			};
		};
	};

	/***********************************************************/

	void start_Usage(Vending* machine)
	{
		char c;
		while (1)
		{
			show_Bar();
			cout << " 0 : список продуктов" << endl;
			cout << " 1 : покупка продукта" << endl;
			show_Bar();
			cout << " операция : ";
			c = get_Operation();
			cout << c << endl;
			switch (c) 
			{
			case '0' : show_Availability(machine);
				break;
			case '1' : choose_Product(machine);
				break;
			};
		};
	};

	/***********************************************************/

	int main()
	{
		setlocale(LC_ALL, "");
		cout << " Ассортимент продуктов" << endl;
		show_Assortment();

		Vending* machine = Vending_Installation();
		cout << " Машина готова к использованию" << endl;

		start_Usage(machine);

		return 0;
	};

	/***********************************************************/