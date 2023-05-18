#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<tuple>
#include<memory>
#include <chrono>
#include <new>
#include <stdexcept>
#include<algorithm>
#include <random>
#include<cstdlib>


using namespace std;
void clearConsole()
{
    cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear console screen

    // Clear the cin input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//--------------------------------------------------------------------------------DATE CLASS---------------------------------------------------------------------------------
class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);
    void setDay(int D);
    void setMonth(int M);
    void setYear(int Y);
    int getDay();
    int getMonth();
    int getYear();
    void setDate(int D, int M, int Y);
    void printDate();

    friend ostream &operator<<(ostream &os, const Date &date)
    {
        os << "'" << date.day << "-" << date.month << "-" << date.year << "'";
        return os;
    }
};
Date::Date() { day = 0, month = 0, year = 0; }
Date::Date(int d, int m, int y) : day(d), month(m), year(y){};
void Date::setDay(int D)
{
    day = D;
}
void Date::setMonth(int M)
{
    month = M;
}
void Date::setYear(int Y)
{
    year = Y;
}
int Date::getDay()
{
    return day;
}
int Date::getMonth()
{
    return month;
}
int Date::getYear()
{
    return year;
}
void Date::setDate(int D, int M, int Y)
{
    setDay(D);
    setMonth(M);
    setYear(Y);
}
void Date::printDate()
{
    cout << " '" << day << "-" << month << "-" << year << "' " << endl;
}
//---------------------------------------------------------------------------SALE - ABSTRACT CLASS---------------------------------------------------------------------------
class Sale
{
protected:
    string sale_name;
    Date start_date;
    Date end_date;
    double discount_percentage;

public:
    Sale();
    Sale(string sale_name, Date start_date, Date end_date, double discount_percentage);
    virtual double applyDiscount() const = 0;
    virtual void display_sale_details() const;
    virtual void promotion_availability() const;
    string get_sale_name() const;
    double getDiscountPercentage() const;
    void set_discount_percentage(double discount_percentage);
    virtual ~Sale(){};
};
Sale::Sale() {}
Sale::Sale(string sale_name, Date start_date, Date end_date, double discount_percentage)
    : sale_name(sale_name), start_date(start_date), end_date(end_date), discount_percentage(discount_percentage) {}
void Sale::display_sale_details() const
{
    cout << get_sale_name() << endl;
    cout << "Discounts are up to " << getDiscountPercentage() << "%"
         << " on selected products" << endl;
    promotion_availability();
}
void Sale::promotion_availability() const
{
    cout << "The promotion is available from: " << start_date << " to " << end_date << "." << endl;
}
string Sale::get_sale_name() const { return this->sale_name; }
double Sale::getDiscountPercentage() const { return this->discount_percentage; }
void Sale::set_discount_percentage(double discount_percentage) { this->discount_percentage = discount_percentage; }

//------------------------------------------------------------------------------REVIEW CLASS---------------------------------------------------------------------------------
class Review
{
private:
    string comment;
    int rating;

public:
    Review();
    Review(string comment, int rating);
    string get_comment() const;
    int get_rating() const;
    void set_comment(string comment);
    void set_rating(int rating);
    const void show_review() const;
};
Review::Review() : comment(""), rating(0.0) {}
Review::Review(string comment, int rating)
{
    this->comment = comment;
    this->rating = rating;
}
string Review::get_comment() const { return this->comment; }
int Review::get_rating() const { return this->rating; }
void Review::set_comment(string comment) { this->comment = comment; }
void Review::set_rating(int rating) { this->rating = rating; }
const void Review::show_review() const { cout << "Comment: " << get_comment() << " "
                                              << "Rating: " << get_rating() << endl; }
//-----------------------------------------------------------------------------PRODUCT CLASS----------------------------------------------------------------------------------
class Product
{
protected:
    string name;
    double price;
    int stock;
    vector<Review> reviews;
    double rating;

public:
    Product();
    Product(const string &name, double price, int stock);
    virtual ~Product() {}
    // Getters & Setters
    const string &get_name() const;
    virtual const double get_price() const;
    const int get_stock() const;
    void set_name(const string &new_name);
    void set_stock(int new_stock);
   
    // Methods
    void increase_stock(int new_stock);
    void decrease_stock(int old_stock);
    void addReview(const Review &review);
    const void show_reviews() const;
    double getAverageRating() const;
    // Virtual methods
    virtual void show_details() const;
     virtual void set_price(double new_price);
};
Product::Product() : name(" "), price(0), stock(0), rating(0) {}
Product::Product(const string &name, double price, int stock) : name(name), price(price), stock(stock) {}
const string &Product::get_name() const { return this->name; }
const double Product::get_price() const { return this->price; }
const int Product::get_stock() const { return this->stock; }
void Product::set_name(const string &new_name) { name = new_name; }
void Product::set_price(double new_price) { price = new_price; }
void Product::set_stock(int new_stock) { stock = new_stock; }
void Product::increase_stock(int new_stock) { stock = stock + new_stock; }
void Product::decrease_stock(int old_stock) { stock = stock - old_stock; }
void Product::addReview(const Review &review)
{
    reviews.push_back(review);
}
const void Product::show_reviews() const
{
    if (!reviews.empty())
    {
        for (const auto &review : reviews)
        {
            review.show_review();
        }
    }
}
void Product::show_details() const
{
    cout << "Product name: " << get_name()<<endl;
    cout << "Price: " << get_price()<<endl;
    cout << "Stock: " << get_stock()<<endl;
}
double Product::getAverageRating() const
{
    if (reviews.empty())
    {
        if (reviews.empty())
        {
            throw runtime_error("Cannot calculate average rating because there are no reviews available.");
        }
    }
    double sum = 0.0;
    for (const auto &review : reviews)
    {
        sum += review.get_rating();
    }
    return sum / reviews.size();
}
//-------------------------------------------------------------------------PRODUCT-ON-SALE CLASS--------------------------------------------------------------------------------
class ProductOnSale : public Sale, public Product
{
private:
    mutable double discount;
    mutable double new_price;

protected:
    double applyDiscount() const override;
    void set_price(double discount) const;

public:
    ProductOnSale();
    ProductOnSale(string sale_name, Date start_date, Date end_date, int discount_percentage, const string &name, double price, int stock);
    double get_new_price() const;
    void show_details() const override;
    virtual ~ProductOnSale() {}
};
ProductOnSale::ProductOnSale() : Sale(), Product(), discount(0), new_price(0) {}
ProductOnSale::ProductOnSale(string sale_name, Date start_date, Date end_date, int discount_percentage, const string &name, double price, int stock)
    : Sale(sale_name, start_date, end_date, discount_percentage), Product(name, price, stock), discount(discount), new_price(new_price) {}
void ProductOnSale::set_price(double discount) const
{
    if (discount > price)
    {
        throw invalid_argument("Discount cannot be greater than price");
    }
    new_price = price - discount;
}
double ProductOnSale::get_new_price() const
{
    applyDiscount();
    set_price(discount);
    return this->new_price;
}
double ProductOnSale::applyDiscount() const
{
    discount = price * discount_percentage / 100;
    return discount;
}
void ProductOnSale::show_details() const
{
    get_new_price();
    cout << "Product " << name << " is on sale." << endl;
    cout << "Old price: " << price << endl;
    cout << "New Price: " << new_price << endl;
    promotion_availability();
}
//-----------------------------------------------------------------------------PERFUME CLASS-------------------------------------------------------------------------------------------
class Perfume : public Product
{
private:
    string designer;
    string category;
    vector<string> fragrances;

public:
    Perfume();
    Perfume(const string &name, double price, int stock, const string &designer, const string &category, const vector<string> &fragrances);
    const string &get_designer() const;
    const string &get_category() const;
    const vector<string> &get_fragrances() const;
    void set_designer(const string &new_designer);
    void set_category(const string &new_category);
    void set_fragrances(const vector<string> &new_fragrances);
    void show_details() const override;
};
Perfume::Perfume() : Product(), designer(""), category("") {}
Perfume::Perfume(const string &name, double price, int stock, const string &designer, const string &category, const vector<string> &fragrances)
    : Product(name, price, stock), designer(designer), category(category), fragrances(fragrances) {}
const string &Perfume::get_designer() const { return designer; }
const string &Perfume::get_category() const { return category; }
const vector<string> &Perfume::get_fragrances() const { return fragrances; }
void Perfume::set_designer(const string &new_designer) { designer = new_designer; }
void Perfume::set_category(const string &new_category) { category = new_category; }
void Perfume::set_fragrances(const vector<string> &new_fragrances) { fragrances = new_fragrances; }
void Perfume::show_details() const
{
    cout << "Perfume name: " << name << endl;
    cout << "Perfume price: " << price << endl;
    cout << "Category: " << category << endl;
    cout << "Designer: " << designer << endl;
    cout << "Main Fragrances: ";
    for (const string &fragrance : fragrances)
    {
        cout << fragrance << " ";
    }
    cout << endl;
}
//---------------------------------------------------------------------------HOME SCENTS CLASS-----------------------------------------------------------------------------------
class HomeScents : public Product
{
private:
    string category;
    string scent_duration;
    string main_fragrance;

public:
    HomeScents();
    HomeScents(const string &name, double price, int stock, const string &category, const string &scent_duration, const string &main_fragrance);
    string getCategory() const;
    string get_scent_duration() const;
    string get_main_fragrance() const;
    void show_details() const override;
};
HomeScents::HomeScents() : Product(), category(""), scent_duration(""), main_fragrance("") {}
HomeScents::HomeScents(const string &name, double price, int stock, const string &category, const string &scent_duration, const string &main_fragrance) : Product(name, price, stock), category(category), scent_duration(scent_duration), main_fragrance(main_fragrance) {}
string HomeScents::getCategory() const { return this->category; }
string HomeScents::get_scent_duration() const { return this->scent_duration; }
string HomeScents::get_main_fragrance() const { return this->main_fragrance; }
void HomeScents::show_details() const
{
    cout << "Category: " << category << endl;
    cout << "Product name: " << name << endl;
    cout << "Fragrance: " << main_fragrance << endl;
    cout << "Price: " << price << endl;
}

//--------------------------------------------------------------------------AROMATHERAPY CLASS-----------------------------------------------------------------------------------
class Aromatherapy: public Product{
    string usage;
    string category;
    string main_fragrance;
    public:
    Aromatherapy();
    Aromatherapy(const string &name, double price, int stock, const string &usage, const string &category, const string &main_fragrance);
    string getCategory() const;
    string getUsage() const;
    string get_main_fragrance() const;
    void show_details() const override;
};
Aromatherapy::Aromatherapy(): Product(), usage(""),category(""),main_fragrance(""){}
Aromatherapy::Aromatherapy(const string &name, double price, int stock, const string &usage, const string &category, const string &main_fragrance): Product(name, price, stock), usage(usage), category(category), main_fragrance(main_fragrance){}
string Aromatherapy::getCategory() const {return category;}
string Aromatherapy::getUsage() const {return usage;}
string Aromatherapy::get_main_fragrance() const {return main_fragrance;}
void Aromatherapy::show_details() const{
    cout<<"Product Name: "<<name<<endl;
    cout<<"Category: "<<category<<endl;
    cout<<"Main Fragrance: "<<main_fragrance<<endl;
    cout<<"Usage: "<<usage<<endl;
}
//------------------------------------------------------------------------INTERFATA LIST_OF_PRODUCTS-----------------------------------------------------------------------------
class List_of_products
{
public:
    virtual void addProduct(const shared_ptr<Product>& product) = 0;
    virtual void removeProduct(const shared_ptr<Product>& product) = 0;
    virtual void displayProducts() = 0;
    virtual ~List_of_products(){};
};
//----------------------------------------------------------------------------EXCEPTIE CUSTOM----------------------------------------------------------------------------------
class OutOfStockException : public exception
{
public:
    const char *what() const throw()
    {
        return "Product is out of stock!";
    }
};
//--------------------------------------------------------------------------SHOPPING CART CLASS------------------------------------------------------------------------------------
class ShoppingCart : public List_of_products
{
private:
    vector<shared_ptr<Product>> products;
    double TotalPrice;

public:
    ShoppingCart();
    ShoppingCart(vector<shared_ptr<Product>> products);
    void addProduct(const shared_ptr<Product>& product) override;
    void removeProduct(const shared_ptr<Product>& product) override;
    void displayProducts() override;
    bool isEmpty() const;
    int getNumOfProducts() const;
    double set_TotalPrice();
    void empty();
    shared_ptr<Product>getProductbyIndex(int index) const;
};
ShoppingCart::ShoppingCart() : TotalPrice(0.0) {}
ShoppingCart::ShoppingCart(vector<shared_ptr<Product>> products) : products(products), TotalPrice(0.0) {}
void ShoppingCart::addProduct(const shared_ptr<Product>& product)
{
    if (product->get_stock() == 0)
    {
        throw OutOfStockException();
    }
    products.push_back(product);
}
void ShoppingCart::removeProduct(const shared_ptr<Product>& product)
{
    products.erase(remove(products.begin(), products.end(), product), products.end());
}
void ShoppingCart::displayProducts()
{
    if (!isEmpty())
    {
        cout << "Your cart contains:" << endl;
        for (int i = 0; i < products.size(); ++i) {
        cout << "Product nr: " << i + 1 << endl;
        products[i]->show_details();
        cout << endl;
        }
        TotalPrice = set_TotalPrice();
        cout << "TotalPrice: " << TotalPrice << endl;
    }
    else
        cout << "Your Shopping Cart is empty" << endl;
}
bool ShoppingCart::isEmpty() const
{
    return products.empty();
}

int ShoppingCart::getNumOfProducts() const
{
    return products.size();
}

double ShoppingCart::set_TotalPrice()
{
    TotalPrice = 0.0;
    for (const auto& product : products)
    {
        TotalPrice += product->get_price();
    }
    return TotalPrice;
}

void ShoppingCart::empty()
{
    for (const auto& product : products)
    {
        product->decrease_stock(1);
    }
    products.clear();
}
shared_ptr<Product> ShoppingCart::getProductbyIndex(int index) const {
    if (index >= 0 && index < products.size()) {
        return products[index];
    } else {
        return nullptr; // or throw an exception indicating invalid index
    }
}

//------------------------------------------------------------------------------WISHLIST CLASS------------------------------------------------------------------------------------
class Wishlist : public List_of_products
{
private:
    vector<shared_ptr<Product>> products;
    static const int MAX_PRODUCTS = 10;

public:
    Wishlist();
    Wishlist(const vector<shared_ptr<Product>>& products);
    void addProduct(const shared_ptr<Product>& product) override;
    void removeProduct(const shared_ptr<Product>& product) override;
    void displayProducts() override;
    bool isEmpty() const;
    int getNumOfProducts() const;
    shared_ptr<Product> getProductbyIndex(int index) const;
};
Wishlist::Wishlist() {}
Wishlist::Wishlist(const vector<shared_ptr<Product>>& products) : products(products) {}
bool Wishlist::isEmpty() const
{
    return products.empty();
}
int Wishlist::getNumOfProducts() const
{
    return products.size();
}
void Wishlist::addProduct(const shared_ptr<Product>& product)
{       if (products.size() < MAX_PRODUCTS) {
            products.push_back(product);
        } 
        else 
        {
            cout << "Wishlist is full" <<endl;
        }
}
void Wishlist::removeProduct(const shared_ptr<Product>& product)
{
     if (!isEmpty()) {
            auto it = find(products.begin(), products.end(), product);
            if (it != products.end()) {
                products.erase(it);
            }
        }
}
void Wishlist::displayProducts()
{
     if (!isEmpty()) 
        {
            cout << "Wishlist contains:" <<endl;
            for (int i = 0; i < products.size(); ++i) {
            cout << "Product nr: " << i + 1 << endl;
            products[i]->show_details();
            cout << endl;
        }
        } 
    else {
            cout << "Your Wishlist is empty" << endl;
        }
} 
shared_ptr<Product> Wishlist::getProductbyIndex(int index) const {
    if (index >= 0 && index < products.size()) {
        return products[index];
    } else {
        return nullptr; // or throw an exception indicating invalid index
    }
}
//-------------------------------------------------------------------------------USER CLASS---------------------------------------------------------------------------------------------
class User
{
private:
    static vector<User *> registered_users;
    string username;
    string password;
    string email;
    bool isLoggedIn;
    bool isRegistered;
    ShoppingCart *cart;
    Wishlist *wishlist;

public:
    User();
    User(string email, string username, string password);
    static bool registerUser(string email, string username, string password);
    static bool isUsernameUnique(string username);
    static vector<User *> getRegisteredUsers()
    {
        return registered_users;
    }
    bool logIn(const string &username, const string &password);
    void setShoppingCart(ShoppingCart *cart); 
    void setWishlist(Wishlist *wishlist);   
    void printUserInformation();
    void printCartDetails() const;
    ~User();
};
vector<User *> User::registered_users;
User::User() : isLoggedIn(false), isRegistered(false) {}
User::User(string email, string username, string password) : isRegistered(false), isLoggedIn(false), email(email), username(username), password(password) {}
bool User::registerUser(string Email, string Username, string Password)
{
    if (Email.length() == 0 || Username.length() == 0 || Password.length() == 0)
    {
        cout << "Invalid input! It is mandatory to complete all required fields." << endl;
        return false;
    }

    else
    {

        if (!isUsernameUnique(Username))
        {
            cout << "Username already taken. Please choose another username." << endl;
            return false;
        }
        User *user = new User(Email, Username, Password);
        registered_users.push_back(user);
        cout << "You have successfully registered!" << endl;
        return true;
    }
}
bool User::isUsernameUnique(string username)
{
    for (int i = 0; i < registered_users.size(); i++)
    {
        if (registered_users[i]->username == username)
            return false;
    }
    return true;
}
bool User::logIn(const string &username, const string &password)
{
    bool user_found = false;
    for (int i = 0; i < registered_users.size(); i++)
    {
        if (registered_users[i]->username == username && registered_users[i]->password == password)
        {
            cout << "You have successfully logged in!" << endl;
            isLoggedIn = true;
            user_found = true;
            return true;
            break;
        }
    }
    if (!user_found)
    {
        cout << "Invalid username or password" << endl;
        isLoggedIn = false;
        try
        {
            throw runtime_error("Authentication failed");
        }
        catch (const exception &e)
        {
            cout << "Error authenticating user: " << e.what() << endl;
            if (username.empty())
            {
                throw invalid_argument("Username cannot be empty");
            }
            else if (password.empty())
            {
                throw invalid_argument("Password cannot be empty");
            }
            else
            {
                throw invalid_argument("Invalid username or password");
            }
        }
        return false;
    }
    return false;
}
void User::setShoppingCart(ShoppingCart *cart)
{
    this->cart = cart;
}
void User::setWishlist(Wishlist *wishlist)
{
    this->wishlist = wishlist;
} 
void User::printUserInformation()
{
    {
        cout << endl;
        cout << "Email: " << this->email << endl;
        cout << "Username: " << this->username << endl;
        cout << "Password: " << this->password << endl;
        cout << endl;
    }
}
void User::printCartDetails() const
{
    cart->displayProducts();
}
User::~User()
{
    for (int i = 0; i < registered_users.size(); i++)
    {
        if (registered_users[i] == this)
        {
            delete registered_users[i];
            registered_users[i] = NULL;
            break;
        }
    }
}
//----------------------------------------------------------------------------PAYMENT METHOD CLASS---------------------------------------------------------------------------------
class PaymentMethod
{
public:
    virtual void pay(double amount)
    {
        cout << "Payment Method: " << endl;
    }
    virtual ~PaymentMethod() = default;
};
//------------------------------------------------------------------------------CREDIT CARD CLASS---------------------------------------------------------------------------------
class CreditCard : public PaymentMethod
{
private:
    string owner;
    string number;
    string expiration_date;
    string cvv;

public:
    CreditCard():owner(""),number(""),expiration_date(""),cvv(""){}
    CreditCard(string owner, string number, string expiration_date, string cvv)
        : owner(owner), number(number), expiration_date(expiration_date), cvv(cvv) {}

    void pay(double amount) override
    {
        cout << "Paying $" << amount << " with credit card number " << number << endl;
    }
};
//--------------------------------------------------------------------------------PAYPAL CLASS--------------------------------------------------------------------------------------
class PayPal : public PaymentMethod
{
private:
    string email;
    string password;

public:
    PayPal():email(""),password(""){}
    PayPal(string email, string password) : email(email), password(password) {}
    void pay(double amount) override
    {
        cout << "Paying $" << amount << " with PayPal account " << email << endl;
    }
};
//--------------------------------------------------------------------------------ORDER CLASS----------------------------------------------------------------------------------------
class Order{
private:
    PaymentMethod *payment_method;
    ShoppingCart *cart;
    int orderId;
    static std::random_device rd;                            // Static object for generating a random seed
    static std::mt19937 gen;                                 // Static generator for pseudo-random numbers
    static std::uniform_int_distribution<int> dis;           // Static distributor for integers
    Date orderDate;
    bool status;
    double TotalAmount;
    string ShippingAddress;

protected:
    double CalculateTotalAmountWithCashBack();

public:
    Order();
    Order(PaymentMethod *payment_method, ShoppingCart *cart);
    void view_order_details();
    void setPaymentMethod(PaymentMethod *method);
    void processOrder();
    int set_order_ID();
    void setShippingAddress(const string address);
};
std::random_device Order::rd;                              // Definition of static member rd
std::mt19937 Order::gen{Order::rd()};                      // Definition of static member gen, initialized with rd
std::uniform_int_distribution<int> Order::dis{1000, 9999}; // Definition of static member dis
Order::Order() : payment_method(nullptr), cart(nullptr), orderId(0), orderDate(Date()), status(false), TotalAmount(0) {}
Order::Order(PaymentMethod *payment_method, ShoppingCart *cart) : payment_method(payment_method), cart(cart), orderId(0), orderDate(Date()), status(false), TotalAmount(0) {}
double Order::CalculateTotalAmountWithCashBack()
{
    double sum = 0.0, TotalAmount = 0.0;
    sum = cart->set_TotalPrice();
    int i = 1;
    double back;
    while (sum > i * 1000)
        i++;
    back = sum * (double(i - 1) / 100);
    TotalAmount = sum - back;
    return TotalAmount;
}
void Order::view_order_details()
{
    cout << "OrderID: " << orderId << endl;
    cout << "Date: " << orderDate << endl;
    cout << "Shipping Address: " << ShippingAddress << endl;
}
void Order::setPaymentMethod(PaymentMethod *method)
{
    payment_method = method;
}
void Order::processOrder()
{
    if (payment_method)
    {
        cart->displayProducts();
        cout << "Total amount with cashback applied: " << CalculateTotalAmountWithCashBack() << endl;
        cout << "Number of items from your order: " << cart->getNumOfProducts() << endl;
        payment_method->pay(CalculateTotalAmountWithCashBack());
        cart->empty();
        string s;
        cout << "Please, introduce the Shipping Address: " << endl;
        cin >> s;
        setShippingAddress(s);
        status = true;
        time_t t = time(NULL);
        tm *timePtr = localtime(&t);
        orderDate.setDate(timePtr->tm_mday, timePtr->tm_mon + 1, timePtr->tm_year + 1900);
        if (status == true)
        {
            cout << "Your order was successfully submitted!" << endl;
            set_order_ID();
            view_order_details();
        }
    }
}
int Order::set_order_ID()
{
    orderId = dis(gen);
    return orderId;
}
void Order::setShippingAddress(const string address)
{
    ShippingAddress = address;
}

//--------------------------------------------------------------------------------TEMPLATE FUNCTIONS-------------------------------------------------------------------------

//template function used to convert a string type element into a T type
template<typename T>
T parseElement(const string& element) {
    istringstream iss(element);
    T value;
    iss >> value;
    return value;
}

//Specialization of parseElement for string: This specialization handles the case when the desired type is string.
//Since string values don't require any conversion, the function simply returns the token itself.
template<>
string parseElement<string>(const string& element) {
    return element;
}

//Auxiliary template function used to parse a row from a file
template<typename... Args, size_t... Indices>
tuple<Args...> parseRow_Indices(const vector<string>& line_elements, index_sequence<Indices...>) {
    return make_tuple(parseElement<Args>(line_elements[Indices])...);
}

//Template function used to parse a row from a file
template<typename... Args>
tuple<Args...> parseRow(const vector<string>& line_elements) {
    return parseRow_Indices<Args...>(line_elements, index_sequence_for<Args...>());
}

//Template function used to parse data from a text file
template<typename... Args>
class FileParser {
public:
    static vector<tuple<Args...>> parseDataFromFile(const string& filename, char delimiter = '/') {
        vector<tuple<Args...>> data;

        ifstream inputFile(filename);
        if (!inputFile) {
            cout << "Failed to open the file." << endl;
            return data;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            vector<string> line_elements;
            string element;

            while (getline(iss, element, delimiter)) {
                line_elements.push_back(element);
            }

            if (line_elements.size() == sizeof...(Args)) {
                data.emplace_back(parseRow<Args...>(line_elements));
            } else {
                cout << "Failed to parse line: " << line << endl;
            }
        }
        inputFile.close();
        return data;
    }
};

//---------------------------------------------------------------------------------SINGLETON MENU------------------------------------------------------------------------
class Menu{
    private:
    static Menu* instance;
    Menu() {}
    vector<unique_ptr<Product>> products;
    ShoppingCart cart;
    Wishlist wish;
    Order order;
    public:
    static Menu* getInstance()
    {
        if(!instance){
            instance = new Menu();
        }
        return instance;
    }
    void setProducts(vector<unique_ptr<Product>>&& products) {
        this->products = move(products);
    }

    //Functions used for menu
    void processMainMenu();
    void processLogin();
    void processRegistration();
    void processProductTypes();
    void processProductOptions(Product& selectedProduct);
    void processShoppingCartOptions();
    void processWishlistOptions();
    void processExitOption();

    //Functions used to print messages
    void showWelcomeMessage();
    void showMainMenuOptions();
    void showProductTypes();
    void showProductOptions();
    void showShoppingCartMenu();
    void showWishlistMenu();
};

//Static member
Menu* Menu::instance = nullptr;

//Functions used to print messages
void Menu::showWelcomeMessage(){
    cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<WELCOME TO OUR ONLINE SHOPPING APPLICATION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~Embark on a Fragrant Journey and discover your Signature Scent with us!~~~~~~~~~~~~~~~~~~~~"<<endl;
}
void Menu::showMainMenuOptions(){
    cout<<"1. Register"<<endl;
    cout<<"2. Login"<<endl;
    cout<<"3. EXIT "<<endl;
}

void Menu::showProductTypes(){
    cout<<"Choose the category of products you would like to see! "<<endl;
    cout<<"1. Perfumes"<<endl;
    cout<<"2. Home Scents"<<endl;
    cout<<"3. Aromatherapy "<<endl;
    cout<<"4. EXIT "<<endl;
}
    
void Menu::showProductOptions(){
    cout<<"1. Add product to shopping cart"<<endl;
    cout<<"2. Add product to wishlist"<<endl;
    cout<<"3. Add review to this product"<<endl;
    cout<<"4. Go Back to marketplace"<<endl;
    cout<<"5. EXIT"<<endl;
}
void Menu::showShoppingCartMenu(){
    cout<<"1. Display Shopping Cart Products"<<endl;
    cout<<"2. Remove product from ShoppingCart"<<endl;
    cout<<"3. Order"<<endl;
    cout<<"4. Go back to marketplace"<<endl;
    cout<<"5. EXIT"<<endl;
}
void Menu::showWishlistMenu(){
    cout<<"1. Display Wishlist Products"<<endl;
    cout<<"2. Remove product from wishlist"<<endl;
    cout<<"3. Go back to marketplace"<<endl;
    cout<<"4. EXIT"<<endl;
}

//Functions used for menu
void Menu::processMainMenu() {
    int choice;
    do {
        clearConsole();
        showWelcomeMessage();
        showMainMenuOptions();
        cout<<endl;
        cout << "Introduce your option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                processRegistration();
                break;
            case 2:
                processLogin();
                break;
            case 3:
                processExitOption();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (choice != 3);
}
void Menu::processRegistration() {
    clearConsole();
    string email, username, password;
    bool registrationSuccessful = false;
    do {
        cout << "Introduce your email: ";
        cin >> email;
        cout << "Introduce your username: ";
        cin >> username;
        cout << "Introduce your password: ";
        cin >> password;            
        registrationSuccessful = User::registerUser(email, username, password);
        if (!registrationSuccessful) 
        {
            cout << "Registration failed. Please try again." << endl;
            int retryOption;
            cout << "1. Retry registration" << endl;
            cout << "2. EXIT" << endl;
            cout<<endl;
            cout << "Introduce your option: ";
            cin >> retryOption;
            switch (retryOption) 
            {
                case 1:
                    break;
                case 2:
                    processExitOption();
                    break;
                default:
                    cout << "Invalid option. Exiting application..." << endl;
                return;
            }
        }
    } while (!registrationSuccessful);
    processProductTypes(); 
}
void Menu::processLogin() {
    clearConsole();
    string username, password;
    bool loggingSuccessful=false;
    do{
        cout << "Introduce your username: ";
        cin >> username;
        cout << "Introduce your password: ";
        cin >> password;
        User u; 
        loggingSuccessful=u.logIn(username,password);
        cout<<loggingSuccessful<<endl;
        if(!loggingSuccessful)
        {
            cout << "LogIn failed. Please try again." << endl;
            int retryOption;
            cout << "1. Retry login" << endl;
            cout << "2. Exit" << endl;
            cout<<endl;
            cout << "Introduce your option: ";
            cin >> retryOption;
            switch (retryOption) 
            {
                case 1:
                    break;
                case 2:
                    cout << "Exiting application..." << endl;
                    return; 
                default:
                    cout << "Invalid option. Exiting application..." << endl;
                return;
            }
        }
    }while(!loggingSuccessful);
    processProductTypes(); 
}

void Menu::processProductTypes() {
    clearConsole();
    int productTypeChoice;
    int perf_cnt;
    int productChoice; 
    int selectedPerfumeIndex; 
    int hs_cnt;
    int selectedHSIndex = 0;
    int currentHSIndex = 0;
    int at_cnt = 0;
    int selectedATIndex = 0;
    int currentATIndex = 0;
    do {
        showProductTypes();
        cout<<endl;
        cout << "Introduce your option: ";
        cin >> productTypeChoice;

        switch (productTypeChoice) {
            case 1:
                cout << endl << endl;
                cout << "<<<<<<<<<PERFUMES>>>>>>>>>>" << endl;
                perf_cnt = 0;
                for (int i = 0; i < products.size(); ++i) {
                    Perfume* perfume = dynamic_cast<Perfume*>(products[i].get());
                    if (perfume) {
                        perf_cnt++;
                        cout << "Perfume nr: " << perf_cnt << endl;
                        perfume->show_details();
                        cout << endl << endl;
                    }
                }
                // Allow user to choose a specific product
                cout << "Choose a product: ";
                cin >> productChoice;
                if (productChoice >= 1 && productChoice <= perf_cnt) {
                    selectedPerfumeIndex = 0;
                    int currentPerfumeIndex = 0;
                    for (const auto& product : products) {
                        if (dynamic_cast<Perfume*>(product.get())) {
                            currentPerfumeIndex++;
                            if (currentPerfumeIndex == productChoice) {
                                break;
                            }
                        }
                        selectedPerfumeIndex++;
                    }
                    unique_ptr<Product>& selectedProduct = products[selectedPerfumeIndex];
                    processProductOptions(*selectedProduct);
                } else {
                    cout << "The product you chose doesn't exist!" << endl;
                }
                break;

            case 2:
                cout << endl << endl;
                cout << "<<<<<<<<<HOME SCENTS>>>>>>>>>>" << endl;
                hs_cnt = 0;              
                for (int i = 0; i < products.size(); ++i) 
                {
                    HomeScents* homescent = dynamic_cast<HomeScents*>(products[i].get());
                    if (homescent) 
                    {
                        hs_cnt++;
                        cout << "HomeScent nr: " << hs_cnt << endl;
                        homescent->show_details();
                        cout << endl << endl;
                    }
                }

                // Allow user to choose a specific product
                cout << "Choose a product: ";
                cin >> productChoice;
                if (productChoice >= 1 && productChoice <= hs_cnt) 
                {
                    selectedHSIndex = 0;
                    currentHSIndex = 0;
                    for (const auto& product : products) 
                    {
                        if (dynamic_cast<HomeScents*>(product.get())) 
                        {
                            currentHSIndex++;
                            if (currentHSIndex == productChoice) 
                            {
                                break;
                            }
                        }
                        selectedHSIndex++;
                    }
                    unique_ptr<Product>& selectedProduct = products[selectedHSIndex];
                    processProductOptions(*selectedProduct);
                } 
                else 
                {
                    cout << "Invalid product choice. Please try again." << endl;
                }
                break;

            case 3:
                cout << endl << endl;
                cout << "<<<<<<<<<AROMATHERAPY>>>>>>>>>>" << endl;
                at_cnt = 0;
                for (int i = 0; i < products.size(); ++i) 
                {
                    Aromatherapy* aroma = dynamic_cast<Aromatherapy*>(products[i].get());
                    if (aroma) 
                    {
                        at_cnt++;
                        cout << "Aroma nr: " << at_cnt << endl;
                        aroma->show_details();
                        cout << endl << endl;
                    }
                }
                int productChoice;
                // Allow user to choose a specific product
                cout << "Choose a product: ";
                cin >> productChoice;
                if (productChoice >= 1 && productChoice <= at_cnt) 
                {
                    selectedATIndex = 0;
                    currentATIndex = 0;
                    for (const auto& product : products) 
                    {
                        if (dynamic_cast<Aromatherapy*>(product.get())) 
                        {
                            currentATIndex++;
                            if (currentATIndex == productChoice) 
                            {
                                break;
                            }
                        }
                        selectedATIndex++;
                    }
                    unique_ptr<Product>& selectedProduct = products[selectedATIndex];
                    processProductOptions(*selectedProduct);
                } 
                else 
                {
                    cout << "Invalid product choice. Please try again." << endl;
                }
                break;
            case 4:
                processExitOption();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (productTypeChoice != 4);
}


void Menu::processProductOptions(Product& selectedProduct) {
    clearConsole();
    cout<<"~THE PRODUCT YOU SELECTED~"<<endl;
    selectedProduct.show_details();
    cout<<endl;
    int option;
    string comment;
    int rating;
    Review rev;
    do {
        showProductOptions();
        cout<<endl;
        cout << "Introduce your option: ";
        cin >> option;

        switch (option) {
            case 1:
                cart.addProduct(make_shared<Product>(selectedProduct));
                cout << "Product added to the shopping cart." << endl;
                processShoppingCartOptions();
                break;
            case 2:
                wish.addProduct(make_shared<Product>(selectedProduct));
                cout<<"Product added to wishlist."<<endl;
                processWishlistOptions();
                break;
            case 3:
                cout<<"Enter comment: ";
                cin.ignore(256, '\n');
                getline(cin, comment);
                cout<<"Enter rating: ";
                cin>>rating;
                cin.ignore();
                rev=Review(comment, rating);
                selectedProduct.addReview(rev);
                selectedProduct.show_reviews();
                cout<<"Average rating for the product you selected: "<<selectedProduct.getAverageRating()<<endl;
                break;
            case 4:
                clearConsole();
                processProductTypes();
                break;
            case 5:
                processExitOption();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (option != 5);
}
void Menu::processShoppingCartOptions(){
    clearConsole();
    int option;
    int nr;
    CreditCard card;
    PayPal paypal;
    string payment_method,email,password,name,number,expiration_date,cvv;
    do{
        showShoppingCartMenu();
        cout<<endl;
        cout << "Introduce your option: ";
        cin >> option;
        switch(option){
            case 1:
                cart.displayProducts();
                cout<<endl;
                break;
            case 2:
                cart.displayProducts();
                cout<<endl;
                cout<<"Enter the number of the product you want to remove";
                cin>>nr;
                if (nr >= 1 && nr <= cart.getNumOfProducts()) {
                    shared_ptr<Product> product = cart.getProductbyIndex(nr - 1);
                    cart.removeProduct(product);
                    cout << "Product removed from the shopping cart." << endl;
                    cart.displayProducts();
                } else {
                    cout << "Invalid product number. Please try again." << endl;
                }
                cart.displayProducts();
                break;
            case 3:
                cout<<endl;
                cout<<"Payment Method Options: PayPal and CreditCard"<<endl;
                cout<<"Choose payment method: ";
                cin.ignore(256, '\n');
                getline(cin, payment_method);
                if(payment_method=="PayPal")
                {
                    cout<<"Enter paypal email: ";
                    //cin.ignore(256, '\n');
                    getline(cin, email);
                    cout<<"Enter paypal password: ";
                    //cin.ignore(256, '\n');
                    getline(cin, password);
                    paypal=PayPal(email,password);
                    order=Order(&paypal,&cart);
                    order.processOrder();
                    processExitOption();
                }
                else if(payment_method=="CreditCard")
                {
                    cout<<"Enter credit card name: ";
                    getline(cin, name);
                    cout<<"Enter credit card number: ";
                    getline(cin, number);
                    cout<<"Enter credit card expiration_date: ";
                    getline(cin, expiration_date);
                    cout<<"Enter credit card cvv: ";
                    getline(cin, cvv);
                    card=CreditCard(name,number,expiration_date,cvv);
                    order=Order(&card,&cart);
                    order.processOrder();
                    processExitOption();
                }
                break;
            case 4:
                clearConsole();
                cout << "Returning to the marketplace..." << endl;
                processProductTypes();
                break;
            case 5:
                processExitOption();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

    }while(option!=5);
}
void Menu::processWishlistOptions(){
    clearConsole();
    int option;
    int nr;
    
    do{
        showWishlistMenu();
        cout<<endl;
        cout << "Introduce your option: ";
        cin >> option;
        switch(option){
            case 1:
                wish.displayProducts();
                break;
            case 2:
                cout<<endl;
                wish.displayProducts();
                cout<<endl;
                cout<<"Enter the number of the product you want to remove";
                cin>>nr;
                if (nr >= 1 && nr <= wish.getNumOfProducts()) {
                    shared_ptr<Product> product = wish.getProductbyIndex(nr - 1);
                    wish.removeProduct(product);
                    cout << "Product removed from the wishlist." << endl;
                    wish.displayProducts();
                } else {
                    cout << "Invalid product number. Please try again." << endl;
                }
                break;
            case 3:
                clearConsole();
                cout << "Returning to the marketplace..." << endl;
                processProductTypes();
                break;
            case 4:
                processExitOption();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }while(option!=4);
}
void Menu::processExitOption() {
    cout<<endl<<endl<<endl;
    cout << "                                THANK YOU FOR USING OUR ONLINE SHOPPING APP!" << endl;
    cout<<"                   Until we meet again, let the aromas of joy follow you wherever you wander."<<endl;
    cout<<endl<<endl<<endl;
    exit(0); // Exit the program
}

int main() {
    //PARSE users.txt file
    vector<tuple<string, string, string>> usersData = FileParser<string, string, string>::parseDataFromFile("users.txt", '/');
    for (const auto& user : usersData) {
        string email = get<0>(user);
        string username = get<1>(user);
        string password = get<2>(user);
        User::registerUser(email, username, password);
    }
    
    //PARSE details about products
    vector<unique_ptr<Product>> products;

    //PARSE HomeScents.txt file
    vector<tuple<string, double, int, string, string, string>> homeScentsData =FileParser<string, double, int, string, string, string>::parseDataFromFile("HomeScents.txt");
    for (const auto& hsprod : homeScentsData) {
    string name = get<0>(hsprod);
    double price = get<1>(hsprod);
    int stock = get<2>(hsprod);
    string category = get<3>(hsprod);
    string scent_duration = get<4>(hsprod);
    string main_fragrance = get<5>(hsprod);

    unique_ptr<Product> homeScent = make_unique<HomeScents>(name, price, stock, category, scent_duration, main_fragrance);
    products.push_back(std::move(homeScent));
    }

    //PARSE perfumes.txt file
    vector<tuple<string, double, int, string, string, string>> PerfumesData = FileParser<string, double, int, string, string, string>::parseDataFromFile("perfumes.txt");
    for(const auto& perfume: PerfumesData){
        string name = get<0>(perfume);
        double price = get<1> (perfume);
        int stock = get<2> (perfume);
        string designer = get<3> (perfume);
        string category = get<4> (perfume);
        string fragrances_string = get<5> (perfume);
        vector<string> fragrances;
        stringstream f(fragrances_string);
        string fragrance;
        while (f >> fragrance)
        {
            fragrances.push_back(fragrance);
        }
        unique_ptr<Product> perfumePtr = make_unique<Perfume>(name, price, stock, designer, category,fragrances);
        products.push_back(move(perfumePtr));
    }

    //PARSE aromatherapy.txt file
    vector<tuple<string,double,int,string,string,string>> AromatherapyData = FileParser<string,double,int,string,string,string>::parseDataFromFile("aromatherapy.txt");
    for(const auto&product: AromatherapyData){
        string name=get<0>(product);
        double price = get<1> (product);
        int stock = get<2> (product);
        string usage = get<3> (product);
        string category = get<4> (product);
        string main_fragrance = get<5> (product);
        unique_ptr<Product> aromaPtr=make_unique<Aromatherapy>(name,price,stock,usage,category,main_fragrance);
        products.push_back(move(aromaPtr));
    }

    //PARSE reviews.txt file
    vector<tuple<string, string, int>> ReviewsData=FileParser<string, string, int>::parseDataFromFile("reviews.txt");
    for(const auto& rev: ReviewsData){
        string name=get<0>(rev);
        string comment=get<1>(rev);
        int rating=get<2>(rev);
        Review review(comment, rating);

        // Find the product with the matching name
        auto productIter = find_if(products.begin(), products.end(), [&name](const unique_ptr<Product>& product) {
        return product->get_name() == name;
        });
        if (productIter != products.end()) 
        {
            (*productIter)->addReview(review);
        } 
        else 
        {
        cout << "Product not found for review: " << name << endl;
        }
    }
    Menu* menu = Menu::getInstance();
    menu->setProducts(move(products));
    menu->processMainMenu();
    return 0;
}
