#include<bits/stdc++.h>
using namespace std;



/* ********************************************************************************************************************************** */
															/*Node Class*/
template<typename Type>
class Node
{
	private:
		Type nodeValue;
		Node<Type>* next;
		Node<Type>* previous;
	public:
	    Node();
		void setData(Type data);
		void setData(Type value,Node<Type>* nextAddress,Node<Type>* previousAddress);
		Type getData();
		void setNextAddress(Node<Type>* address);
		void setPreviousAddress(Node<Type>* address);
		Node<Type>* getNextNodeAddress();
		Node<Type>* getPreviousNodeAddress();
		Node<Type>* getNodeAddress();
};

template<typename Type>
Node<Type> :: Node()
{
    previous = next = NULL;
}

template<typename Type>
void Node<Type> :: setData(Type value,Node<Type>* nextAddress,Node<Type>* previousAddress)
{
	this->nodeValue = value;
	this->next = nextAddress;
	this->previous = previousAddress;
}

template<typename Type>
void Node<Type> :: setData(Type data)
{
	this->nodeValue = data;
}

template<typename Type>
Type Node<Type> :: getData()
{
	return this->nodeValue;
}

template<typename Type>
void Node<Type> :: setNextAddress(Node<Type>* address)
{
	this->next = address;
}

template<typename Type>
void Node<Type> :: setPreviousAddress(Node<Type>* address)
{
	this->previous = address;
}


template<typename Type>
Node<Type>* Node<Type> :: getNextNodeAddress()
{
	return this->next;
}

template<typename Type>
Node<Type>* Node<Type> :: getPreviousNodeAddress()
{
	return this->previous;
}

template<typename Type>
Node<Type>* Node<Type> :: getNodeAddress()
{
	return this;
}



/*  ********************************************************************************************************************************  */
											/*		Linked List Class	*/



template<typename Type>
class LinkedList			//Implemented as Doubly Linked List
{

	private:
		Node<Type>* head;
		Node<Type>* end;
		int size;

		void reverseList(Node<Type>* currentNode);
	public:

		/*	*********************************************************************************************	*/
									/*	Iterator Class (Nested Class)	*/
		class Iterator
		{
		private:
			Node<Type>* currentNode;
			Node<Type>* previousNode;
			int position;
			int type;
            static const int FORWARD,BACKWARD;
		public:
			Iterator(){}
			Iterator(Node<Type>* node)		//How to define these functions outside class?
			{
				this->currentNode = node;
				this->previousNode = NULL;
				position = 0;
				type = FORWARD;
			}

            Iterator(Node<Type>* node,int type,LinkedList<Type>& lst)
            {
                this->currentNode = node;
                this->previousNode = NULL;
                this->type = type;
                if(type == FORWARD)
                {
                    position = 0;
                }
                else if(type == BACKWARD)
                {
                    position = lst.getSize()-1;
                }
            }
			Node<Type>* operator*()
			{
				return currentNode;
			}
			void operator++()
			{
			    if(type == FORWARD)
                {
                    previousNode = currentNode;
                    currentNode = currentNode->getNextNodeAddress();
                    position++;
                }
                else if(type == BACKWARD)
                {
                    previousNode = currentNode;
                    currentNode = currentNode->getPreviousNodeAddress();
                    position--;
                }
			}
			bool operator!=(Iterator iterator)
			{
				return (this->previousNode != iterator.currentNode);
			}

			int getCurrentPosition()
			{
				return position;
			}
		};
	public:
		LinkedList();
//		LinkedList(LinkedList<Type>& lst);  //Copy Constructor,creates a new list from the given list
		LinkedList(Iterator first,Iterator last);   //Creates a list from passed starting position to ending position of list
		LinkedList(int listSize,Type inputValue);   //Creates List with Given Size with all its elements being passed Value
		void push_back(Type data);
		void push_front(Type data);
		void pop_front();
		void pop_back();
		void insert(Type data,int position);
		void reverse();
		void remove(Type data);	//Removing first occurance of the given data from the list
		void remove(Iterator position);	//Removing data at a given position
		Type getElementAtPosition(Iterator position);
		void splice(Iterator position,LinkedList<Type>& lst);
		void splice(Iterator position,LinkedList<Type>& lst,Iterator element);
		//TODO: What if first iterator occurs after last iterator in the original list(i.e. 10 20 30,first points to 30 and last points to 10)
		void splice(Iterator position,LinkedList<Type>& lst,Iterator first,Iterator last);
		void sort( bool (*compare)(Type,Type) );
		int getSize();
		void clear();
		bool empty();

		Iterator Begin()		//How to define it outside class?
		{
			Iterator it = Iterator(head);
			return it;
		}
		Iterator End()
		{
			Iterator it = Iterator(end);
			return it;
		}

		Iterator crBegin()
		{
		    Iterator it = Iterator(end,2,*this);
		    return it;
		}

		Iterator crEnd()
		{
            Iterator it = Iterator(head,2,*this);
            return it;
		}
};

template<typename Type>
const int LinkedList<Type> :: Iterator :: FORWARD = 1;

template<typename Type>
const int LinkedList<Type> :: Iterator :: BACKWARD = 2;

template<typename Type>
LinkedList<Type> :: LinkedList()
{
	head = NULL;
	end = NULL;
	size = 0;
}

template<typename Type>
LinkedList<Type> :: LinkedList(int listSize,Type inputValue)
{
	head = NULL;
	end = NULL;
	size = 0;
	int counter;
	for(counter=0;counter<listSize;counter++)
	{
		push_back(inputValue);
	}
}

template<typename Type>
LinkedList<Type> :: LinkedList(Iterator first,Iterator last)
{
	head = NULL;
	end = NULL;
	size = 0;
	LinkedList<Type> :: Iterator it;
	for(it=first;it!=last;++it)
	{
		push_back((*it)->getData());
	}
}

//template<typename Type>
//LinkedList<Type> :: LinkedList(LinkedList<Type>& lst)
//{
//    head = NULL;
//	end = NULL;
//	size = 0;
//    LinkedList<Type>::Iterator it;
//    for(it = lst.Begin();it != lst.End();++it)
//    {
//		push_back((*it)->getData());
//    }
//}

template<typename Type>
void LinkedList<Type> :: push_back(Type data)
{
//	Node<Type>* newNode = (Node<Type>*)malloc(sizeof(Node<Type>));

	Node<Type>* newNode = new Node<Type>();
	if(!newNode)
	{
		cout<<"\n\tMemory Full!";
		return;
	}

	if(this->head == NULL)
	{
		newNode->setData(data,NULL,NULL);
		head = end = newNode;
		size++;
		return;
	}

	newNode->setData(data,NULL,end);
	end->setNextAddress(newNode);
	end = newNode;
	size++;
}

template<typename Type>
void LinkedList<Type> :: pop_back()
{
	Node<Type>* temp;

	if(head == NULL)
		cout<<"\n\tList is Empty!";

	if(this->head == this->end)	//When there is only single node in Linked List
	{
		temp = head;
		head = end = NULL;
		free(temp);
		size--;
		return;
	}

	end->getPreviousNodeAddress()->setNextAddress(NULL);
	temp = end;
	end = end->getPreviousNodeAddress();
	free(temp);
	size--;
}

template<typename Type>
void LinkedList<Type> :: push_front(Type data)
{
//	Node<Type>* newNode = (Node<Type>*)malloc(sizeof(Node<Type>));

    Node<Type>* newNode = new Node<Type>();
	if(head == NULL)	//If there is no element in the Linked List
	{
		newNode->setData(data,NULL,NULL);
		head = end = newNode;
		size++;
		return;
	}

	newNode->setData(data,head,NULL);
	head->setPreviousAddress(newNode);
	head = newNode;
	size++;
}

template<typename Type>
void LinkedList<Type> :: pop_front()
{
	Node<Type>* temp;

	if(head == NULL)
		cout<<"\n\tList is Empty!";

	if(head == end) 	//if there is only one node in the Linked List
	{
		temp = head;
		head = end = NULL;
		free(temp);
		size--;
		return;
	}

	temp = head;
	head->getNextNodeAddress()->setPreviousAddress(NULL);
	head = head->getNextNodeAddress();
	free(temp);
	size--;
}

template<typename Type>
void LinkedList<Type> :: insert(Type data,int position)
{
	int counter = 0;
	Node<Type>* temp;

	if(position == 0)
	{
		push_front(data);
		return;
	}

	if(position == size)
	{
		push_back(data);
		return;
	}

	temp = head;
	while(counter != position-1)	//position-1 so that i can have pointer to previous node of insert position
	{
		temp = temp->getNextNodeAddress();
		counter++;
	}

	Node<Type>* newNode = new Node<Type>();
	newNode->setData(data,temp->getNextNodeAddress(),temp);
	temp->getNextNodeAddress()->setPreviousAddress(newNode);
	temp->setNextAddress(newNode);
	size++;
}

template<typename Type>
void LinkedList<Type> :: reverse()
{
	reverseList(head);
}

template<typename Type>
void LinkedList<Type> :: reverseList(Node<Type>* currentNode)		//using recursion
{
	static int counter = -1;
	int tempCounter;
	counter++;
	tempCounter = counter;
	if(currentNode->getNextNodeAddress() == NULL)		//Base Condition
	{
		//This means it is the last node in the list, so make it as the head of the list
		//Swap Next and Previous Address Values of the Node
		Node<Type>* temp;
		temp = currentNode->getNextNodeAddress();
		currentNode->setNextAddress(currentNode->getPreviousNodeAddress());
		currentNode->setPreviousAddress(temp);
		head = currentNode;
		return;
	}

	reverseList(currentNode->getNextNodeAddress());

	Node<Type>* temp;
	temp = currentNode->getNextNodeAddress();
	currentNode->setNextAddress(currentNode->getPreviousNodeAddress());
	currentNode->setPreviousAddress(temp);
	if(tempCounter == 0)
		end = currentNode;
}

template<typename Type>
void LinkedList<Type> :: remove(Type data)
{
	Node<Type>* temp;

	if(head == NULL)	//Check if the list is empty or not
	{
		cout<<"\n\tList is Empty!";
		return;
	}

	temp = head;
	while(temp != NULL)
	{
		if(temp->getData() == data)
		{
			if(temp == head)
			{
				pop_front();
				return;
			}
			else if(temp == end)
			{
				pop_back();
				return;
			}
			else
			{
				temp->getPreviousNodeAddress()->setNextAddress(temp->getNextNodeAddress());
				temp->getNextNodeAddress()->setPreviousAddress(temp->getPreviousNodeAddress());
				free(temp);
				size--;
				return;
			}

		}
		temp = temp->getNextNodeAddress();
	}
	cout<<"\n\tNode Not Found!";
}

template<typename Type>
int LinkedList<Type> :: getSize()
{
	return size;
}

template<typename Type>
void LinkedList<Type> :: clear()
{
	Node<Type>* temp,*clearNode;

	if(head == NULL)
		cout<<"\n\tList is already Empty!";

	temp = head;
	while(temp != NULL)
	{
		clearNode = temp;
		temp = temp->getNextNodeAddress();
		free(clearNode);
	}
	size = 0;
	head = end = NULL;
}

template<typename Type>
bool LinkedList<Type> :: empty()
{
	if(size == 0)
		return true;
	return false;
}

template<typename Type>
Type LinkedList<Type> :: getElementAtPosition(Iterator position)
{
	Node<Type>* temp;

	if(head == NULL)
	{
		cout<<"\n\tList is Empty!";
		//return;
	}
	else
	{
//		int counter;
//		temp = head;
//		for(counter = 0;counter < position.getCurrentPosition();counter++)
//		{
//			temp = temp->getNextNodeAddress();
//		}
		temp = head;
		while(temp != *position)
			temp = temp->getNextNodeAddress();
		return (temp->getData());
	}
}

template<typename Type>
void LinkedList<Type> :: remove(Iterator position)
{
	Node<Type>* temp;
	Node<Type>* previous = NULL;

	if(head == NULL)
	{
		cout<<"\n\tList is Empty!";
		return;
	}

	if(*position == head)
	{
		pop_front();
		return;
	}

	if(*position == end)
	{
		pop_back();
		return;
	}

//	int counter = 0;
	temp = head;
//	while(counter < position.getCurrentPosition())
//	{
//		previous = temp;
//		temp = temp->getNextNodeAddress();
//		counter++;
//	}
	while(temp != *position)
	{
		previous = temp;
		temp = temp->getNextNodeAddress();
	}

	previous->setNextAddress(temp->getNextNodeAddress());
	temp->getNextNodeAddress()->setPreviousAddress(previous);
	free(temp);
}

template<typename Type>
void LinkedList<Type> :: splice(Iterator position,LinkedList<Type>& lst)
{
	int pos = position.getCurrentPosition();
	LinkedList<Type> :: Iterator it;
	for(it = lst.Begin();it != lst.End();++it)
	{
		insert((*it)->getData(),pos);
		pos++;
	}
	lst.clear();	//Clearing the Source List
}

template<typename Type>
void LinkedList<Type> :: splice(Iterator position,LinkedList<Type>& lst,Iterator element)
{
	int pos = position.getCurrentPosition();
	//cout<<"\n\tCurrent Position(Destination List): "<<pos<<endl;
	if(pos < 0 || pos >= size)
	{
		cout<<"\n\tDestination Iterator Out Of Bound!";
		return;
	}

	if(element.getCurrentPosition() < 0 || element.getCurrentPosition() >= lst.getSize())
	{
		cout<<"\n\tSource Iterator Out Of Bound!";
		return;
	}
	insert(lst.getElementAtPosition(element),pos);	//inserted the data at required position in the destination list
	//cout<<"\n\tData Inserted!";
	lst.remove(element);	//removing the element from the source list
}

template<typename Type>
void LinkedList<Type> :: splice(Iterator position,LinkedList<Type>& lst,Iterator first,Iterator last)
{
	int pos = position.getCurrentPosition();
	LinkedList<Type> :: Iterator it;

	//Inserting Elements in the destination List
	for(it = first; it != last;++it)
	{
		insert((*it)->getData(),pos);
		pos++;
	}

	//Deleting Elements from the Source List
	LinkedList<Type>:: Iterator tempIT;
	for(it = first;it!=last;)
	{
		tempIT = it;
		++tempIT;
		lst.remove(it);
		it = tempIT;
	}
}

template<typename Type>
void LinkedList<Type> :: sort( bool (*compare)(Type,Type) )
{
	LinkedList<Type> :: Iterator out,in,position;
	Type temp,compareValue;

	//Selection Sort
	for(out = this->Begin(); out != (*this->End())->getPreviousNodeAddress(); ++out)
	{
		//cout<<"\n\tOut";
		compareValue = (*out)->getData();
		position = out;

		for(in = Iterator((*out)->getNextNodeAddress()); in != End(); ++in )
		{
			if(compare((*in)->getData(),compareValue))
			{
				position = in;
				compareValue = (*in)->getData();
			}
		}
		temp = (*out)->getData();
		(*out)->setData(compareValue);
		(*position)->setData(temp);
	}
	//cout<<"\n\tSorted All Elements";
}



class Name
{
    private:
        string name;
        int worth;
    public:
        Name(){}
        Name(string name,int worth)
        {
            this->name = name;
            this->worth = worth;
        }
        string getName()
        {
            return name;
        }

        int getWorth()
        {
            return worth;
        }

};

bool compare(int a,int b)
{
	return (a < b);
}

bool compare(Name a,Name b)
{
    return(a.getWorth() < b.getWorth());
}

bool compare(float a,float b)
{
    return (a > b);
}

bool compare(string a,string b)
{
    return(a < b);
}

int main()
{
    LinkedList<int> intList = LinkedList<int>();
    LinkedList<float> floatList = LinkedList<float>();
    LinkedList<Name> nameList = LinkedList<Name>();
    LinkedList<string> stringList = LinkedList<string>();
    LinkedList<int> newIntList = LinkedList<int>(6,200);

    intList.push_back(30);
    intList.push_back(10);
    intList.push_back(80);
    intList.push_back(40);
    intList.push_back(100);
    intList.pop_back();

    //intList.reverse();
    intList.sort(compare);
    cout<<"\n\tPrinting List using Forward Iterator: ";
    LinkedList<int> :: Iterator intit;
    for(intit = intList.Begin();intit != intList.End();++intit)
    {
        cout<<(*intit)->getData() <<" ";
    }

    cout<<"\n\tPrinting List using Backward Iterator:";
    for(intit = intList.crBegin();intit != intList.crEnd();++intit)
    {
        cout<<(*intit)->getData() <<" ";
    }


    floatList.push_back(5.6);
    floatList.push_back(34.5);
    floatList.push_back(3.5);
    floatList.push_back(1.9);
    floatList.sort(compare);
    cout<<"\n\t";
    LinkedList<float>:: Iterator floatit;
    for(floatit = floatList.Begin();floatit != floatList.End();++floatit)
    {
        cout<<(*floatit)->getData()<<" ";
    }

    nameList.push_back(Name("Jitesh",1000));
    nameList.push_back(Name("Mohit",200));
    nameList.push_back(Name("Himesh",150));
    nameList.push_back(Name("Gulshan",500));
    nameList.sort(compare);

//    cout<<"\n\t";
    LinkedList<Name> :: Iterator nameit;
    for(nameit = nameList.Begin();nameit != nameList.End();++nameit)
    {
        cout<<"\n\tName: "<<(*nameit)->getData().getName() <<" | Worth: "<<(*nameit)->getData().getWorth()<<endl;
    }

    stringList.push_back("Jitesh");
    stringList.push_back("Himesh");
    stringList.push_back("Gulshan");
    stringList.push_back("Aman");
    stringList.push_back("Prince");
    stringList.push_back("Abhinav");
    stringList.sort(compare);

    cout<<"\n\t";
    LinkedList<string> :: Iterator strit;
    for(strit = stringList.Begin();strit != stringList.End();++strit)
    {
        cout<<(*strit)->getData()<<" ";
    }

    cout<<"\n\t";
    for(intit = newIntList.Begin();intit != newIntList.End();++intit)
        cout<<(*intit)->getData()<<" ";

    intit = intList.Begin();
    ++intit;
    ++intit;

    LinkedList<int> copyIntList = LinkedList<int>(intit,intList.End());
    intit = copyIntList.Begin();
    ++intit;
    copyIntList.splice(intit,intList);
    cout<<"\n\t";
    for(intit = copyIntList.Begin();intit != copyIntList.End();++intit)
        cout<<(*intit)->getData()<<" ";
	return 0;
}
