	#pragma once
	/***********************************************************/
	/*                    Maintanance Inerface                 */
	/***********************************************************/

	class Price
	{
	public:
		long value = 0;
		Price() {};
		const char* to_String();
		Price(long price_value) : value(price_value) {};
	};

	ostream& operator << (ostream& output, const Price& price);

	/***********************************************************/
	/*                     Product Assortment                  */
	/***********************************************************/

	enum class Product_Code { Mars, Snickers, Bounty } ;

	#define NUMPRODUCTS 3

	struct { Product_Code code; const char* name; Price price; }
	assortment[NUMPRODUCTS] =
	{
		{ Product_Code::Mars,		"Mars",		Price(120)},
		{ Product_Code::Snickers,	"Snikers",  Price(150)},
		{ Product_Code::Bounty,		"Bounty",	Price(210)}
	};

	/***********************************************************/
	/*                       Vending Actions                   */
	/***********************************************************/

	class Slot;
	class Product;
	class Vending;

	Vending* new_Vending(short positions);	// get a new vending for several slots

	short vending_Ñapacity(Vending* machine);		// get the number of slots

	short free_Slots(Vending* machine);				// free slot positions

	short free_Positions(Vending* machine);			// free product positions
	
	void add_Slot(Vending* machine, Slot* slot);	// insert a new slot
	
	Slot* get_Slot(Vending* machine, short number);			// get slot access (nullptr!)

	short* product_Availability(Vending* machine);	// get product avalability

	/***********************************************************/
	/*                       Slot Actions                      */
	/***********************************************************/

	Slot* new_Slot(short positions);		// get a new slot for several positions

	short slot_Capacity(Slot* slot);						// slot capacity

	void add_Product(Slot* slot, Product* product);			// add product

	short free_Positions(Slot* slot);						// slot free product positions

	/***********************************************************/
	/*                      Product Actions                    */
	/***********************************************************/

	Product* new_Product(Product_Code code);				// get a new product

	/***********************************************************/
