#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// class Item;
// class Cart;
class Product
{
    int id;
    string name;
    int price;

public:
    Product()
    {
    }
    Product(int u_id, string name, int price)
    {
        id = u_id;
        this->name = name;
        this->price = price;
    }
    string getdisplayname()
    {
        return name + " : Rs " + to_string(price) + "\n";
    }

    string getshortname()
    {
        return name.substr(0, 1);
    }

    friend class Item;
    friend class Cart;
};

class Item
{
    Product product;
    int quantity;

public:
    Item()
    {
    }
    Item(Product p, int q) : product(p), quantity(q) {} // initialistion list

    int getItemprice()
    {
        return quantity * product.price;
    }

    string getItemInfo()
    {
        return to_string(quantity) + " x " + product.name + " RS" + to_string(quantity * product.price);
    }
    friend class Cart;
};
class Cart
{
    unordered_map<int, Item> items;

public:
    void addproduct(Product product)
    {
        if (items.count(product.id) == 0)
        {
            Item newitem(product, 1);
            items[product.id] = newitem;
        }
        else
        {
            items[product.id].quantity += 1;
        }
    }
    int gettotal()
    {
        int total = 0;
        for (auto itempair : items)
        {
            auto item = itempair.second;
            // itemizedlist.append(item.getItemInfo());
            total += item.getItemprice();
        }
        return total;
    }
    string viewcart()
    {
        if (items.empty())
        {
            return "cart is empty";
        }
        string itemizedlist;
        int cart_total = gettotal();
        for (auto itempair : items)
        {
            auto Items = itempair.second;
            itemizedlist.append(Items.getItemInfo());
        }
        return itemizedlist + "\n Total Amount : RS. " + to_string(cart_total) + '\n';
    }
    bool isempty()
    {
        return items.empty();
    }
};

vector<Product> allproduct = {
    Product(1, "apple", 26),
    Product(3, "mango", 16),
    Product(2, "guava", 36),
    Product(5, "banana", 56),
    Product(4, "strawberry", 29),
    Product(6, "pineapple", 20),

};

Product *chooseProduct()
{
    string productlist;
    cout << "Available products " << endl;
    for (auto product : allproduct)
    {
        productlist.append(product.getdisplayname());
    }
    cout << productlist << endl;

    cout << "------------" << endl;
    string choice;
    cin >> choice;

    for (int i = 0; i < allproduct.size(); i++)
    {
        if (allproduct[i].getshortname() == choice)
        {
            return &allproduct[i];
        }
    }
    cout << "product not found " << endl;
    return NULL;
}
bool checkout(Cart &cart)
{
    if (cart.isempty())
    {
        return false;
    }

    int total = cart.gettotal();
    cout << "Pay in cash ";

    int paid;
    cin >> paid;
    if (paid >= total)
    {
        cout << "Change " << paid - total << endl;
        cout << "Thank u for shopping with us ! ";
        return true;
    }
    else
    {
        cout << "Not enough cash!";
        return false;
    }
}

int main()
{
    char action;
    Cart cart;
    while (true)
    {
        cout << "select an action - (a)dd item, (v)iew cart , (c)heckout" << endl;
        cin >> action;

        if (action == 'a')
        {
            // todo add to cart
            // view all products+ choose product+add to the cart
            Product *product = chooseProduct();
            {
                if (product != NULL)
                {
                    cout << "added to the cart " << product->getdisplayname() << endl;
                    cart.addproduct(*product);
                    // todo
                }
            }
        }
        else if (action == 'v')
        {
            // // view the cart

            cout << "--------" << endl;
            cout << cart.viewcart();
            cout << "--------" << endl;
        }
        else
        {
            // checkout
            cart.viewcart();
            if (checkout(cart))
            {
                break;
            }
        }
    }
    return 0;
}