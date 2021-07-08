//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<process.h>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<direct.h>
#include<windows.h>
#include<conio.h>
using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************



class Wholesaler
{
	public:
		string pno,nameofproduct,description;
		long barcode;
		int quantity;
		double price;
	public:
		Wholesaler(string pno,string nameofproduct,string description,long barcode,int quantity,double price)
		{
			this->pno=pno;
			this->nameofproduct=nameofproduct;
			this->description=description;
			this->barcode=barcode;
			this->quantity=quantity;
			this->price=price;
		}
		Wholesaler()
		{

		}
		void show()
		{
			cout<<"Sl. No. :\t\t"<<pno <<endl;
			cout<<"Product Name:\t\t"<<nameofproduct<<endl;
			cout<<"Description:\t\t"<<description<<endl;
			cout<<"barcode:\t\t"<<barcode<<endl;
			cout<<"Quantity:\t\t"<<quantity<<endl;
			cout<<"Price:\t\t"<<price<<endl;
			getch();
		}

};
class Retailer
{
	public:
		string rno,regNo,rName;
	public:
		Retailer()
		{
			rno="";
			regNo="";
			rName="";
		}
		Retailer(string rno,string regNo,string rName)
		{
			this->rno=rno;
			this->regNo=regNo;
			this->rName=rName;
		}
		void show()
		{
			cout<<"******************** RETAILER DETAILS *************************"<<endl;
			cout<<"Serial No.: "<<rno<<endl;
			cout<<"Registration No.: "<<regNo<<endl;
			cout<<"Name: "<<rName<<endl;
		}


};
class WholeNode
{
	public:
	Wholesaler data;
	WholeNode *next;
};
WholeNode* head=NULL;
void order(string productName);
void deleteData(string name);
void append(WholeNode** head_ref, Wholesaler obj)
{
    /* 1. allocate node */
    WholeNode *new_node = new WholeNode();
    WholeNode *last = *head_ref; /* used in step 5*/
    /* 2. put in the data */
    new_node->data = obj;
    /* 3. This new node is going to be the last node, so make next of
    it as NULL*/
    new_node->next = NULL;
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

void searchProduct(WholeNode** head,string productName)
{
	int flag=0;
	WholeNode *current=*head;
	while(current!=NULL)
	{
		Wholesaler ob=current->data;
		if(ob.nameofproduct==productName)
		{
			flag=1;
			cout<<"Product available for sale"<<endl;
			ob.show();
			return;
		}
		current=current->next;
	}
	if(flag==0)
	cout<<"No such product availaible"<<endl;
	cout<<"Do you want to put an order for the product?(Y/n)"<<endl;
	char ch;
	cin>>ch;
	if(ch=='Y'||ch=='y')
	order(productName);
	return;
}
void searchBarcode(WholeNode** head,long bar)
{
	int flag=0;
	WholeNode *current=*head;
	while(current!=NULL)
	{
		Wholesaler ob=current->data;
		if(ob.barcode==bar)
		{
			flag=1;
			cout<<"Product available for sale "<<endl;
			ob.show();
			break;
		}
		current=current->next;
	}
	if(flag==0)
	cout<<"No such product available"<<endl;
	getch();
	return;

}
void order(string productName)
{
	fstream fout;
	fout.open("order.csv", ios::out|ios::app);
	cout<<"Please give the details of your order --"<<endl;
	cout<<"Product Name:\t\t"<<productName<<endl;
	int quan;
	cout<<"Quantity? ";
	cin>>quan;
	fout<<productName<<","<<quan<<"\n";
	cout<<"Order is succesfully saved"<<endl;
	getch();
}
void searchDescription(WholeNode** head,string des)
{
	int flag=0;
	WholeNode *current=*head;
	while(current!=NULL)
	{
		Wholesaler ob=current->data;
		if(ob.description==des)
		{
			flag=1;
			cout<<"Product available"<<endl;
			ob.show();
			break;
		}
		current=current->next;
	}
	if(flag==0)
	{
	    cout<<"No such Product available"<<endl;
        cout<<"Do you want to apply for order>(Y/n)"<<endl;
        char ch;
        cin>>ch;
        if(ch=='Y'||ch=='y')
        {
            cout<<"Enter name of product you want: ";
            string name;
            cin>>name;
            order(name);
        }
	}

	return;
}

void readOrder()
{
	string name;
	int quantity;
	fstream fin;
	fin.open("order.csv",ios::in);
	if(!fin)
	{
		cout<<"ERROR!! NO SUCH FILE EXITS SO NO ORDERS GIVEN";
		getch();
		return;
	}
	vector<string> row;
	string line,word,temp;
	cout<<"***********************************************"<<endl;
	cout<<" Product Name\t\t\tQuantity "<<endl;
	cout<<"***********************************************"<<endl;
	while(fin.good())
	{
		row.clear();
		getline(fin,line);
		stringstream s(line);
		while(getline(s,word,','))
		{
			cout<<word<<"\t\t";
		}
		cout<<endl;
	}
	cout<<"***********************************************"<<endl;
	getch();
	return;
}
void deleteProduct(WholeNode** head,string proName)
{
    int flag=0;
	WholeNode *current=*head,*temp;
	for(int i=0;current!=NULL;i++)
	{
		Wholesaler ob=current->data;

		if(i==0 && ob.nameofproduct==proName)
		{
			flag==1;
			*head=current->next;
			free(current);
			break;
		}
		else if(ob.nameofproduct==proName)
		{
			flag=1;
			temp->next=current->next;
			free(current);
			break;
		}
		temp=current->next;
		current=current->next;
	}
	if(flag==1)
	{
	    deleteData(proName);
	}
	else
	{
		cout<<"PRODUCT IS NOT AVAILABLE...."<<endl;
	}
	getch();
    return;

}
void deleteData(string name)
{
	fstream fin, fout;
    // Open the existing file
    fin.open("product.csv", ios::in);
    // Create a new file to store the non-deleted data
    fout.open("productnew.csv", ios::out);
    string line, word;
    vector<string> row;
    // Check if this record exists
    // If exists, leave it and
    // add all other data to the new file
    int count=0;
    while (!fin.eof())
	{
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ','))
		{
            row.push_back(word);
        }
        string n=row[0];

        // writing all records,except the record to be deleted,
        // into the new file 'reportcardnew.csv' using fout pointer
        int row_size=row.size();
        if(n==name)
        {
        	count=1;
        	continue;
		}
        else
		{
            if (!fin.eof())
			{
                for (int i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        if (fin.eof())
            break;
    }
    if (count == 1)
        cout << "\nRecord deleted\n";
    else
    	cout<<"\nRecord Not Found\n";
    fin.close();
    fout.close();
    // removing the existing file
    remove("product.csv");
    // renaming the new file with the existing file name
    rename("productnew.csv", "product.csv");
}
void deleteList(WholeNode** head_ref)
{
	/* deref head_ref to get the real head */
	WholeNode* current = *head_ref;
	WholeNode* next;

	while (current != NULL)
	{
	    next = current->next;
	    free(current);
	    current = next;
	}
	/* deref head_ref to affect the real head back
	    in the caller. */
	*head_ref = NULL;
}
void showAllProducts(WholeNode** head)
{
	WholeNode *current=*head;
	cout<<"*************************  ALL products **********************"<<endl;
	cout<<endl<<"********************************************************"<<endl;
	while(current!=NULL)
	{
		Wholesaler ob=current->data;
		cout<<"Serial no.: "<<ob.pno<<endl;
		cout<<"Product Name: "<<ob.nameofproduct<<endl;
		cout<<"Description: "<<ob.description<<endl;
		cout<<"Barcode: "<<ob.barcode<<endl;
		cout<<"Quantity: "<<ob.quantity<<endl;
		cout<<"Price: "<<ob.price<<endl;
		cout<<"\n********************************************************\n"<<endl;
		current=current->next;
	}
	getch();
	return;
}
void writeFile()
{
    char ch;
	system("CLS");
	fstream fout;
    // opens an existing csv file or creates a new file.
    fout.open("product.csv", ios::out | ios::app);
    string s,pname,descrip;
    long barcode;
    int quan;
    double price;
    cout<<"*************************************************"<<endl;
  	cout<<"****************  PRODUCT ENTRY  ****************"<<endl;
  	cout<<"*************************************************"<<endl<<endl;
    do
    {
    	cout<<"Enter Serial No.  :\t";
    	cin>>s;
    	cout<<"\nEnter product name  :\t";
    	cin.ignore();
    	getline(cin,pname);
    	cout<<"\nEnter Description of product  :\t";
    	cin.ignore();
    	getline(cin,descrip);
    	cout<<"\nEnter Barcode of the product  :\t";
    	cin>>barcode;
    	cout<<"\nEnter quantity of product  :\t";
    	cin>>quan;
    	cout<<"\nEnter the price of the product  :\t";
    	cin>>price;

    	fout<<s<<","<<pname<<","<<descrip<<","<<barcode<<","<<quan<<","<<price<<"\n";
    	Wholesaler ox(s,pname,descrip,barcode,quan,price);
    	cout<<"Do you want to see what you have just entered?(Y/n)"<<endl;

		cin>>ch;
		if(ch=='Y'||ch=='y')
		ox.show();
    	cout<<"Do you want to add more products to database?(Y/n)"<<endl;
		cin>>ch;
	}while(ch=='Y'||ch=='y');


}
void readFile()
{
    fstream fin;

    // Open an existing file
    fin.open("product.csv", ios::in);
    if(!fin)
    {
    	cout<<"ERROR NO FILE";
    	getch();
    	return;
	}
  	int count=0;
    // Read the Data from the file as String Vector
    vector<string> row;
    string line, word, temp;

    while (fin.good())
	{
  		count=1;
        row.clear();
        // read an entire row and store it in a string variable 'line'
        getline(fin, line);
        // used for breaking words
        stringstream s(line);
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s,word,','))
		{
        	row.push_back(word);
        }
  		Wholesaler obj(row[0],row[1],row[2],stol(row[3]),stoi(row[4]),stod(row[5]));
  		append(&head,obj);

    }
    if (count == 0)
        cout << "Record not found\n";
}
void writeRetailFile()
{
    char ch;
	string sl,reg,rName;
	fstream fout;
	fout.open("retail.csv",ios::out|ios::app);
	cout<<"**************************************************"<<endl;
	cout<<"************ RETAIL INFORMATION ENTRY ************"<<endl;
	cout<<"**************************************************"<<endl;
	do
	{
		cout<<"Enter Serial No. : ";
		cin>>sl;
		cout<<"Enter registration No.: ";
		cin>>reg;
		cout<<"Enter Retailer Name : ";
		cin.ignore();
		getline(cin,rName);

		fout<<sl<<","<<reg<<","<<rName<<"\n";
		cout<<"Do you want to see what you have just entered?(Y/n)"<<endl;

		cin>>ch;
		if(ch=='Y'||ch=='y')
		{
			Retailer ox(sl,reg,rName);
			ox.show();
			system("CLS");
		}
		cout<<"Do you want more entry to database?(Y/n)";
		cin>>ch;
		cout<<endl;
	}while(ch=='Y'||ch=='y');

}
void readRetailFile()
{
	int count=0;
	fstream fin;
	fin.open("retail.csv",ios::in);
	if(!fin)
	{

		cout<<"ERROR NO SUCH FILE EXISTS"<<endl;
		getch();
		return;
	}
	vector<string> row;
	string line,word,temp;
	while(fin.good())
	{
	    row.clear();
		count=1;
		getline(fin,line,'\n');
		stringstream s(line);
		while(getline(s,word,','))
		{
			row.push_back(word);
		}

		Retailer obj(row[0],row[1],row[2]);
		obj.show();
		cout<<"\n***************************************************\n";
	}
	fin.close();
	getch();
}
int  searchProQuan(WholeNode** head,string name,int qu)
{
	int flag=0;
	WholeNode *current=*head;
	while(current!=NULL)
	{
		Wholesaler ob=current->data;
		if(ob.nameofproduct==name && ob.quantity>=qu)
		{
			flag=1;
			ob.quantity-=qu;
			return 1;
		}
		else if(ob.nameofproduct==name && ob.quantity<qu)
		{
			return ob.quantity;
		}
		current=current->next;
	}
	return 0;

}
void productbuy(string reg)
{
	char d;
	fstream fout;
	fout.open("productbuy.csv",ios::out|ios::app);
	cout<<"Please enter what you want to buy...."<<endl;
	do
	{
		string s;int num;
		cout<<"Product Name? ";
		cin.ignore();
		getline(cin,s);
		cout<<"Quantity? ";
		cin>>num;
		int x=searchProQuan(&head,s,num);
		if(x==1)
		{
			fout<<reg<<","<<s<<"("<<num<<")"<<"\n";
		}
		else if(x==0)
		{
			cout<<"Sorry we don't have the product. Do you want to give order?(Y/n)";
			char ch;
			cin>>ch;
			if(ch=='Y'||ch=='y')
			order(s);
		}
		else
		{
			cout<<"Sorry we only have "<<x<<" "<<s<<endl;
			cout<<"Do you want to buy?(Y/n)";
			char c;
			cin>>c;
			if(c=='y'||c=='Y')
			fout<<reg<<","<<s<<"("<<x<<")"<<"\n";
		}
		cout<<"Do you want to buy more?(Y/n)";
		cin>>d;
		cout<<endl;

	}while(d=='Y'||d=='y');
}
void readProductFile()
{
	int count=0;
	fstream fin;
	fin.open("productbuy.csv",ios::in);
	if(!fin)
	{
		cout<<"Error no such file";
		getch();
		return;
	}
	vector<string> row;
	string line,word,temp;
	while(fin.good())
	{
		count=1;
		getline(fin,line);
		stringstream s(line);
		while(getline(s,word,','))
		{
			row.push_back(word);
		}
		vector<string>::iterator ptr;
		cout<<"->";
		for(ptr=row.begin();ptr<row.end();ptr++)
		cout<<*ptr<<" - ";
		cout<<endl;
	}
	getch();
}
void retail_menu()
{
    string f;int n1;
	system("CLS");
	cout<<"\n\t\t1.Create a Retailer entry";
	cout<<"\n\t\t2.Show All retailer Information";
	cout<<"\n\t\t3.Buy product?";
	cout<<"\n\t\t4.Product Selling Information";
	cout<<"\n\t\t5.EXIT";

	cout<<"\n\nPLEASE ENTER YOUR CHOICE ---";
	cin>>n1;
	switch(n1)
	{
		case 1:system("CLS");
				writeRetailFile();
				break;
		case 2:system("CLS");
				cout<<"\n************************  RETAILER INFORMATION **************************\n";
				readRetailFile();
				break;
		case 3:system("CLS");
				cout<<"Enter the registration No of the Retailer - ";
				cin>>f;
				cout<<"\nThank you\n";
				productbuy(f);
				break;
		case 4:system("CLS");
				cout<<"************************  SELLING INFORMATION ****************************"<<endl;
				cout<<"Registration No.\t\t\t Products(Quantities)\t\n";
				readProductFile();
				break;
		case 5:system("CLS");
				return;
		default:cout<<"\a";
	}
	retail_menu();

}
void whole_menu()
{
	string na;long bar;
	system("CLS");
	cout<<"\n************************************Wholesaler Menu******************************"<<endl;
	cout<<"\n\t\t1.CREATE PRODUCT ENTRY";
	cout<<"\n\t\t2.VIEW ALL PRODUCTS";
	cout<<"\n\t\t3.SEARCH PRODUCT BY NAME";
	cout<<"\n\t\t4.SEARCH PRODUCT BY DESCRIPTION";
	cout<<"\n\t\t5.SEARCH PRODUCT BY BARCODE";
	cout<<"\n\t\t6.DELETE PRODUCT";
	cout<<"\n\t\t7.VIEW ORDER LIST";
	cout<<"\n\t\t8.EXIT";
	cout<<"\n\nPlease enter a correct choice:- ";
	int a;
	cin>>a;
	switch(a)
	{
		case 1:system("CLS");
			writeFile();
			break;
		case 2:system("CLS");
			showAllProducts(&head);
			break;
		case 3:system("CLS");
			cout<<"Enter product name - ";
			cin.ignore();
			getline(cin,na);
			cout<<endl;
			searchProduct(&head,na);
			break;
		case 4:system("CLS");
			cout<<"Enter description - ";
			cin.ignore();
			getline(cin,na);
			cout<<endl;
			searchDescription(&head,na);
			break;
		case 5:system("CLS");
			cout<<"Enter Barcode - ";
			cin>>bar;
			cout<<endl;
			searchBarcode(&head,bar);
			break;
		case 6:system("CLS");
			cout<<"Enter product name - ";
			cin.ignore();
			getline(cin,na);
			deleteProduct(&head,na);
			break;
		case 7:system("CLS");
			readOrder();
			break;
		case 8:return;
		default:cout<<"\a";
	}
	whole_menu();
}
void intro()
{
	system("CLS");
	cout<<"\n\n\t\t\t1.RETAILER MENU";
	cout<<"\n\n\t\t\t2.WHOLESALER MENU";
	cout<<"\n\n\t\t\t3.EXIT";
	cout<<"\n\nPlease enter your choice - ";
	int h;
	cin>>h;
	switch(h)
	{
		case 1:retail_menu();
				break;
		case 2:whole_menu();
				break;
		case 3:return;
		default:cout<<"\a";
	}
	intro();
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
int main()
{
    readFile();
	cout<<"\n\n\n\n\n\t\t\t\tWELCOME\t\t\t\t\t\t\t\n\n\n";
	cout<<"NAME - ";
	cout<<"Registration no. - -";
	cout<<"VIT University, Vellore - 632014";
	delay(2);
	intro();
	return 0;
}
