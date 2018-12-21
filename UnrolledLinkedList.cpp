#include"UnrolledLinkedList.h"
void UnrolledLinkedList::add(int val) {
	// TODO
	if (head == NULL)
	{
		Node * new_node = new Node(nodeSize);
		new_node->add(val);
		head = new_node;
		tail = new_node;
		size = 1;
		numOfNodes = 1;
	}
	else
	{
		Node * Temp = tail;
		//kiem tra node cuoi co full ko
		if (!Temp->isFull())
		{
			Temp->add(val);
			size = size + 1;
		}
		else
		{
			Node * new_node = new Node(nodeSize);
			// looi
			for (int i = Temp->getHalfNodeSize(); i < Temp->numElements; i++)
			{
				new_node->add(Temp->elements[i]);
			}
			new_node->add(val);
			//xoa du lieu trong node Temp
			int x = Temp->getHalfNodeSize();
			while (Temp->numElements != x)
			{
				Temp->removeAt(Temp->numElements-1);
			}
			/////////////////////////////////////////sua
			new_node->next = Temp->next;
			Temp->next = new_node;
			new_node->prev = Temp;
			tail = new_node;
			size = size + 1;
			numOfNodes = numOfNodes + 1;
		}
	}
}
//xong
int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node * Temp;	
	Temp = head;
	while (Temp != NULL)
	{
		if (pos < Temp->numElements)
			break;
		else
		{
			pos = pos - Temp->numElements;
		}
		Temp = Temp->next;
	}
	return Temp->elements[pos];	
}
//xong
void UnrolledLinkedList::setAt(int pos, int val){
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node * Temp;
	Temp = head;
	while (Temp != NULL)
	{
		if (pos < Temp->numElements)
		{
			break;
		}
		else
		{
			pos = pos - Temp->numElements;
		}
		Temp = Temp->next;
	}
	Temp->elements[pos] = val;
}
//xong
void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	// TODO
	Node * Temp=NULL;
	// head==NULL
	if (head == NULL)
	{
		Node * new_node = new Node(nodeSize);
		new_node->add(val);
		head = new_node;
		tail = new_node;
		size = size + 1;
		numOfNodes = numOfNodes + 1;
		return;
	}
	if (pos==size)
	{
		add(val);
		return;
	}
	//tinh pos
	Temp = head;
	while (Temp != NULL)
	{
		if (pos < Temp->numElements)
		{
			break;
		}
		else
		{
			pos = pos - Temp->numElements;
		}
		Temp = Temp->next;
	}
	//xong
	if (!Temp->isFull())
	{
		Temp->insertAt(pos,val);
		size++;
	}
	else
	{
		
		Node * new_node = new Node(nodeSize);
		numOfNodes++;
		//tachs
		int index = Temp->getHalfNodeSize();
		for (int i = index; i < Temp->numElements; i++)
		{
			new_node->add(Temp->elements[i]);
		}
		//xoa du lieu trong node Temp
		while (Temp->numElements-1 >=index)
		{
			Temp->removeAt(Temp->numElements-1);
		}
		/////////////////////////////////////////////////////////sua
		//insert new_node
		new_node->next = Temp->next;
		Temp->next = new_node;
		new_node->prev = Temp;
		if (new_node->next != NULL)
			new_node->next->prev = new_node;
		//update tail/////////////////////////////////////////
		if (new_node->next == NULL)
		{
			tail = new_node;
		}
		//insert val
		if (pos < Temp->numElements)
		{
			Temp->insertAt(pos, val);
			size++;
		}
		else
		{
			pos = pos - Temp->numElements;
			new_node->insertAt(pos, val);
			size++;
		}
		//kiem tra dk in halfull and fix
		if (Temp->isUnderHalfFull())
		{
			Temp->add(new_node->elements[0]);
			new_node->removeAt(0);
		}
		if (new_node->isUnderHalfFull())
		{
			new_node->insertAt(0, Temp->elements[Temp->numElements - 1]);
			Temp->removeAt(Temp->numElements - 1);
		}
	}
}
//xong
void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node * Temp;
	if (head == NULL) return;	
	//tinh pos
	Temp = head;
	while (Temp != NULL)
	{
		if (pos < Temp->numElements)
		{
			break;
		}
		else
		{
			pos = pos - Temp->numElements;
		}
		Temp = Temp->next;
	}
	//remove
	Temp->removeAt(pos);
	size = size - 1;
	if (Temp->isUnderHalfFull())
	{
		//check 
		//th chi co 1 node la head
		if (head->next==NULL)
		{
			return;
		}
		//th > 1 node
		else
		{
			//kiem tra trai/ phai
			// truong hop trai / phai khac NULL
			if (Temp->next != NULL && Temp->prev != NULL)
			{
				//kiem tra pre/next num==half
				if (Temp->prev->numElements == Temp->prev->getHalfNodeSize())
				{
					//merger 
					for (int i = 0; i < Temp->numElements; i++)
					{
						Temp->prev->add(Temp->elements[i]);
					}
					//delete node Temp
					if (Temp->next != NULL)
						Temp->next->prev = Temp->prev;
					if (Temp->prev != NULL)
						Temp->prev->next = Temp->next;
					delete Temp;
					numOfNodes--;
				}
				else
				{
					if (Temp->next->numElements == Temp->getHalfNodeSize())
					{
						//merger 
						for (int i = Temp->numElements-1; i >=0; i--)
						{
							Temp->next->insertAt(0,Temp->elements[i]);
						}
						//delete node Temp
						if (Temp->next != NULL)
							Temp->next->prev = Temp->prev;
						if (Temp->prev != NULL)
							Temp->prev->next = Temp->next;
						delete Temp;
						numOfNodes--;
					}
					else
					{
						//lay 1 phan tu tu node next
						Temp->add(Temp->next->elements[0]);
						Temp->next->removeAt(0);
					}
				}
			}
			else
			{
				//truong pre ==NULL
				if (Temp->prev == NULL)
				{
					//kiem tra next
					if (Temp->next->numElements == Temp->next->getHalfNodeSize())
					{
						//merger 
						for (int i = Temp->numElements-1; i >=0 ; i--)
						{
							Temp->next->insertAt(0,Temp->elements[i]);
						}
						//delete node Temp
						head = Temp->next;
						Temp->next->prev = NULL;
						delete Temp;
						numOfNodes--;
					}
					else
					{
						//lay 1 phan tu tu node next
						Temp->add(Temp->next->elements[0]);
						Temp->next->removeAt(0);
					}
				}
				else
				{
					//truong hop next=NULL
					if (Temp->next == NULL)
					{
						if (Temp->prev->numElements == Temp->getHalfNodeSize())
						{
							for (int i = 0; i < Temp->numElements; i++)
							{
								Temp->prev->add(Temp->elements[i]);
							}
							//delete node Temp
							if (Temp->next != NULL)
								Temp->next->prev = Temp->prev;
							if (Temp->prev != NULL)
								Temp->prev->next = Temp->next;
							tail = Temp->prev;
							delete Temp;
							numOfNodes--;

						}
						else
						{
							Temp->insertAt(0, Temp->prev->elements[Temp->prev->numElements - 1]);
							Temp->prev->removeAt(Temp->prev->numElements - 1);
						}
					}
				}
			}
		}
	}
}
//xong
int UnrolledLinkedList::firstIndexOf(int val) {
	// TODO
	Node * Temp = head;
	int pos = -1;
	while (Temp != NULL)
	{
		for (int i = 0; i < Temp->numElements; i++)
		{
			if (Temp->elements[i] == val)
			{
				return pos + i + 1;
			}
		}
		pos = pos + Temp->numElements;
		Temp = Temp->next;
	}
	return -1;
}
//xong
int UnrolledLinkedList::lastIndexOf(int val) {
	// TODO
	Node * Temp = tail;
	int pos = size;
	while (Temp!=NULL)
	{
		int x = Temp->numElements;
		for (int i = x-1; i>=0; i--)
		{
			if (Temp->elements[i] == val)
			{
				return pos - (x - i);
			}
		}
		pos = pos - x;
		Temp = Temp->prev;
	}
	return -1;
}
//xong
bool UnrolledLinkedList::contains(int val) {
	// TODO
	Node * Temp = head;
	while (Temp != NULL)
	{
		for (int i = 0; i < Temp->numElements; i++)
		{
			if (Temp->elements[i] == val)
			{
				return true;
			}
		}
		Temp = Temp->next;
	}
	return false;
}
//xong
void UnrolledLinkedList::reverse() {
	// TODO
	// reverse node 
	//reverse elements
	Node * Temp = head;
	tail = head;
	Node *pTemp = NULL;
	Node *pTemp1 = head;
	if (Temp == NULL)
	{
		return;
	}
	if (Temp->next == NULL && Temp->prev == NULL)
	{
		Temp->reverse();
		return;
	}
	while (pTemp1!=NULL)
	{
		pTemp = pTemp1->prev;
		pTemp1->prev = pTemp1->next;
		pTemp1->next = pTemp;
		pTemp1->reverse();
		pTemp1 = pTemp1->prev;
	}
	if (pTemp != NULL)
	{
		head = pTemp->prev;
	}
}
//xong
int* UnrolledLinkedList::toArray() {
	// TODO
	int * array = new int[size];
	Node * Temp = head;
	int pos = 0;
	while (Temp != NULL)
	{
		for (int i = 0; i < Temp->numElements; i++)
		{
			array[pos] = Temp->elements[i];
			pos = pos + 1;
		}
		Temp = Temp->next;
	}
	return array;
}
//xong