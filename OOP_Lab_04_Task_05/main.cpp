#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class CarTrans {
public:
    string CarNumb;
    string Name;
    string Surname;
    int Age = 0;
    int Sum = 0;
    
    void CopyCar(CarTrans * cr)
    {
        this->SetValues(cr->CarNumb, cr->Name, cr->Surname, cr->Age, cr->Sum);
    }
    
    void SetValues(string num, string name, string surname, int age,int sum)
    {
        this->CarNumb = num;
        this->Name = name;
        this->Surname = surname;
        this->Age = age;
        this->Sum = sum;
    }
    
    void PrintValues()
    {
        cout << "Car Number: " << CarNumb << endl << "Name: " << Name << endl << "Surname: " << Surname << endl << "Age: " << Age <<endl<<"Sum: "<< Sum << endl<<endl;
    }
    
    CarTrans(string num , string name , string surname, int age,int sum)
    {
        SetValues(num, name, surname, age,sum);
    }
    
    CarTrans()
    {
    }
    
    CarTrans(CarTrans* cr)
    {
        this->CopyCar(cr);
    }
};

class Taxi : public CarTrans {
private:
    int order = 0;
    double price = 0;
    
public:
    int GetOrder()
    {
        return this->order;
    }
    double GetPrice()
    {
        return this->price;
    }
    
    void Copy(Taxi* tax)
    {
        SetValues(tax->order, tax->price);
        this->CarNumb = tax->CarNumb;
        this->Name = tax->Name;
        this->Surname = tax->Surname;
        this->Age = tax->Age;
        this->Sum = tax->Sum;
    }
    
    void PrintFields()
    {
        cout << "Driver:\n";
        PrintValues();
        cout << "Order:\nCost of the order: " << order << endl << "Price per km: " << price <<"\n\n"<< endl<<endl;
    }
    
    void SetValues(int order, double price)
    {
        this->order = order;
        this->price = price;
    }
    
    void SetParent(CarTrans* cr)
    {
        this->CarNumb = cr->CarNumb;
        this->Name = cr->Name;
        this->Surname = cr->Surname;
        this->Age = cr->Age;
        cr->Sum += this->order;
        this->Sum = cr->Sum;
    }
    
    Taxi(int order, double price) : CarTrans()
    {
        SetValues(order, price);
    }
    
    Taxi(int order, double price, CarTrans* cr) : CarTrans()
    {
        SetValues(order, price);
        SetParent(cr);
    }
    
    Taxi() : CarTrans()
    {
    }
    
    Taxi(Taxi * tax)
    {
        Copy(tax);
    }
};

    void Swap1(Taxi* a1, Taxi* a2)
    {
        Taxi*  temp = new Taxi(a1);
        a1->Copy(a2);
        a2->Copy(temp);
    }

    void Swap2(CarTrans* a1, CarTrans* a2)
    {
        CarTrans*  temp = new CarTrans(a1);
        a1->CopyCar(a2);
        a2->CopyCar(temp);
    }

    void PrintArray1(Taxi* arr, int size)
    {
        for (int i = 0; i < size; i++)arr[i].PrintFields();
    }

    void PrintArray2(CarTrans* arr, int size)
    {
        for (int i = 0; i < size; i++)arr[i].PrintValues();
    }

    void SortByIncrease(CarTrans* arr, int size)
    {
        int min = 0;
        for (int i = 0; i < size; i++)
    {
            min = i;
            for (int j = i + 1; j < size; j++)
                min = (arr[j].Sum > arr[min].Sum) ? j : min;
            if (i != min)
            {
                Swap2(arr + i, arr + min);
            }
        }
    }

    int WholeSum(CarTrans * arr,int size)
    {
        int sum = 0;
        for (int i = 0; i < size; i++)sum += (arr + i)->Sum;
        return sum;
    }

int main()
{
    CarTrans* c = new CarTrans[3];
    
    c[0].SetValues("AM 5665 KM", "Ruslan", "Malinovsky", 25, 0);
    c[1].SetValues("AV 7921 KV", "Roman", "Yaremchuk", 23, 0);
    c[2].SetValues("VS 0001 NS", "Oleksandr", "Zinchenko", 22, 0);
    
    Taxi* tax = new Taxi[10];
    
    srand(time(0));
   // cout << "Orders: \n";
    for (int i = 0; i < 10; i++) {
        tax[i] = new Taxi(100 + rand()%1000, 3 + rand() % 5,c + rand() % 3);
        tax[i].PrintFields();
    }
    
    SortByIncrease(c, 3);
    cout << "\n\nArray after sorting:\n\n";
    PrintArray2(c, 3);
    
    cout << "\n\nThe whole sum is " << WholeSum(c, 3) <<
    "\nThe most successful driver is " << c[0].Name << " " << c[0].Surname << " With total value of " << c[0].Sum<<"\n\n"<<endl;
    
    return 42;
}
