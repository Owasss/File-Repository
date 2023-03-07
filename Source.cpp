#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#include<list>
#include<string>


using namespace std;
template <typename k, typename u, typename o>
class items		//Data of user
{
public:
	k key;		//Priority
	u id;		//USer id
	o op;		//Operation type

	items()		//Deafault CONSTRUCTOR
	{
		key = 0;
		id = 0;
		op = '\0';
	}

	items(k key, u id, o op)		//Paramterized Constructor
	{
		this->key = key;
		this->id = id;
		this->op = op;
	}
	//friend ostream & operator <<(ostream & out ,const items<k,u,o> & obj);
};
//template <typename k,typename u,typename o>
//ostream & operator <<(ostream & out ,const items<k,u,o> & obj)
//{
//		out<<obj.key<<"\t"<<obj.id<<"\t"<<obj.op<<endl;
//		return out;
//}
template <typename k, typename u, typename o> //TO SORT THE VECTOR(MAINTAING IT AS A MAX HEAP)
struct HeapType
{
	bool operator()(items<k, u, o>& p, items<k, u, o>& p2)
	{
		return p.key > p2.key;
	}
};

template<typename k, typename u, typename o>
class priority
{               
public:
	//items<k,u,o> it;
	vector<items<k, u, o>> v;  // VECTOR FOR QUEUE OF USERS

	priority()
	{}
	priority(vector<items<k, u, o>> m)
	{
		v = m;
	}
	void Insert(k key, u id, o op)  // INSERTION IN QUEUE OF VECTORS
	{
		items<k, u, o> x(key, id, op);
		v.push_back(x);
		buildHeap();  // AFTER INSERTING MAINTAING THE MAX HEAP
	}

	void buildHeap()
	{
		make_heap(v.begin(), v.end(), HeapType<k, u, o>());
		sort_heap(v.begin(), v.end(), HeapType<k, u, o>());
	}  // HEAPIFY

	int mySize()  // FOR SIZE OF VECTOR
	{
		return v.size();
	}

	void printpriority()//DISPLAY
	{
		cout << "PABLO " << endl;

		for (auto i = v.begin(); i != v.end(); i++)
		{
			cout << i->key << "	" << i->id << "	" << i->op << endl;
		}
	}   
	items<k, u, o> extract_max()
	{
		items<k, u, o> n = v[0];
		v[0] = v[v.size() - 1];
		v.erase(v.begin());
		buildHeap();
		return n;
	}     

	void Find_min()
	{
		vector<items<int, int, char>>::iterator it = v.end();
		cout << "Min key is : " << it.key;
		cout << "ID at Min key is : " << it.id;
	}   //AS WE SORTED VECTOR IN DECREASING ORDER ,MAINTAING IT AS MAX HEAP, LAST ELEMENT WILL BE THE MINIMUM ONE

	items<k, u, o> Find_max()
	{
		return v[0];
	} // TOP IS MAXIMUM IN MAX HEAP

	bool IsEmpty(vector<items<k, u, o>>& v)
	{
		return v.empty();
	}
	void printmyvector()
	{
		for (auto i = v.begin(); i != v.end(); i++)
		{
			cout << i->key << "	" << i->id << "	" << i->op << endl;
		}
	}
};

template <typename k, typename u, typename o>
class hashItem  // FOR FILE
{
public:
	int file_id;  // DATA MEMBERS
	priority<k, u, o> p;// QUEUE FOR USERS WITH ACCESS
	priority<k, u, o> p1;//WAITING USERS
	hashItem() //DEFULT CONST
	{
		file_id = 0;
	}

	hashItem(int id, priority<k, u, o> pr, priority<k, u, o> pr1)
	{
		this->file_id = id;
		this->p = pr;
		this->p1 = pr1;
		//this->p.it.key=pr.it.key;
		//this->p.it.op=pr.it.op;
	}

	void printhashitem()
	{
		cout << "File id : " << file_id << endl;
		p.printpriority();
		p1.printpriority();
	}//DISPLAY 
};
template <typename k, typename u, typename o>
class hashTable
{
public:
	list<hashItem<k, u, o>> arr[10];//TABLE SIZE IS 10
	int tablesize;
	void printHashTable()
	{
		for (int i = 0; i < tablesize; i++)
		{
			cout<<endl;
			cout << "H" << i << "-->";
			auto it = arr[i].begin();
			for ( it = arr[i].begin(); it != arr[i].end(); it++)
			{
				cout << "FILE " << it->file_id << "\t";
				cout << "Access granted to user   ";
				for (int a = 0; a < it->p.v.size(); a++)
				{
					cout << it->p.v[a].id << " ";
				}
				cout << endl;
				int a;
				cout << "NEXT User   ";
				for (a = 0; a < it->p1.mySize(); a++)
				{
					if (a == 0)
						cout << it->p1.v[a].id << " ";
				}
				cout << "Waiting " << a << " users" << endl;
				cout << endl;
				//break;
				cout << endl;
			}
		}
	}
	hashTable(int a = 10)
	{
		tablesize = a;
	}

	int calcHash(int f_id)
	{
		return f_id % 10;
	} //CALCULATING INDEX

	bool insertItem(hashItem<k,u,o> obj)//INSERTION IN HASH TABLE
	{
		if(obj.file_id>=5000 && obj.file_id<=99999)
		{
			int index = calcHash(obj.file_id);
			auto l = arr[index].begin();
			bool check=false;
			for (l = arr[index].begin(); l != arr[index].end(); l++) 
			{
				if (obj.file_id== l->file_id)
				{
					check = true;
					return false;
				}
			}
			if (check == false) 
			{
				arr[index].push_back(obj);
				return true;
			}
			else
			{
				cout << "FILE ALREADY INSERTED" << endl;   //CHECK FOR REPEATITION
				return false;
			}
		}
		else
			cout<<"The file_ID is not valid\n";
	}

	void access(int userid, int file_id, int pri, char oper) // FUNCTION FOR REQUEST OF ACCESS
	{

		int index = calcHash(file_id);
		bool flag = false;
		for (auto it = arr[index].begin(); it != arr[index].end(); it++)
		{
			if (it->file_id == file_id)
			{
				flag = true;
				if (it->p.v.empty())
					it->p.Insert(pri, userid, oper);   // INSERTION IN ARRARY WITH ACCESS GRANTED USERS
				else if (it->p.v[0].op == 'R' && oper == 'R')
					it->p.Insert(pri, userid, oper);
				else
					it->p1.Insert(pri, userid, oper); // INSERTION IN WAITING LIST
				cout << "---------------------ACCESS of File : " << file_id << " GRANTED to USER : " << userid << "---------------------" << endl;
				break;
			}
		}
		if (!flag)
		{
			cout << "------------------------------------Error Encountered----------------------------------" << endl;
		}
	}
	void Print()
	{
		for (int i = 0; i < tablesize; i++)
		{
			for (auto it = arr[i].begin(); it != arr[i].end(); ++it)
			{
				it->printhashitem();
			}
		}
	}

	void release(int userid, int file_id)  //FOR REMOVING USERS FROM QUEUE WO RELEASED THE FILE
	{

		int index = calcHash(file_id);
		bool granted = true;
		bool user_flag = false;
		if (arr[index].begin() == arr[index].end()) {
			cout << "LIST EMPTY " << endl;
			return;
		}
		auto it = arr[index].begin();
		for (it = arr[index].begin(); it != arr[index].end(); ++it)
		{

			if (it->file_id == file_id)
			{
				granted = false;
				break;
			}
		}
		int i;
		for (i = 0; i < it->p.mySize(); i++)
		{
			if (it->p.v[i].id == userid)
			{
				user_flag = true;
				break;
			}
		}
		if (user_flag == true)
		{
			it->p.v.erase(it->p.v.begin() + i);
			if (it->p.v.empty())
			{
				if (!it->p1.v.empty())
				{
					if (it->p1.v[0].op == 'W')
					{
						it->p.v.push_back(it->p1.v.front());
						it->p1.v.erase(it->p1.v.begin()+0);
						cout << "----------------------FILE RELEASED---------------------" << endl;
						return;
					}

					int index = 0;
					auto a = it->p1.v.begin();
					if (a->op == 'R')
					{
						while(it->p1.v.empty()!=1)
						{
						
							it->p.v.push_back(it->p1.v.front());
							it->p1.v.erase(it->p1.v.begin()+0);
							if(it->p1.v.empty()!=1)
							{
								a = it->p1.v.begin();
								if (it->p1.v.front().op == 'W')
									break;
							}
							else break;
						}
					}
				}
				cout << "----------------------FILE RELEASED---------------------" << endl;
				//break;
			}
		}
		/*else
			cout << "USER NOT FOUND\n";*/
		if (granted)
		{
			cout << "------------------------------------Error Encountered----------------------------------" << endl;
		}
	}
	void DeleteAfile(int fileid) //DELETION OF FILE
	{
		bool d = false;
		for (int INDEX = 0; INDEX < tablesize; INDEX++)
		{
			auto itr = arr[INDEX].begin();
			int i = 0;
			for (itr = arr[INDEX].begin(); itr != arr[INDEX].end(); itr++)
			{
				if (itr->file_id == fileid && itr->p.v.empty() == 1)
				{
					arr[INDEX].erase(itr);
					d = true;
					break;
				}
				i++;
			}
			if (d == true)
			{
				cout << "File Deleted Successfully!" << endl;
				break;
			}
			else
				cout<<"File Is Not Deleted\n";
			//ELSE ACCESSED GRANTED ARRAY WAS NOT EMPTY SO CAN NOT DELETE FILE
		}
	}

	void load(string filename)
	{
		int fi, ui, pr;
		char c;
		priority<k, u, o> p;
		priority<k, u, o> p1;
		hashItem<int, int, char> h;
		hashItem<int, int, char> h1;
		hashTable<int, int, char> oo;

		fstream f(filename, ios::in);
		if (f.is_open())
		{
			cout << "-------------------File named : " << filename << " has Opened Successfully---------------" << endl;
			while (!f.eof())
			{
				while (f >> fi) {
					f >> ui;
					f >> pr;
					f >> c;
					h.file_id = fi;
					oo.insertItem(h);
					/*p.Insert(pr,ui,c);
					h.insertitem(fi,p,p1);
					o.insertItem(h);*/
					if (c == 'W')
					{
						oo.access(ui, fi, pr, 'W');
					}
					else if (c == 'R')
					{
						oo.access(ui, fi, pr, 'R');

					}
				}
			}

		}
		else
		{
			cout << "---------------------------------Unable to Access File named : " << filename << " ---------------------------" << endl;
			cout << "-------Make Sure You have placed the file in correct directory and named it correctly--------" << endl;
		}
		*this = oo;
	}
	void menu()		//Menu of the hash table
	{
		int i=0;
		hashItem<k, u, o>obj;
		char option;
		cout << "---------------------------------------------- MENU ---------------------------------------------------------------\n";
		cout << "YOUR MENU IS\n";
		cout << "PRESS A TO GET THE ACCESS TO A FILE "<<endl;
		cout << "PRESS L TO LOAD THE DATA "<<endl;
		cout << "PRESS I TO INSERT THE FILE "<<endl;
		cout << "PRESS D TO DELETE THE FILE "<<endl;
		cout << "PRESS P TO PRINT THE HASH TABLE "<<endl;
		cout << "PRESS R TO RELEASE THE FILE "<<endl;
		cout << "PRESS T TO TERMINATE THE PROGRAM"<<endl;
		option = '\0';
		while (option != 'T')
		{
			cin>>option;

			if(option=='P')
			{
				printHashTable();
			}
			else if(option=='L')
			{
				load("Demo1.txt");
			}
			else if(option=='I')
			{
				int file_Id;

				cout << "ENTER File Id You WAnt to Insert"<<endl;
				cin >> file_Id;
				obj.file_id=file_Id;
				insertItem(obj);
			}
			else if(option=='D')
			{
				int Fileid;
				cout << "Enter File Id TO DELETE"<<endl;
				cin >> Fileid;
				DeleteAfile(Fileid);
			}
			else if(option=='A')
			{
				int user_id, fileid, pri;
				char accessType;
				cout << "Enter User Who Access the File"<<endl;
				cin >> user_id;
				cout << "Enter File Id which you Wants to Access"<<endl;
				cin >> fileid;
				cout << "Enter user's priority"<<endl;
				cin >> pri;
				cout << "Enter The Access Type R to Read the File and W to Write in the File"<<endl;
				cin >> accessType;
				access(user_id, fileid, pri, accessType);
			}
			else if(option=='R')
			{
				int user_ID, Fileid;
				cout<<"Enter User Who RELEASE the File"<<endl;
				cin>>user_ID;
				cout<<"Enter File Id to be Released"<<endl;
				cin>>Fileid;
				release(user_ID,Fileid);
			}
			else
				cout << "INVALID COMMAND ENTERED"<<endl;
		}
	}
};

int main()
{
	hashTable<int, int, char> obj;
	obj.menu();
	system("pause");
	return 0;
}