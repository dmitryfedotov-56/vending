	#pragma once
	/***********************************************************/
	/*                  Vending class description	           */
	/***********************************************************/

	/***********************************************************/
	/*                         Product                         */
	/***********************************************************/

	class Product
	{
	public:
		const char* get_Name();			// product name

		const Product_Code get_Code();		// product code

		const Price get_Price();			// product price

		Product(const Product_Code code);	// constructor

	private:
		const Product_Code code;
	};

	/***********************************************************/
	/*                         Slot                            */
	/***********************************************************/

	class Slot
	{
	public:

		short get_Capacity();

		short free_Positions();

		void add_Product(Product* product);			// add product (may fail!)

		Product* get_Product(Product_Code code);	// get product (may return nullptr!)

		short* product_Availability();				// product availability

		Slot(short positions);
		~Slot();

	private:

		const short numb_positions;					// number of product positions

		short free_positions;						// number of free positions

		short used_positions;						// number of used positions

		Product** products;							// available products

		short availability[NUMPRODUCTS]{ 0 };			// product availability
	};

	/***********************************************************/
	/*                         Vending                         */
	/***********************************************************/

	class Vending
	{
	public:

		short get_Capacity();						// number of slots

		short free_Slots();							// number of free slots

		Slot* get_Slot(short number);				// get slot access (may return nullptr!)

		void add_Slot(Slot* slot);					// add a new slot (may fail!)

		Product* get_Product(Product_Code code);	// get product (may return nullptr!)

		short free_Positions();						// free product positions

		short* product_Availability();				// product availability

		Vending(short positions);					// constructor

		~Vending();									// destructor

	private:

		const short numb_slots;						// number of slots

		short free_slots;							// free slots

		short used_slots;							// used slots

		Slot** slots;								// available slots

		short availability[NUMPRODUCTS]{ 0 };		// product availability
	};

	/***********************************************************/

