#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<conio.h>
#include<iomanip>//input-output manipulator
#include<stdlib.h> 
#include<string.h>
#include<stdio.h>

using namespace std;
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}
class book
{
	char bno[6];//bookno.
	char bname[50];//bookname
	char aname[20];//authorname
	public:
	void createbook()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nENTER BOOK NO. ";
		cin>>bno;
		cout<<"\nENTER BOOK NAME ";
        cin>>bname;
		gets(bname);//enables enter with space
		cout<<"\nENTER AUTHOR NAME ";
        cin>>aname;
	gets(aname);
		cout<<"\n\n\nBook Created..";
	}
	void showbook()
	{
		cout<<"\nBook Number : "<<bno;
		cout<<"\nBook Name: "<<bname;
		puts(bname);
		cout<<"\nBook Author Name: "<<aname;
		puts(aname);
	}
	void modifybook()
	{
		cout<<"\nBook Number: "<<bno;
		cout<<"\nModify Book Name :";
		gets(bname);
		cout<<"\nModify Author's Name :";
		gets(aname);
		
	}
	
	char* retbno()//string return
	{
		return bno;
	
	}
	void report()
	{
		cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}
};//class ends here

class student
{
	char admno[6];//admission no.
	char name[20];
	char stbno[6];// student book no 
	int token;//total book of student
	public:
	void createstudent()
	{
		clearScreen();

		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The Admission No. ";
		cin>>admno;
		cout<<"Enter The Student Name ";
        cin>>name;
		// gets(name);
		token=0;
		stbno[0]='\0';
		cout<<"\n\n\nStudent Record Created...";
	}
	void showstudent()
	{
		cout<<"\nAdmission Number : "<<admno;
		cout<<"\nStudent Name : "<<name;
		// puts(name);
		cout<<"\nNo of Book Issued : "<<token;
		if(token==1)
		{
			cout<<"\nBook Number "<<stbno;
		}
	}
	void modifystudent()
	{
		cout<<"\nAdmission No. "<<admno;
		cout<<"\nModify Student Name : ";
		gets(name);
	}
	char* retadmno()
	{
		return admno;
	}
	char* retstbno()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token=1;
	}
	void resettoken()
	{ 
	token=0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}
	void report()
	{
		cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl ;
	}
};//class ends here
fstream fp,fp1;//object
book bk;//book class object
student st;//student class object

void writebook()
{
	char ch;
	fp.open("books.txt",ios::out|ios::app);//write and append data
	do{
		clearScreen();
		bk.createbook();
		fp.write((char*)&bk,sizeof(book));//size of class
		cout<<"\n\nDo you want to add more record...(y/n?) ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void writestudent()
{
    char ch;
    fp.open("students.txt",ios::out|ios::app);//write and append data
    do{
        clearScreen();
        st.createstudent();
        fp.write((char*)&st,sizeof(student));//size of class
        cout<<"\n\nDo you want to add more record...(y/n?) ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void displayspb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;//book not found
    fp.open("books.txt",ios::in);//read data
    while(fp.read((char *)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)//not case sensitive
        {
            bk.showbook();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)//book not found
    {
        cout<<"\n\nBook does not exist";
    }
    getch();
}

void displaysps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;//student not found
    fp.open("students.txt", ios::in);//read data
    while(fp.read((char *)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)==0)//not case sensitive
        {
            st.showstudent();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)//student not found
    {
        cout<<"\n\nStudent does not exist";
    }
    getch();
}

void modifybook()
{
    char n[6];
    int found=0;//seach book of given data
    clearScreen();
    cout<<"\n\nMODIFY BOOK RECORD...";
    cout<<"\n\nEnter the book no. ";
    cin>>n;
    fp.open("books.txt",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.showbook();
            cout<<"\nEnter the new details book";
            bk.modifybook();
            int pos=-1*sizeof(bk);
            fp.seekp(pos,ios::cur);//back from current position
            fp.write((char *)&bk,sizeof(book));
            cout<<"\n\nRecord Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
    {
        cout<<"\n\nRecord Not Found";
    }
    getch();//press key to get out
}

void modifystudent()
{
    char n[6];
    int found = 0; // search student of given data
    clearScreen();
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no. ";
    cin >> n;
    fp.open("students.txt", ios::in | ios::out);
    fp.read((char*)&st, sizeof(student));
    while (!fp.eof() && found == 0)
    {
        if (strcmpi(st.retadmno(), n) == 0)
        {
            st.showstudent();
            cout << "\nEnter the new details of student";
            st.modifystudent();
            fp.seekp(-sizeof(student), ios::cur); // move back to the beginning of the current record
            fp.write((char *)&st, sizeof(student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
        else
        {
            fp.read((char*)&st, sizeof(student));
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found";
    }
    getch(); // press key to get out
}

void deletestudent()
{
    char n[6];
    int flag=0;
    clearScreen();
    cout<<"\n\n\n\tDELETE STUDENT...";
    cout<<"\n\nEnter the Admission no> : ";
    cin>>n;
    fp.open("students.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.txt",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=0)
        {
            fp2.write((char*)&st,sizeof(student));
        }
        else{
            flag=1;//student found
        }
    }
    fp2.close();
    fp.close();
    remove("students.txt");
    rename("temp.txt","students.txt");//data after deletion moved to temp
    if(flag==1)
    {
        cout<<"\n\n\tRecord Deleted..";
    }
    else
    {
        cout<<"Record not Found";
    }
    getch();
}

void deletebook()
{
    char n[6];//book no.
    int flag=0;
    clearScreen();
    cout<<"\n\n\n\tDELETE BOOK...";
    cout<<"\n\nEnter the Book no> : ";
    cin>>n;
    fp.open("books.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.txt",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(book));
        }
        else{
            flag=1;//book found
        }
    }
    fp2.close();
    fp.close();
    remove("books.txt");
    rename("temp.txt","books.txt");//data after deletion moved to temp
    if(flag==1)
    {
        cout<<"\n\n\tRecord Deleted..";
    }
    else
    {
        cout<<"Record not Found";
    }
    getch();
}

void bookissue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    clearScreen();
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter the student's admission no. ";
    cin>>sn;
    fp.open("students.txt",ios::in|ios::out);
    fp1.open("books.txt",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                cout<<"\n\n\tEnter the book no. ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    if(strcmpi(bk.retbno(),bn)==0)
                    {
                        bk.showbook();
                        flag=1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\tBook issued successfully...";
                    }
                }
                if(flag==0)
                {
                    cout<<"Book no does not exist";
                }
            }
            else
            {
                cout<<"\n\n\tYou have not returned the last book ";
            }
        }
    }
    if(found==0)
    {
        cout<<"\n\n\tStudent record not found ";
    }
    getch();
    fp.close();
    fp1.close();
}

void bookdeposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clearScreen();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter the student's admission no. ";
    cin>>sn;
    fp.open("students.txt",ios::in|ios::out);
    fp1.open("books.txt",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    if(strcmpi(bk.retbno(),st.retstbno())==0)
                    {
                        bk.showbook();
                        flag=1;
                        cout<<"\n\nBook deposited in no. of days";
                        cin>>day;
                        if(day>15)
                        {
                            fine=(day-15)*1;
                            cout<<"\n\nFine Rs. "<<fine;
                        }
                        st.resettoken();
                        int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\tBook deposited successfully...";
                    }
                }
                if(flag==0)
                {
                    cout<<"Book no does not exist";
                }
            }
            else
            {
                cout<<"\n\n\tNo book is issued..please check";
            }
        }
    }
    if(found==0)
    {
        cout<<"\n\n\tStudent record not found ";
    }
    getch();
    fp.close();
    fp1.close();
}
void displayalls();
void displayallb();

void adminmenu()
{
    int ch2;
    clearScreen();
    cout<<"\n\nADMIN MENU";
    cout<<"\n\n1.CREATE STUDENT RECORD";
    cout<<"\n2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n4.MODIFY STUDENT RECORD";
    cout<<"\n5.DELETE STUDENT RECORD";
    cout<<"\n6.CREATE BOOK ";
    cout<<"\n7.DISPLAY ALL BOOKS ";
    cout<<"\n8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n9.MODIFY BOOK ";
    cout<<"\n10.DELETE BOOK ";
    cout<<"\n11.BACK TO MAIN MENU";
    cout<<"\n\nEnter your choice(1-11) ";
    cin>>ch2;
    switch(ch2)
    {
        case 1:
            writestudent();
            break;
        case 2:
            displayalls();
            break;
        case 3:
            int x;
            char n[6];
            cout<<"\n\nEnter Admission No. ";
            cin>>n;
            displaysps(n);
            break;
        case 4:
            modifystudent();
            break;
        case 5:
            deletestudent();
            break;
        case 6:
            writebook();
            break;
        case 7:
            displayallb();
            break;
        case 8:
            char m[6];
            cout<<"\n\nEnter Book No. ";
            cin>>m;
            displayspb(m);
            break;
        case 9:
            modifybook();
            break;
        case 10:
            deletebook();
            break;
        case 11:
            return;
        default:
            cout<<"\a";
    }
    adminmenu();
}

void studentmenu()
{
    int ch3;
    clearScreen();
    cout<<"\n\nSTUDENT MENU";
    cout<<"\n\n1.VIEW BOOK LIST";
    cout<<"\n2.SEARCH BOOK ";
    cout<<"\n3.ISSUE BOOK ";
    cout<<"\n4.RETURN BOOK ";
    cout<<"\n5.BACK TO MAIN MENU";
    cout<<"\n\nEnter your choice(1-5) ";
    cin>>ch3;
    switch(ch3)
    {
        case 1:
            displayallb();
            break;
        case 2:
            char sn[6];
            cout<<"\n\nEnter Book No. ";
            cin>>sn;
            displayspb(sn);
            break;
        case 3:
            bookissue();
            break;
        case 4:
            bookdeposit();
            break;
        case 5:
            return;
        default:
            cout<<"\a";
    }
    studentmenu();
}
void displayalls()
{
    fp.open("students.txt", ios::in);
    if (!fp)
    {
        cout << "Error opening file";
        return;
    }
    fp.read((char*)&st, sizeof(student));
    while (!fp.eof())
    {
        st.showstudent();
        fp.read((char*)&st, sizeof(student));
    }
    fp.close();
    getch();
}

void displayallb()
{
    fp.open("books.txt", ios::in);
    if (!fp)
    {
        cout << "Error opening file";
        return;
    }
    fp.read((char*)&bk, sizeof(book));
    while (!fp.eof())
    {
        bk.report();
        fp.read((char*)&bk, sizeof(book));
    }
    fp.close();
    getch();
}

int main()
{
    int ch;
    clearScreen();
    cout<<"\n\nMAIN MENU";
    cout<<"\n\n1.ADMINISTRATOR";
    cout<<"\n2.STUDENT";
    cout<<"\n3.EXIT";
    cout<<"\n\nEnter your choice(1-3) ";
    cin>>ch;
    switch(ch)
    {
        case 1:
            adminmenu();
            break;
        case 2:
            studentmenu();
            break;
        case 3:
            exit(0);
        default:
            cout<<"\a";
    }
    return 0;
}