///  Project 2
//  Created by Edgar Esparza on 6/24/15.


#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
using namespace std;

const bool KEYBOARD = true;
ofstream Out("con");

int getNumberOfSales(void);
int getItemNumber(void);
double getPrice(int itemNumber);
bool isTaxable(int itemNumber);
int getQuantity(int itemNumber);
double getCost(int itemNumber, int count, double price);
double getTax(double sales);
void printLine(ostream & w,int iNumber, int qty, double price,double cost, bool taxable);
void printTotal(ostream & w, int loopCount, double grandTotal, double taxDue);
void headings(ostream & w);
void startRandom(void);
void prepareOutput( ostream & w);

int main()
{
    int differentItems,
    iNumber,
    qty;
    double price,
			 cost,
			 taxableTotal,
			 nonTaxableTotal,
			 taxDue,
			 grandTotal;
    bool   taxable;
    
    taxableTotal=0;
    nonTaxableTotal=0;
    grandTotal=0;
    
    prepareOutput(Out);
    if (!KEYBOARD) startRandom();
    headings(Out);
    differentItems = getNumberOfSales();
    for( int i = 0; i < differentItems ; i++)
    {
        iNumber = getItemNumber();
        qty     = getQuantity(iNumber);
        price   = getPrice(iNumber);
        cost    = getCost(iNumber, qty, price);
        taxable = isTaxable(iNumber);
        headings(Out);
        printLine(Out,iNumber,qty,price,cost,taxable);
        
        if(taxable)
            taxableTotal+=cost;
        else
            nonTaxableTotal+=cost;
       
    }
    taxDue = getTax(taxableTotal);
    grandTotal=taxableTotal+nonTaxableTotal;
    printTotal(Out,differentItems, grandTotal, taxDue);
    return 0;
}


void startRandom(void)
{
    int seed;
    cout << "Enter seed value for random number generator: ";
    cin >> seed;
    srand(seed);
}
int getItemNumber(void)
{
    int num;
    if (KEYBOARD)
    {  cout << "Enter item number: ";
        cin >> num;
    }
    else
        num = rand() % 9000 + 1000;
    return num;
}
double getPrice(int num)
{
    double price;
    if (KEYBOARD)
    {  cout << "Enter price for item  " << num << " : ";
        cin >> price;
    }
    else
        price = double (rand() % 1000 + 10 ) / 100;
    return price;
}
bool isTaxable(int itemNumber)
{
    char ans;
    if(KEYBOARD){
        cout<<"Is item number "<<itemNumber<<" taxable (y or n): ";
        
        cin>>ans;
        if(ans=='y')
            return true;
        else
            return false;
    }
    else
    {
        if(itemNumber%5==0)
            return false;
        else
            return true;
    }
    
}
int getQuantity(int num)
{
    int quant;
    if (KEYBOARD)
    {
        cout<<"How many of item "<<num<<" were purchased? ";
        cin>>quant;
    }
    else
        quant=rand()%9;
    return quant;
}
int getNumberOfSales(void)
{
    int nSales;
    if(KEYBOARD)
    {
        cout<<"How many different items to purchase? ";
        cin>>nSales;
    }
    else
        nSales=rand()%16;
    return nSales;
}
double getCost(int itemNumber, int count, double price)
{
    return count*price ;
}
double getTax(double sales)
{
    const double tax=0.0725;
    return sales*tax;
}
void printLine(ostream & w,int iNumber, int qty, double price,double cost, bool taxable)
{
    cout <<setw(10)<< iNumber<<setw(10)<<qty<<setw(10)<<price<<setw(10)<<cost;
    if (taxable == false)
        cout << "   *";
    cout<<endl;
}

void printTotal(ostream & w,int loopCount, double grandTotal, double taxDue)
{
    cout << "Purchase : "<<grandTotal<<endl<< "Tax :   "<<taxDue<<endl <<"Amount : " << grandTotal + taxDue << endl;
    cout<< endl <<" * indicates item was not taxable ." << endl;
}

void headings(ostream & w)
{
    w << setw(10) << "Item #" << setw(10) << "Quantity" << setw(10) <<"Price"
    << setw(10) << "Cost" << endl << endl;
}

void prepareOutput(ostream & w)
{
    cout << setiosflags(ios::showpoint | ios:: fixed) << setprecision(2);
}

