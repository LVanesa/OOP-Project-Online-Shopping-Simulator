# **POO - MAGAZIN ONLINE** 
# Etapa I
Construit în primul rând din perspectiva utilizatorului, proiectul simulează experiența unei aplicații de shopping online. Utilizatorul poate să se înregistreze sau să se conecteze la contul personal pentru a plasa comenzi și a accesa date. Utilizatorul poate să vizualizeze produsele și să dea review-uri acestora. De asemenea, stocul produselor se actualizeaza în timp real, odată cu fiecare comandă nouă plasată, fapt vizibil tutoror userilor. Mai mult de atât, în limita posibilităților, userilor nu le este permis să adauge în coșul de cumpărături mai multe produse decât există pe stoc, ei fiind întâmpinați de un mesaj de eroare în cazul în care acest lucru se întâmplă. Clasele și metodele implementate în proiect asigură și alte funcționalități precum: calculul unui procent de cashback, media review-urilor, posibilitatea schimbării informațiilor despre utilizatori, adăugarea și eliminearea produselor din coșul de cumpărături etc.

## Clasele implementate pentru prima etapă:
### 1.CLASA PRODUCT: reține numele, prețul, categoria, stocul și review-ul fiecărui produs existent în baza de date a magazinul.
>Constructori/destructori:
    - Constructor fara parametri
	  - Constructor cu parametri
	  - Constructor de copiere
	  - Destructor

>Getteri:
	-getName() 
	-getPrice() 
	-getCategory() 
	-int getStock() 

>Setteri:
	-void setStock(int stock)
	-void setPrice(double price)

>Alte metode:
	-addReview(int starts)
	-getAverageRating() const
	-increase_stock(int quantity)
	-decrease_stock(int quantity)
  
>Overloading:
	- "<<"
	- "="



