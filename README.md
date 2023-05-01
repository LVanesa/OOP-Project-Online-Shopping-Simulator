# **POO - MAGAZIN ONLINE** 
# Etapa I
Construit în primul rând din perspectiva utilizatorului, proiectul simulează experiența unei aplicații de shopping online. Utilizatorul poate să se înregistreze sau să se conecteze la contul personal pentru a plasa comenzi și a accesa date. Utilizatorul poate să vizualizeze produsele și să dea review-uri acestora. De asemenea, stocul produselor se actualizeaza în timp real, odată cu fiecare comandă nouă plasată, fapt vizibil tutoror userilor. Mai mult de atât, în limita posibilităților, userilor nu le este permis să adauge în coșul de cumpărături mai multe produse decât există pe stoc, ei fiind întâmpinați de un mesaj de eroare în cazul în care acest lucru se întâmplă. Clasele și metodele implementate în proiect asigură și alte funcționalități precum: calculul unui procent de cashback, media review-urilor, posibilitatea schimbării informațiilor despre utilizatori, adăugarea și eliminearea produselor din coșul de cumpărături etc.

## Clasele implementate pentru prima etapă:
### 1.CLASA PRODUCT: reține numele, prețul, categoria, stocul și review-ul fiecărui produs existent în baza de date a magazinul.

>Constructori/destructori:
    	   Constructor fara parametri;
	   Constructor cu parametri;
	   Constructor de copiere;
	   Destructor;

>Getteri:
	getName(); 
	getPrice(); 
	getCategory(); 
	getStock(); 

>Setteri:
	setStock(int stock);
	setPrice(double price);

>Alte metode:
	addReview(int starts);
	getAverageRating();
	increase_stock(int quantity);
	decrease_stock(int quantity);
  
>Operator overloading:
	"<<";
	"=";



### 2.CLASA DATE: compusă clasei Order, cu ajutorul ei generez data plasării unei comenzi în timp real.
	
>Constructori:
	Constructor fara parametri;
	Constructor cu parametri;
	
>Setteri:
	setDay(int D)
	setMonth(int M)
	setYear(int Y)
	setDate(int D, int M, int Y) 
	
>Getteri:
	getDay()
	getMonth()
	getYear()
	
>Alte metode:
	printDate()
	
>Operator overloading: folosesc acest overloading la plasarea unei comenzi, când afișez detaliile comenzii dacă aceasta a fost plasată cu succes îndeplinind toate condițiile
	"<<"



### 3.CLASA ORDER: aici sunt prelucrate informațiile care vizează plasarea unei comenzi. Compusă claselor ShoppingCart și User.

>Constructor:
	Constructor fara parametri;
	
>Setteri:
	setShippingAddress(const char* addr)
	setPaymentMethod(const char* paym)
	setTotalAmount(const double sum)
	
>Getteri:
	getTotalAmount();
	getStatus (apelată din clasa ShoppingCart pentru a goli coșul de cumpărături dacă întoarce true);
	
>Alte metode:
	bool submitOrder() (în această metodă se generează un orderID random odată ce funcția de placeOrder() este executată cu succes);
	placeOrder() ( programul cere informatii utilizatorului: payment,shipping address, după care apelează submitOrder pentru generarea unui ID de comandă.);
	viewOrderDetails() (dacă plasarea comenzii a avut loc cu succes, placeOrder() apelează intern această funție pentru a-i printa utilizatorului informațiile comenzii);
	cash_back_calculator() (functie care calculeaza procentajul de cashback in functie de valoarea totala a unei comenzi).
	
	
	
### 4. CLASA SHOPPINGCART: aici sunt manipulate informații despre produsele pe care utilizatorul le adaugă/șterge din coșul de cumpărături. De asemenea, clasa este compusă clasei User.

>Constructori/Destructori:
	Constructor fara parametri;
	Constructor de copiere;
	Destructor - dezaloca memoria array-ului;

>Setteri 
	setTotalPrice();
	setNumProducts();
	
>Getteri	
        getTotalPrice();  (metoda îmi calculează suma totală a unui coș în funcție de produsele adăugate în el și cantitatea fiecăruia specificată în array-ul de cantități)
	getnumProducts();

>Alte metode:
	addProduct(Product *product, int quantity=1);
	removeProduct(int index, int quantity=1);
	displayCartInfo();
	make_purchase() (metoda care plasează o comandă și șterge apoi pointerii din array-ul de produse) 

>Operator Overloading:
	"=" (folosit în clasa user, unde definesc coșul de cumpărături al utilizatorului)



### 5. CLASA USER: în această clasă programul memorează date despre utilizatorii săi(username, parolă, email, adresă etc.)

>În afară de variabilele care sunt private, definesc și 3 metode private pe care le accesez doar atunci când user-ul vrea să schimbe informații private
	setUsername();
	setPassword();
	setEmail();
	
>Constructori/Destructori:
	Constructorul fara parametri;
	Constructorul cu parametri;
	
>Getteri:
	getUsername();
	getPassword();
	getEmail();
	getAddress();
	
>Setteri:
	setAddress(const char *Address);
	setCart(Shopping Cart);

>Others:
	bool login(const char*Username, const char *Password); 
	bool registration(const char*Username, const char *Password, const char* Email, const char *Address);
	print_user_information(); 
	account_settings(const char *OldUsername, const char *OldPassword, const char *OldEmail, const char *NewUsername, const char *NewPassword, const char *NewEmail);
	view_cart();
	order()
# Etapa II
## Clasele implementate pentru a doua etapă:
### 1.CLASA DATE
### 2.CLASA SALE - clasă abstractă
### 3.CLASA REVIEW
### 4.CLASA PRODUCT
### 5.CLASA PRODUCT_ON_SALE
### 6.CLASA PERFUME 
### 7.CLASA LIST_OF_PRODUCTS - intefață
### 8.CLASA OUT_OF_STOCK_EXCEPTION
### 9.CLASA SHOPPING_CART
### 10.CLASA WISHLIST
### 11.CLASA USER
### 12.CLASA PAYMENT_METHOD
### 13.CLASA CREDIT_CARD
### 14.CLASA PAYPAL
### 15.CLASA ORDER



