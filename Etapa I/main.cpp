#include <iostream>
#include <cstring>
#include <ctime>
#include <new>
using namespace std;

//--------------------------------------------------------CLASA PRODUS----------------------------------------------------------
class Product
{
private:
    char *Product_name;
    double price;
    char *category;
    int stock;
    int totalStars;
    int numReviews;

public:
    // Constructor fara parametri
    Product();
    // Constructor cu parametri
    Product(const char *name, double price, const char *cat, int stock);
    // Constructor de copiere, o sa am nevoie de el la OVERLOADAREA "=" din ShoppingCart
    Product(const Product &other);

    // Destructor
    ~Product();

    // Getters
    char *getName() const;
    double getPrice() const;
    char *getCategory() const;
    int getStock() const;

    // Setters
    void setStock(int stock);
    void setPrice(double price);

    // Review functions
    void addReview(int stars);
    double getAverageRating() const;

    // Another methods:
    void increase_stock(int quantity); // cu aceasta motoda administratorul magazinului poate schimba stocul disponibil
    void decrease_stock(int quantity); // voi apela metoda asta atunci cand o comanda este plasata cu succes, pentru ca restul utilizatorilor sa stie in timp real daca produsul pe care vor sa-l achizitioneze mai este disponibil sau nu.

    // Operator overloading
    friend ostream &operator<<(ostream &os, const Product &product);
    Product &operator=(const Product& other)
    {
        if(this==&other)
        {
            return *this;
        }
        delete[] Product_name;
        Product_name= new char[strlen(other.Product_name)+1];
        strcpy(Product_name, other.Product_name);
        price=other.price;

        delete[] category;
        category= new char[strlen(other.category)+1];
        strcpy(category,other.category);

        stock=other.stock;
        totalStars=other.totalStars;
        numReviews=other.numReviews;
        return *this;
    }
};
//-------------------------------------------DEFINIREA METODELOR PENTRU CLASA PRODUS--------------------------------------------
// Constructor()
Product::Product() : Product_name(nullptr), price(0.0), category(nullptr), stock(0), totalStars(0), numReviews(0) {}
// Constructor(parameters)
Product::Product(const char *name, double price, const char *cat, int stock) : price(price), stock(stock), totalStars(0), numReviews(0)
{
    // Allocate memory for name and category and copy the input strings
    this->Product_name = new char[strlen(name) + 1];
    strcpy(this->Product_name, name);

    this->category = new char[strlen(cat) + 1];
    strcpy(this->category, cat);
}
// Copy Constructor
Product::Product(const Product &other)
{
    Product_name = new char[strlen(other.Product_name) + 1];
    strcpy(Product_name, other.Product_name);
    price = other.price;
    category = new char[strlen(other.category) + 1];
    strcpy(category, other.category);
    stock = other.stock;
    totalStars = other.totalStars;
    numReviews = other.numReviews;
}
// Destructor
Product::~Product()
{
    // Deallocate memory for name and category
     delete[] Product_name;
     delete[] category;
    
}

/// GETTERS
char *Product::getName() const
{
    return Product_name;
}
double Product::getPrice() const
{
    return price;
}
char *Product::getCategory() const
{
    return category;
}
int Product::getStock() const
{
    return stock;
}

/// SETTERS
void Product::setStock(int stock)
{
    this->stock = stock;
}
void Product::decrease_stock(int quantity)
{
    stock -= quantity;
    setStock(stock);
}
void Product::increase_stock(int quantity)
{
    stock += quantity;
    setStock(stock);
}
void Product::setPrice(double price)
{
    this->price = price;
}
void Product::addReview(int stars)
{
    totalStars += stars;
    numReviews++;
}
double Product::getAverageRating() const
{
    if (numReviews == 0)
    {
        return 0.0;
    }
    else
    {
        return (double)totalStars / numReviews;
    }
}
ostream &operator<<(ostream &os, const Product &product)
{
    os << "Product name: " << product.Product_name << endl;
    os << "Category: " << product.category << endl;
    os << "Price: " << product.price << endl;
    if (product.getAverageRating() == 0.0)
    {
        cout << "Rating: There is no existent rating for this product" << endl;
    }
    else
        os << "Rating: " << product.getAverageRating() << " stars" << endl;
    os << "Stock: " << product.getStock() << endl;
    return os;
}

//------------------------------------------------------CLASA DATA------------------------------------------------------------------
class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date() { day = 0, month = 0, year = 0; }
    Date(int d, int m, int y) : day(d), month(m), year(y){};
    void setDay(int D)
    {
        day = D;
    }
    void setMonth(int M)
    {
        month = M;
    }
    void setYear(int Y)
    {
        year = Y;
    }
    int getDay()
    {
        return day;
    }
    int getMonth()
    {
        return month;
    }
    int getYear()
    {
        return year;
    }
    void setDate(int D, int M, int Y)
    {
        setDay(D);
        setMonth(M);
        setYear(Y);
    }
    void printDate()
    {
        cout << " '" << day << "-" << month << "-" << year << "' " << endl;
    }
    friend ostream &operator<<(ostream &os, const Date &date)
    {
        os << "'" << date.day << "-" << date.month << "-" << date.year << "'";
        return os;
    }
};

//------------------------------------------------------CLASA ORDER-----------------------------------------------------------------
class Order
{
private:
    int orderID;
    Date orderDate;
    bool status;
    double TotalAmount;
    int NumberOfProducts;
    char *PaymentMethod;
    char *ShippingAddress;

public:
    Order();
    void setShippingAddress(const char *addr);
    void setPaymentMethod(const char *paym);
    void setTotalAmount(const double sum);
    double cash_back_calculator(const double sum);
    double getTotalAmount();
    bool getStatus();
    bool submitOrder();
    void placeOrder();
    void viewOrderDetails();
};

//------------------------------------------------Definirea metodelor pentru clasa Order-------------------------------------------

Order::Order() : orderID(0), status(false), TotalAmount(0), NumberOfProducts(0), PaymentMethod(nullptr), ShippingAddress(nullptr) { orderDate.setDate(0, 0, 0); }
void Order::setShippingAddress(const char *addr)
{
    this->ShippingAddress = new char[strlen(addr) + 1];
    strcpy(this->ShippingAddress, addr);
}
void Order::setPaymentMethod(const char *paym)
{
    this->PaymentMethod = new char[strlen(paym) + 1];
    strcpy(this->PaymentMethod, paym);
}
void Order::setTotalAmount(const double sum)
{

    TotalAmount = sum - cash_back_calculator(sum);
}
double Order::cash_back_calculator(double sum)
{
    int i = 1;
    double back;
    while (sum > i * 1000)
        i++;
    back = sum * (double(i - 1) / 100);
    return back;
}
bool Order::submitOrder()
{
    orderID = rand();
    status = true;
    return true;
}
void Order::placeOrder()
{
    char s[500], p[500];
    cout << "Please, introduce the Shipping Address: " << endl;
    cin.getline(s, 500);
    setShippingAddress(s);
    cout << "Please, introduce the Payment Method: " << endl;
    cin.getline(p, 500);
    setPaymentMethod(p);

    time_t t = time(NULL);
    tm *timePtr = localtime(&t);
    orderDate.setDate(timePtr->tm_mday, timePtr->tm_mon + 1, timePtr->tm_year + 1900);
    submitOrder();

    if (status == true)
    {
        cout << "Your order was successfully submitted!" << endl;
        viewOrderDetails();
    }
}
void Order::viewOrderDetails()
{
    cout << "OrderID: " << orderID << endl;
    cout << "Date: " << orderDate << endl;
    cout << "Payment Method: " << PaymentMethod << endl;
    cout << "Shipping Address: " << ShippingAddress << endl;
}
bool Order::getStatus()
{
    return status;
}
double Order::getTotalAmount()
{
    return TotalAmount;
}

//----------------------------------------------------CLASA SHOPPING CART----------------------------------------------------------
class ShoppingCart
{
private:
    Product **products; // Pointer to dynamic array of pointers to Product Objects
    int numProducts;    // Number of unique products in the cart
    int capacity;
    int *quantities; // Array of quantities
    double total_price;
    bool purchased;
    Order order;

public:
    // Constructor()
    ShoppingCart();
    // Copy Constructor
    ShoppingCart(const ShoppingCart &other);
    // Destructor
    ~ShoppingCart();

    // Getters & Setters
    double getTotalPrice();
    int getnumProducts();
    void setTotalPrice();
    void setnumProducts();

    void addProduct(const Product &product, int quantity = 1);
    void removeProduct(int index, int quantity = 1);
    void displayCartInfo();
    void make_purchase();

    ShoppingCart &operator=(const ShoppingCart &other)
    {
        if (this == &other)
            return *this;

        for (int i = 0; i < numProducts; i++)
            delete products[i];
        delete[] products;
        delete[] quantities;

        numProducts = other.numProducts;
        capacity = other.capacity;
        total_price = other.total_price;
        purchased = other.purchased;
        order = other.order;
        products = new Product *[capacity];
        quantities = new int[capacity];
        for (int i = 0; i < numProducts; i++)
        {
            products[i] = new Product(*(other.products[i]));
            quantities[i] = other.quantities[i];
        }

        return *this;
    }
};

//-------------------------------------------------DEFINIREA METODELOR PENTRU SHOPPING CART---------------------------------------

// Constructor()
ShoppingCart::ShoppingCart()
{
    numProducts = 0;
    total_price = 0;
    capacity = 50;
    purchased = false;
    products = new Product *[capacity]; // allocate memory for the array of pointers
    quantities = new int[capacity];
}
// Copy Constructor
ShoppingCart::ShoppingCart(const ShoppingCart &other)
{
    numProducts = other.numProducts;
    total_price = other.total_price;
    purchased = other.purchased;
    capacity = other.capacity;
    purchased = other.purchased;
    order = other.order;
    products = new Product *[capacity];
    quantities = new int[capacity];
    for (int i = 0; i < numProducts; i++)
    {
        products[i] = new Product(*(other.products[i]));
        quantities[i] = other.quantities[i];
    }
}
// Destructor
ShoppingCart::~ShoppingCart()
{
    for (int i = 0; i < numProducts; i++)
        delete products[i]; // delete each Product object pointer
    delete[] products;      // Deallocate the array of pointers
    delete[] quantities;
}

// Setters & Getters
void ShoppingCart::setTotalPrice()
{
    total_price = 0;
}
void ShoppingCart::setnumProducts()
{
    numProducts = 0;
}
int ShoppingCart::getnumProducts()
{
    return numProducts;
}
double ShoppingCart::getTotalPrice()
{
    double TotalPrice = 0;
    for (int i = 0; i < numProducts; i++)
        TotalPrice += (products[i]->getPrice()) * quantities[i];
    return TotalPrice;
}

void ShoppingCart::addProduct( const Product &product, int quantity)
{
    if (product.getStock() >= quantity)
    {
        int poz = -1;
        for (int i = 0; i < numProducts; i++)
        {
            if (strcmp(products[i]->getName(), product.getName()) == 0)
            {
                poz = i;
                break;
            }
        }
        if (poz >= 0)
            quantities[poz] += quantity;
        else
        {
            if (numProducts == capacity)
            {
                capacity *= 2;
                Product **new_products = new Product *[capacity];
                int *new_quantities = new int[capacity];
                for (int i = 0; i < numProducts; i++)
                {
                    new_products[i] = products[i];
                    new_quantities[i] = quantities[i];
                }
                delete[] products;
                delete[] quantities;
                products = new_products;
                quantities = new_quantities;
            }
            products[numProducts] = new Product(product);
            quantities[numProducts] = quantity;
            numProducts++;
        }
    }
    else
        cout << "Current stock: " << product.getStock() << ". Introduce a smaller quantity!" << endl;
}
void ShoppingCart::removeProduct(int index, int quantity)
{
    if (index >= 1 && index <= numProducts)
    {
        if (quantities[index - 1] == quantity)
        {
            delete products[index-1];
            for (int i = index - 1; i < numProducts - 1; i++)
            {
                products[i] = products[i + 1];
                quantities[i] = quantities[i + 1];
            }
            numProducts--;
        }
        else
        {
            if (quantities[index - 1] > quantity)
            {
                quantities[index-1] = quantities[index-1]-quantity;
            }
            else
            cout << "Invalid quantity!" << endl;
        }
    }
    else
        cout << "Invalid index, product not found :( " << endl;
}
void ShoppingCart::displayCartInfo()
{
    if (numProducts == 0)
    {
        cout << "Your Shopping Cart is empty." << endl;
        return;
    }
    else
    {
        cout << "Your Shopping Cart: " << endl;
        for (int i = 0; i < numProducts; i++)
        {
            cout << "Item " << i + 1 << " : Name: " << products[i]->getName() << ". Price: " << products[i]->getPrice() << ". Quantity: " << quantities[i] << endl;
        }
        cout << "Number of products: " << numProducts << endl;
        cout << "Total Price: " << getTotalPrice() << endl;
    }
}
void ShoppingCart::make_purchase()
{
    order.placeOrder();
    if (order.getStatus() == true)
    {
        order.setTotalAmount(getTotalPrice());
        double sum;
        sum = order.getTotalAmount();
        purchased = true;
        cout << "Total price: " << getTotalPrice() << endl;
        cout << "Total amount with cashback applied: " << sum << endl;
        cout << "Number of items from your order: " << getnumProducts() << endl;

        for (int i = 0; i < numProducts; i++)
        {
            cout << "Product nr. " << i + 1 << ": " << products[i]->getName() << ". Quantity: " << quantities[i] << endl;
            products[i]->decrease_stock(quantities[i]);
            cout << "Stock after purchase: " << products[i]->getStock() << endl;
            quantities[i]=0;
            delete products[i];
        }
        setnumProducts();
        setTotalPrice();
    }
    else
        purchased = false;
}

//-----------------------------------------------------------------CLASA USER---------------------------------------------------------------------------------------
class User
{
private:
    char username[50];
    char password[50];
    char email[50];
    char address[100];
    bool is_registered;
    bool is_loggedin;
    ShoppingCart cart;
    Order o;

    void setUsername(const char *Username);
    void setPassword(const char *Password);
    void setEmail(const char *Email);

public:
    /// Constructor()
    User();
    /// Constructor(parameters)
    User(const char *Username, const char *Password, const char *Email, const char *Address);

    /// Getters & setters
    const char *getUsername() const;
    const char *getPassword() const;
    const char *getEmail() const;
    const char *getAddress() const;
    void setAddress(const char *Address);
    void setCart(ShoppingCart Cart);

    /// Other Methods
    bool login(const char *Username, const char *Password);
    bool registration(const char *Username, const char *Password, const char *Email, const char *Address);
    void print_user_information() const;
    void account_settings(const char *OldUsername, const char *OldPassword, const char *OldEmail, const char *NewUsername, const char *NewPassword, const char *NewEmail);
    void view_Cart();
    void order();
};

/// ---------------------------------------------Definirea metodelor pentru clasa USER----------------------------

/// Constructor():
User::User()
{
    is_registered = false;
    is_loggedin = false;
};
/// Constructor(parameters)
User::User(const char *Username, const char *Password, const char *Email, const char *Address)
    : is_registered(true), is_loggedin(true)
{
    strcpy(username, Username);
    strcpy(password, Password);
    strcpy(email, Email);
    strcpy(address, Address);
}

// Getters and setters:
const char *User::getUsername() const
{
    return username;
}
const char *User::getPassword() const
{
    return password;
}
const char *User::getAddress() const
{
    return address;
}
const char *User::getEmail() const
{
    return email;
}
void User::setAddress(const char *Address)
{
    strcpy(address, Address);
}
void User::setUsername(const char *Username)
{
    strcpy(username, Username);
}
void User::setPassword(const char *Password)
{
    strcpy(password, Password);
}
void User::setEmail(const char *Email)
{
    strcpy(email, Email);
}
void User::setCart(ShoppingCart Cart)
{
    cart = Cart;
}

// METHODS
bool User::registration(const char *Username, const char *Password, const char *Email, const char *Address)
{
    // Check if the user is already registered
    if (is_registered == true)
    {
        cout << "User is already registered" << endl;
        return false;
    }

    //
    if (strlen(Username) == 0 || strlen(Password) == 0 || strlen(Email) == 0 || strlen(Address) == 0)
    {
        cout << "Invalid input! It is mandatory to complete all required fields." << endl;
        return false;
    }

    // Update user information
    strcpy(username, Username);
    strcpy(password, Password);
    strcpy(email, Email);
    strcpy(address, Address);
    is_registered = true;
    cout << "You have successfully registered!" << endl;
    return true;
}
bool User::login(const char *Username, const char *Password)
{
    // Check if the user is registered
    if (!is_registered)
    {
        cout << "User is not registered" << endl;
        return false;
    }

    // Check if the username and password match with an existing one
    if (strcmp(Username, username) == 0 && strcmp(Password, password) == 0)
    {
        cout << "You have successfully logged in!" << endl;
        is_loggedin = true;
        return true;
    }
    else
    {
        cout << "Invalid username or password" << endl;
        is_loggedin = false;
        return false;
    }
}
void User::print_user_information() const
{
    cout << "YOUR ACCOUNT INFO: " << endl;
    cout << "Username: " << getUsername() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Password: " << getPassword() << endl;
    cout << "Registered Address: " << getAddress() << endl;
}
void User::account_settings(const char *OldUsername, const char *OldPassword, const char *OldEmail, const char *NewUsername, const char *NewPassword, const char *NewEmail)
{
    if (strcmp(username, OldUsername) == 0 && strcmp(email, OldEmail) == 0 && strcmp(password, OldPassword) == 0)
    {

        setUsername(NewUsername);
        setEmail(NewEmail);
        setPassword(NewPassword);
        is_loggedin = true;
    }
    else
    {
        cout << "Invalid username, email or password!";
    }
}
void User::view_Cart()
{
    if (is_loggedin == true)
    {
        cart.displayCartInfo();
    }
    else
        cout << "To see your Shopping Cart you need to register, or log-in in case you already have an account!" << endl;
}
void User::order()
{
    if (is_loggedin == true)
    {   if(cart.getnumProducts()!=0)
            cart.make_purchase();
        else
            {
                cout<<"Your cart is empty. There is nothing to purchase.";
                return;
            }
    }
    else
    {
        cout << "To order, you have to register, or log-in in case you already have an account!" << endl;
    }
}

int main()
{
    //------------------------------------------------DEFINESC PRODUSE-----------------------------------------------
    Product P1("Lost Cherry", 200, "Tester", 2);
    Product P2("Invictus", 400, "Esenta", 10);
    Product P3("PureXS", 50, "Tester", 2);
    Product P4("Tresor", 500, "Parfum", 6);
    Product P5("La Vie est Belle", 300, "Parfum", 5);
    Product P6("Lavanda", 20, "Esenta", 15);
    Product P7("Soleil", 150, "Auto", 5);
    Product P8("Lemongrass", 10, "Auto", 12);
    Product P9("Encre Noire", 199, "Parfum", 3);
    Product P10("Euphoria", 100, "Tester", 4);
    Product P11("Arbore de ceai", 10, "Esenta", 7);
    Product P12("Eucalipt", 5, "Esenta", 20);
    Product P13("Pin", 13, "Auto", 5);
    Product P14("Strawberry", 3, "Auto", 2);
    Product P15("FloriAlbe", 75, "Casa", 6);
    P1.addReview(3), P1.addReview(5), P1.addReview(5), P1.addReview(5), P1.addReview(4);
    P2.addReview(2), P2.addReview(3), P2.addReview(1);
    P3.addReview(5), P3.addReview(4);
    P4.addReview(1), P4.addReview(5), P4.addReview(4);
    P7.addReview(5), P7.addReview(2);
    P8.addReview(2);
    P9.addReview(5);
    P10.addReview(4), P10.addReview(2);
    P13.addReview(4);
    P15.addReview(3), P15.addReview(3);
    cout << P1 << P6;

    //---------------------------------------------------DEFINESC CATIVA UTILIZATORI AI MAGAZINULUI:)--------------------------------
    User user1, user2, user3, user4, user5;
    user1.registration("ALEX", "1234", "alex@gmail.com", "Bucuresti, Sector 3, strada Eroilor");
    user2.registration("MARIA", "copaci", "maria@gmail.com", "Tg. Mures, strada Florilor");
    user3.registration("DIANA", "morcovi", "diana.dia@gmail.com", "Brasov, strada Temnitei");
    user4.registration("IOANA", "010203", "ioana.artist@gmail.com", "Prahova, strada Stejarilor");
    user5.registration("Ion", "pamant", "ion@gmail.com", "Galati, strada 1 Decembrie");

    //---------------------------------------------------DEFINESC SI CATEVA CART-URI "FANTOMA"----------------------------------------

    ShoppingCart C1, C2, C3, C4, C5;
    C1.addProduct(P3,2);
    C2.addProduct(P7,3);
    ///----------------------------------------------------
    C3.addProduct(P6, 2);
    C3.addProduct(P11, 4);
    C3.addProduct(P13, 2);
    C3.removeProduct(1, 2);
    C3.displayCartInfo();
    C3.removeProduct(2);
    C3.removeProduct(3);
    C3.displayCartInfo();
    ///---------------------------------------------------- 
    
    C4.addProduct(P15,3);
    C5.addProduct(P1);
    cout<<"Cosul1: "<<endl;
    C1.displayCartInfo();
    cout<<"Cosul2: "<<endl;
    C2.displayCartInfo();
    cout<<"Cosul3: "<<endl;
    C3.displayCartInfo();
    cout<<"Cosul4: "<<endl;
    C4.displayCartInfo();
    cout<<"Cosul5: "<<endl;
    C5.displayCartInfo();
    
    //------------------------------------SIMULATING THE EXPERIENCE OF ONLINE SHOPPING-------------
     cout<<endl<<endl<<endl;
     User someone;
     //someone.setCart(C3);
     someone.order(); //here, the program prints an error message, because the user cannot order if he is not registered or logged-in
     cout<<endl;
     someone.registration("GHOST", "ghost", "ghost@gmail.com", "NowhereCity");
     cout<<endl;
     someone.order();  //After registration, the user still has to login
     someone.login("GHOST","1234");  //error message - invalid password
     cout<<endl;
     someone.login("GHOST","ghost");
     someone.print_user_information();
     cout<<endl;
     //someone.order();
     C3.addProduct(P2,5);
     C3.displayCartInfo();
     someone.setCart(C3); //Here C3 has a bigger Total_Price and the cashback method comes in handy
     someone.order();
    someone.account_settings("GHOST", "ghost","ghost@gmail.com", "G","G","g@gmail.com");
    someone.print_user_information();
    return 0;
}
