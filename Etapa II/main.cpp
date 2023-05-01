#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <new>
#include <stdexcept>

using namespace std;
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
    // Getteri si Setteri
    const string &get_name() const;
    virtual const double get_price() const;
    const int get_stock() const;
    void set_name(const string &new_name);
    void set_stock(int new_stock);
    virtual void set_price(double new_price); // suprascrisa in ProductOnSale;
    // Metode
    void increase_stock(int new_stock);
    void decrease_stock(int old_stock);
    void addReview(const Review &review);
    const void show_reviews() const;
    double getAverageRating() const;
    // Metode  virtuale
    virtual void show_details() const;
    //FUNCTIE SABLON
    template <typename T>
    static Product *find_product_by_name(const string &name, vector<T> &products)
    {
        for (auto &product : products)
        {
            if (product.get_name() == name)
            {
                return &product;
            }
        }
        return nullptr;
    } 
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
    cout << "Number of reviews: " << reviews.size() << endl;
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
    cout << "Product name: " << get_name();
    cout << "Price: " << get_price();
    cout << "Stock: " << get_stock();
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

protected: // metode care vor fi apelate in clasa productOnSale sau in alte clase derivate, dar nu pot fi apelate din afara clasei
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
void ProductOnSale::set_price(double discount) const {
    if (discount > price) {
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
//------------------------------------------------------------------------INTERFATA LIST_OF_PRODUCTS-----------------------------------------------------------------------------
class List_of_products
{
public:
    virtual void addProduct(Product *product) = 0;
    virtual void removeProduct(Product *product) = 0;
    virtual void displayProducts() = 0;
    virtual ~List_of_products(){};
};
//----------------------------------------------------------------------------EXCEPTIE CUSTOM----------------------------------------------------------------------------------
class OutOfStockException : public exception
{
public:
    const char* what() const throw() {
        return "Product is out of stock!";
    }
};
//--------------------------------------------------------------------------SHOPPING CART CLASS------------------------------------------------------------------------------------
class ShoppingCart : public List_of_products
{
private:
    vector<Product *> products;
    double TotalPrice;

public:
    ShoppingCart();
    ShoppingCart(vector<Product *> products);
    void addProduct(Product *product) override;
    void removeProduct(Product *product) override;
    void displayProducts() override;
    bool isEmpty() const;
    int getNumOfProducts() const;
    double set_TotalPrice();
    void empty();
};
ShoppingCart::ShoppingCart() : TotalPrice(0.0) {}
ShoppingCart::ShoppingCart(vector<Product *> products) : products(products), TotalPrice(0.0) {}
void ShoppingCart::addProduct(Product *product)
{
    if (product->get_stock() == 0) {
        throw OutOfStockException();
    }
    products.push_back(product);
    
}
void ShoppingCart::removeProduct(Product *product)
{
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i] == product)
        {
            products.erase(products.begin() + i);
            break;
        }
    }
}
void ShoppingCart::displayProducts()
{
    if (!isEmpty())
    {
        cout << "Your cart contains:" << endl;
        for (int i = 0; i < products.size(); i++)
        {
            cout << "- " << products[i]->get_name() << endl;
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
    for (int i = 0; i < products.size(); i++)
        TotalPrice += products[i]->get_price();
    return TotalPrice;
}
void ShoppingCart::empty()
{
    for (int i = products.size() - 1; i >= 0; i--)
    {
        products[i]->decrease_stock(1);
        removeProduct(products[i]);
    }
}
//------------------------------------------------------------------------------CLASA WISHLIST------------------------------------------------------------------------------------
class Wishlist : public List_of_products
{
private:
    vector<Product *> products;
    static const int MAX_PRODUCTS = 10;

public:
    Wishlist();
    Wishlist(vector<Product *> &products);
    void addProduct(Product *product) override;
    void removeProduct(Product *product) override;
    void displayProducts() override;
    bool isEmpty() const;
    int getNumOfProducts() const;
};
Wishlist::Wishlist() {}
Wishlist::Wishlist(vector<Product *> &products) : products(products) {}
bool Wishlist::isEmpty() const
{
    return products.empty();
}
int Wishlist::getNumOfProducts() const
{
    return products.size();
}
void Wishlist::addProduct(Product *product)
{
    if (products.size() < MAX_PRODUCTS)
        products.push_back(product);
    else
        cout << "Wishlist is full";
}
void Wishlist::removeProduct(Product *product)
{
    if (!isEmpty())
    {
        for (int i = 0; i < products.size(); i++)
        {
            if (products[i] == product)
            {
                products.erase(products.begin() + i);
                break;
            }
        }
    }
}
void Wishlist::displayProducts()
{
    if (!isEmpty())
    {
        cout << "Wishlist contains:" << endl;
        for (int i = 0; i < products.size(); i++)
        {
            cout << "- " << products[i]->get_name() << endl;
        }
    }
    else
    {
        cout << "Your Wishlist is empty" << endl;
    }
}
//-------------------------------------------------------------------------------CLASA USER---------------------------------------------------------------------------------------------
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
    static void registerUser(string email, string username, string password);
    static bool isUsernameUnique(string username);
    static vector<User *> getRegisteredUsers()
    {
        return registered_users;
    }
    void logIn(const string& username, const string& password);
    void setShoppingCart(ShoppingCart *cart); // method to set the cart
    void setWishlist(Wishlist *wishlist);     // method to set the wishlist
    void printUserInformation();
    void printCartDetails() const;
    ~User();
};
vector<User *> User::registered_users;
User::User() : isLoggedIn(false), isRegistered(false) {}
User::User(string email, string username, string password) : isRegistered(false), isLoggedIn(false), email(email), username(username), password(password) {}
void User::registerUser(string Email, string Username, string Password)
{
    if (Email.length() == 0 || Username.length() == 0 || Password.length() == 0)
    {
        cout << "Invalid input! It is mandatory to complete all required fields." << endl;
        return;
    }

    else
    {

        if (!isUsernameUnique(Username))
        {
            cout << "Username already taken. Please choose another username." << endl;
            return;
        }
        User *user = new User(Email, Username, Password);
        registered_users.push_back(user);
        cout << "You have successfully registered!" << endl;
        /* delete user;  */
        // deallocate memory
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
void User::logIn(const string& username, const string& password)
{
    bool user_found = false;
    for (int i = 0; i < registered_users.size(); i++)
    {
        if (registered_users[i]->username == username && registered_users[i]->password == password)
        {
            cout << "You have successfully logged in!" << endl;
            isLoggedIn = true;
            user_found = true;
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
        catch (const exception& e) 
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
    }
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
//----------------------------------------------------------------------------CLASA PAYMENT METHOD---------------------------------------------------------------------------------
class PaymentMethod
{
public:
    virtual void pay(double amount)
    {
        cout << "Payment Method: " << endl;
    }
    virtual ~PaymentMethod() = default;
};
//------------------------------------------------------------------------------CLASA CREDIT CARD---------------------------------------------------------------------------------
class CreditCard : public PaymentMethod
{
private:
    string owner;
    string number;
    string expiration_date;
    string cvv;

public:
    CreditCard(string owner, string number, string expiration_date, string cvv)
        : owner(owner), number(number), expiration_date(expiration_date), cvv(cvv) {}

    void pay(double amount) override
    {
        cout << "Paying $" << amount << " with credit card number " << number << endl;
    }
};
//--------------------------------------------------------------------------------CLASA PAYPAL--------------------------------------------------------------------------------------
class PayPal : public PaymentMethod
{
private:
    string email;
    string password;

public:
    PayPal(string email, string password) : email(email), password(password) {}
    void pay(double amount) override
    {
        cout << "Paying $" << amount << " with PayPal account " << email << endl;
    }
};
//--------------------------------------------------------------------------------CLASA ORDER----------------------------------------------------------------------------------------
class Order : private PaymentMethod
{
private:
    PaymentMethod *payment_method;
    ShoppingCart *cart;
    int orderId;
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
    {   cart->displayProducts();
        cout << "Total amount with cashback applied: " << CalculateTotalAmountWithCashBack() << endl;
        cout << "Number of items from your order: " << cart->getNumOfProducts() << endl;
        payment_method->pay(CalculateTotalAmountWithCashBack());
        cart->empty();
        string s;
        cout << "Please, introduce the Shipping Address: " << endl;
        cin>>s;
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
    orderId = rand();
    return orderId;
}
void Order::setShippingAddress(const string address)
{
    ShippingAddress=address;
}

//-------------------------------------------------------------------------------MAIN FUNCTION-------------------------------------------------------------------------------

int main()
{
    //----------------------------------------------------------------------READ PERFUMES FROM FILE------------------------------------------------------------------------------
    ifstream f("perfumes.txt");
    if (!f.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }
    vector<Perfume> perfumes;
    string line;
    while (getline(f, line))
    {
        stringstream ff(line);
        string name, designer, category, fragrances_string;
        double price;
        int quantity;
        vector<string> fragrances;
        getline(ff, name, ',');
        ff >> price;
        ff.ignore();
        ff >> quantity;
        ff.ignore();
        getline(ff, designer, ',');
        getline(ff, category, ',');
        getline(ff, fragrances_string);
        stringstream fff(fragrances_string);
        string fragrance;
        while (fff >> fragrance)
        {
            fragrances.push_back(fragrance);
        }
        Perfume perfume(name, price, quantity, designer, category, fragrances);
        perfumes.push_back(perfume);
    }
    f.close();
    for (const Perfume &perfume : perfumes)
    {
        perfume.show_details();
        cout << endl;
    }

    //----------------------------------------------------------------------READ PERFUME REVIEWS FROM FILE----------------------------------------------------------------
    ifstream r("reviews.txt");
    if (!r.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string review_line;
    while (getline(r, review_line))
    {
        stringstream rr(review_line);
        string product_name;
        string comment;
        int rating;
        getline(rr, product_name, '/');
        getline(rr, comment, '/');
        rr >> rating;
        Review rev(comment, rating);
        Product *product = Product::find_product_by_name(product_name, perfumes);
        if (product != nullptr)
        {
            Perfume *perfume_found = dynamic_cast<Perfume *>(product);
            if (perfume_found != nullptr)
            {
                perfume_found->addReview(rev);
            }
        }
        else
        {
            cout << "Product not found: " << product_name << endl;
        }
    }
    for (const Perfume &perfume : perfumes)
    {
        perfume.show_details();
        perfume.show_reviews();
        cout << "Average rating: " << perfume.getAverageRating() << endl;
        cout << endl;
    } 
    r.close();

    //Exemplu apelarea destructorului virtual + UPCASTING ------------------------------------------------------------------------------------------------------------------
    Product *p = new Perfume("Dior Sauvage", 120.0, 5, "Dior", "Woody", {"Lavender", "Bergamot", "Patchouli"});
    p->show_details();
    p->set_price(130);
    p->show_details();
    delete p;
    
    //Exemple de upcasting-------------------------------------------------------------------------------------------------------------------------------------
    PaymentMethod *paym= new CreditCard("John Doe", "1234 5678 9012 3456", "12/25", "123");
    paym->pay(130);
    delete paym;

    Date date_start(25, 10, 2023);
    Date date_end(30, 10, 2023);
    Product *p_sale=new ProductOnSale("Autumn Scents Sales", date_start, date_end, 15, "Chanel No. 5", 100.0, 10);
    p_sale->show_details();
    delete p_sale;

    Perfume p1("Chanel No. 5", 100.0, 10, "Chanel", "Floral", {"Rose", "Jasmine", "Sandalwood"});
    Perfume p2("Dior Sauvage", 120.0, 5, "Dior", "Woody", {"Lavender", "Bergamot", "Patchouli"});
    Perfume p3("Gucci Bloom", 90.0, 15, "Gucci", "Floral", {"Jasmine", "Tuberose", "Rangoon Creeper"});
    vector<Product *> Perfumes;
    Perfumes.push_back(&p1);
    Perfumes.push_back(&p2);
    Perfumes.push_back(&p3);
    List_of_products *list = new Wishlist(Perfumes);
    list->displayProducts();
    delete list;
    //---------------------------------------------------------------------Test ShoppingCart class functionality---------------------------------------------------------
    cout<<endl<<endl<<"Test ShoppingCart class functionality"<<endl;
    ShoppingCart cart1;
    List_of_products *cartInterface = &cart1;
    cartInterface->addProduct(&p1);
    cartInterface->addProduct(&p2);
    cartInterface->addProduct(&p2);
    cartInterface->addProduct(&p3);
    cart1.set_TotalPrice();
    cart1.displayProducts();
    cout << endl;
    ShoppingCart cart2;
    cart2.addProduct(&p3);
    cart2.addProduct(&p1);
    cart1.removeProduct(&p3);
    cart1.displayProducts();
    cout << endl;
    // ------------------------------------------------------------------------Test wishlist class functionality----------------------------------------------------------------------
    cout<<endl<<endl<<"Test wishlist class functionality"<<endl;
    Wishlist list1;
    list1.addProduct(&p1);
    list1.addProduct(&p2);
    list1.addProduct(&p3);
    list1.displayProducts();
    list1.removeProduct(&p2);
    list1.displayProducts(); 
    //---------------------------------------------------------------------------Test user class functionality----------------------------------------------------------------------------
    // register a user
    cout<<endl<<"Test user class functionlity"<<endl;
    User::registerUser("test@example.com", "testuser", "password");
    // try to register another user with the same username
    User::registerUser("another@example.com", "testuser", "password123");
    // log in with the registered user
    User user;
    user.logIn("testuser", "password");
    //------------------------------------------------------------------------------Register users from file--------------------------------------------------------------------------------
    cout<<endl<<endl<<"REGISTER USERS FROM FILE"<<endl;
    ifstream u("users.txt");
    if (!u.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }
    string user_line;
    vector<User> users;
    while (getline(u, user_line))
    {
        string email, username, password;
        stringstream uu(user_line);
        getline(uu, email, '/');
        getline(uu, username, '/');
        getline(uu, password, '/');
        User::registerUser(email, username, password);
    }
    for (auto user : User::getRegisteredUsers())
    {
        user->printUserInformation();
        user->setShoppingCart(&cart1);
        user->printCartDetails();
    }
    u.close();

    //------------------------------------------------------------------------Test ProductOnSale class functionality-----------------------------------------------------------
    cout<<endl<<"Test ProductOnSale class functionality"<<endl;
    Date Date_start(25, 10, 2023);
    Date Date_end(30, 10, 2023);
    ProductOnSale prod1("Autumn Scents Sales", Date_start, Date_end, 15, "Chanel No. 5", 100.0, 10);
    prod1.display_sale_details();
    cout << endl;
    prod1.show_details();
    //---------------------------------------------------------------Test PaymentMethod, CreditCard, PayPal classes functionalities--------------------------------------------
    cout<<endl<<endl<<"Test PaymentMethod, CreditCard, Order functionalities"<<endl;
    CreditCard card1("John Doe", "1234 5678 9012 3456", "12/25", "123");
    PayPal paypal1("johndoe@example.com", "mypassword");
    //---------------------------------------------------------------------------Test ORDER CLASS FUNCTIONALITY-------------------------------------------------------------
    ShoppingCart c;
    c.addProduct(&p1);
    c.addProduct(&p2);
    c.addProduct(&p2);
    Order order(&paypal1,&c);
    order.processOrder();
    cout<<"STOCUL "<<p2.get_stock()<<endl; //to test the functionality of decrease_stock()

    //---------------------------------------------------------------------------------TRY ... CATCH----------------------------------------------------
    cout<<endl<<"Try... catch blocks"<<endl;
    ShoppingCart C;
    Perfume P1("Chanel No. 5", 100.0, 1, "Chanel", "Floral", {"Rose", "Jasmine", "Sandalwood"});
    
    //CUSTOM EXCEPTION
    try {
        C.addProduct(&p1);
        C.addProduct(&p1);
    } 
    catch (const OutOfStockException& e) {
        cout << e.what() <<endl;
    }

    //ANOTHER EXCEPTION
    //P1.getAverageRating();
    try {
        double average_rating = P1.getAverageRating();
        cout << "Average rating for product is: " << average_rating  << endl;
        } 
    catch (const runtime_error& e) 
    {
    cout<< "Error calculating average rating: " << e.what() <<endl;
    }

    //ANOTHER EXCEPTION - USER CLASS -logIn method
    User u1,u2;
    string username, password;
    u2.logIn("testuser", "password");
    u1.logIn("mihai","1235");
    return 0;
}