#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;
class cont
{
	char name[100];
	char address[100];
	long long phoneno;
	public:
		void read()
		{
			cout<<"\n\n\n\n\t\t\t\tEnter name:";
			cin.ignore();
			cin.get(name,100);
			cout<<"\t\t\t\tEnter address:";
			cin.ignore();
			cin.get(address,100);
			cout<<"\t\t\t\tEnter phoneno:";
			cin>>phoneno;
		}
		void show()
		{
			cout<<"\n\t\t\t\tNAME:"<<name<<endl;
			cout<<"\t\t\t\tADDRESS:"<<address<<endl;
			cout<<"\t\t\t\tPHONE NO:"<<phoneno<<endl;
		}
		void write2file()
		{
			ofstream infile("record.dat",ios::binary|ios::app);
			read();
			infile.write(reinterpret_cast<char*>(this),sizeof(*this));
		}
		void showall()
		{
			cout<<"\n\n\t\t NAME\t\t     ADDRESS\t        PHONE N0"<<endl;
			cout<<"\n"<<endl;
			ifstream outfile("record.dat",ios::binary);
			while(!outfile.eof())
			{
				if(outfile.read(reinterpret_cast<char*>(this),sizeof(*this))>0)
				{
					cout<<setw(25)<<name<<setw(25)<<address<<setw(15)<<phoneno<<endl;
				}
			}
		}
		void showone()
		{
			ifstream infile("record.dat",ios::binary);
			char search[100];
			cout<<"\n\n\t\t\t\tEnter the name you want to search:";
			cin.ignore();
			cin.get(search,100);
			infile.seekg(0,ios::end);
			int count=infile.tellg()/sizeof(*this);
			infile.seekg(0,ios::beg);
			int n=2;
			int flag=0;
			while(!infile.eof())
			{
				if(infile.read(reinterpret_cast<char*>(this),sizeof(*this))>0)
				{
					if(strcmp(name,search)==0)
					{
					infile.seekg((n-1)*sizeof(*this));
					show();
					flag=1;
					break;	
					}
					n++;
				}
			}
			if(flag==0)
			{
				cout<<"\n\n\t\t\t\tThere is no such contact"<<endl;
			}
		}
		void modify()
		{
			fstream inoutfile("record.dat",ios::binary|ios::out|ios::in);
			char search[100];
			cout<<"\n\n\t\t\tEnter the name you want to edit:";
			cin.ignore();
			cin.get(search,100);
			inoutfile.seekg(0,ios::end);
			int count=inoutfile.tellg()/sizeof(*this);
			inoutfile.seekg(0,ios::beg);
			int n=1;
			int flag=0;
			while(!inoutfile.eof())
			{
				if(inoutfile.read(reinterpret_cast<char*>(this),sizeof(*this))>0)
				{
					if(strcmp(name,search)==0)
					{
					flag=1;
					break;	
					}
					n++;
				}
			}
			if(inoutfile.eof())
			inoutfile.clear();
			int location=(n-1)*sizeof(*this);
			inoutfile.seekp(location);
			if(flag==1)
			{
				read();
				inoutfile.write(reinterpret_cast<char*>(this),sizeof(*this));
			}
			else
			{
				cout<<"\n\n\t\t\t\tThere is no such contact"<<endl;	
			}
			inoutfile.close();
			if(flag==1)
			{
				showall();
			}
		}
		void deleter()
		{
			ofstream infile("temp.dat",ios::binary|ios::in|ios::app);
			fstream inoutfile("record.dat",ios::binary|ios::out|ios::in);
			char search[100];
			cout<<"\n\n\n\t\t\tEnter the name you want to delete:";
			cin.ignore();
			cin.get(search,100);
			int flagg=1;
			while(!inoutfile.eof())
			{
				if(inoutfile.read(reinterpret_cast<char*>(this),sizeof(*this))>0)
				{
					if(strcmp(name,search)!=0)
					{
						infile.write(reinterpret_cast<char*>(this),sizeof(*this));	
					}
					else
					{
						flagg=0;
					}
				}
			}
			inoutfile.close();
			infile.close();
			remove("record.dat");
			rename("temp.dat","record.dat");
			if(flagg==1)
			{
				cout<<"\n\n\t\t\t\tThere is no such contact"<<endl;
			}
			else
			{
				cout<<"\n\n\t\t\t\tThe File name "<<search<<" has been deleted"<<endl;
				showall();
			}
		}
};
int main()
{
	while(1)
	{
		system("CLS");
		cont c;
		int choice;
		cout<<"\n\n\t\t\t\tContact Dairy:";
		cout<<"\n\n\n\n\t\t\t\tEnter 1 to add new contact"<<endl;
		cout<<"\t\t\t\tEnter 2 to show all contact"<<endl;
		cout<<"\t\t\t\tEnter 3 to show one contact"<<endl;
		cout<<"\t\t\t\tEnter 4 to edit contacts"<<endl;
		cout<<"\t\t\t\tEnter 5 to delete contact"<<endl;
		cout<<"\t\t\t\tEnter 0 to exit"<<endl;
		cout<<"\n\t\t\t\tEnter choice:";
		cin>>choice;
		switch(choice)
		{
			case 1: system("CLS");
					c.write2file();
					cout<<"\n\n\t\t\t\tPress Enter to go MAIN PAGE";
					getch();
					break;
					
			case 2:	system("CLS");
					c.showall();
					cout<<"\n\n\t\t\t\tPress Enter to go MAin Page";
					getch();
					break;
					
			case 3:	system("CLS");
					c.showone();
					cout<<"\n\n\t\t\t\tPress Enter to go MAin Page";
					getch();
					break;
						
			case 4:	system("CLS");
					c.modify();	
					cout<<"\n\n\t\t\t\tPress Enter to go MAin Page";
					getch();
					break;
						
			case 5: system("CLS");
					c.deleter();
					cout<<"\n\n\t\t\t\tPress Enter to go MAin Page";
					getch();
					break;
					
			case 0:exit(0);
			
			default:cout<<"Not a valid choice";
					cout<<"\t\t\t\tPress Enter to go MAIN PAge";
					getch();
					break;
		}
	}
}
