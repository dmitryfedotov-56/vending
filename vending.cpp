	/***********************************************************/
	/*                           Vending	 	               */
	/***********************************************************/

	#define _CRT_SECURE_NO_WARNINGS

	#include <iostream>
	#include <stdio.h>

	using namespace std;

	#include "vending_mgt.h"		// management interface
	#include "vending_user.h"		// vending user interface

	#include "vending.h"			// class description

	/***********************************************************/

	ostream& operator << (ostream& output, const Price &price) 
	{
		output << price.value / 100 << '.' << price.value % 100;
		return output;
	};

	/***********************************************************/

	#define BUFFSIZE 12

	static char buffer[BUFFSIZE];

	const char* Price::to_String() 
	{
		short n;
		n = sprintf(buffer, "%d", value / 100);
		buffer[n] = '.';
		sprintf(&buffer[n+1], "%d", value % 100);
		return buffer;
	};
	
	/***********************************************************/
	/*                         Product                         */
	/***********************************************************/
	
	const Product_Code Product::get_Code() { return code; }

	const char* Product::get_Name() { return assortment[(short)code].name; }

	const Price Product::get_Price() { return assortment[(short)code].price;  };

	Product::Product(const Product_Code product_code) : code(product_code) {};

	/***********************************************************/
	/*                      Product Actions                    */
	/***********************************************************/

	Product* new_Product(Product_Code code) { return new Product(code); };

	void add_Product(Slot* slot, Product* product) { slot -> add_Product(product); };

	/***********************************************************/
	/*                         Slot                            */
	/***********************************************************/

	short Slot::free_Positions() { return free_positions; };

	short Slot::get_Capacity() { return numb_positions; };

	void Slot::add_Product(Product* product) 			// add product (may fail!)
	{
		Product_Code code;
		for (short i = 0; i < numb_positions; i++) 
		{
			if (products[i] == nullptr)					// empty position?
			{
				products[i] = product;					// put product
				code = product-> get_Code();			// product code
				(availability[(short)code])++;			// increase availability
				free_positions--;
				used_positions++;
				return;
			};
		};
	};

	/***********************************************************/

	Product* Slot::get_Product(Product_Code code)		// get product (may return nullptr!)
	{
		Product* product;
		for (short i = 0; i < numb_positions; i++)
		{
			if (products[i] != nullptr)					// not an empty position?
			{
				product = products[i];
				if (product-> get_Code() == code)		// required code?
				{
					products[i] = nullptr;
					(availability[(short)code])--;		// decrease availability
					free_positions++;
					used_positions--;					
					return product;
				};
			};
		};
		return nullptr;
	};

	/***********************************************************/

	short* Slot::product_Availability() { return availability; };
	
	Slot::Slot(short max_positions): numb_positions(max_positions)
	{
		products = new Product * [numb_positions] {nullptr};
		free_positions = numb_positions;
		used_positions = 0;
	};

	Slot::~Slot() { delete [] products; };

	/***********************************************************/
	/*                       Slot Actions                      */
	/***********************************************************/

	Slot* new_Slot(short positions) { return new Slot(positions); };

	short slot_Capacity(Slot* slot) { return slot->get_Capacity(); };

	void add_Slot(Vending* machine, Slot* slot) { machine-> add_Slot(slot); };

	Slot* get_Slot(Vending* machine, short number) { return machine-> get_Slot(number); };

	short free_Positions(Slot* slot) { return slot->free_Positions(); };

 	/***********************************************************/
	/*                       Vending                           */
	/***********************************************************/

	short Vending::get_Capacity() { return numb_slots; };		// number of slots

	short Vending::free_Slots() { return free_slots; };		// number of free slots

	short* Vending::product_Availability() { return availability; };

	Slot* Vending::get_Slot(short number)		// get slot access (may return nullptr!)
	{
		if (number >= used_slots)return nullptr;
		return slots[number];
	};

	/***********************************************************/

	short Vending::free_Positions()		// total number of machine free product positions
	{
		short positions = 0;
		for (short i = 0; i < used_slots; i++)
		{
			positions += slots[i]->free_Positions();
		};
		return positions;
	};

	/***********************************************************/

	Product* Vending::get_Product(Product_Code code)
	{
		Product* product;
		Slot* slot;
		short* slot_availability;

		if (availability[(short)code] == 0)return nullptr;	// that should be an error!

		for (short i = 0; i < used_slots; i++)	// look for a siutable slot
		{
			slot = slots[i];
			slot_availability = slot-> product_Availability();
			if (availability[(short)code] != 0)
			{
				product = slot-> get_Product(code);
				(availability[(short)code])--;
				return product;
			};
		};
		return nullptr;
	};

	/***********************************************************/

	void Vending::add_Slot(Slot* slot)				// add slot (may fail!)
	{
		if (used_slots == numb_slots)return;		// that should be an error!
		slots[used_slots] = slot;
		used_slots++;
		free_slots--;
		short* slot_availability = slot-> product_Availability();
		for (short i = 0; i < NUMPRODUCTS; i++)
		{
			availability[i] += slot_availability[i];
		};
	};

	/***********************************************************/

	Vending::Vending(short max_slots) : numb_slots(max_slots) 
	{
		slots = new Slot * [max_slots] { nullptr };
		free_slots = numb_slots;
		used_slots = 0;
	};	

	Vending::~Vending() { delete[] slots; };

	/***********************************************************/
	/*                     Vending Actions                     */
	/***********************************************************/

	Vending* new_Vending(short positions) { return new Vending(positions); };

	short vending_Ñapacity(Vending* machine) { return machine->get_Capacity(); };

	short free_Slots(Vending* machine) { return machine->free_Slots(); };

	short free_Positions(Vending* machine) { return machine->free_Positions(); };

	short* product_Availability(Vending* machine)
	{
		return machine-> product_Availability();
	};

	Product* buy_Product(Vending* machine, Product_Code code) 
	{
		return machine-> get_Product(code);
	};

	/***********************************************************/

	

