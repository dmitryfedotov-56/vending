	#pragma once
	/***********************************************************/
	/*                           User Inerface                 */
	/***********************************************************/

	class Product;
	class Vending;

	void product_Availability(const Vending* machine);

	Product* buy_Product(Vending* machine, Product_Code code);

	/***********************************************************/

