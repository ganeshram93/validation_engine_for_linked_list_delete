#include <iostream>
#include <math.h>
using namespace std;

class node
{
	public:
		int data, size;
		node *next;
		void add(int);
		void display(node *);
		node* createCopy(int);
		int validationEngine();
		node* deleteNode();
};

node *head, *head2;
int del_index, tc_pass_num, expected_del_index; 

int node::validationEngine()
{
	int i = 0;
	bool is_elem_deleted = false, check_all_elem = true, is_num_valid = false;
	node *temp, *temp2;

	tc_pass_num = 0;
	temp = head;
	while(temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	if(i == (size - 1)) //Validation 0: Total size of original array must be (s2.size - 1) after deletion
	{
		 cout<<"\n\n----Validation 0: Check number of elements----";
		 cout<<"\nExpected number of elements before deletion = "<<(size - 1);
		 cout<<"\nObtained number of elements after deletion = "<<i;
		 cout<<"\nResult: PASSED\n";
		 tc_pass_num++;
	}
	else
	{
		 cout<<"\n\n----Validation 0: Check number of elements----\nResult: FAILED\n";
		 return (tc_pass_num = 0);
	}

	temp = head;
	temp2 = head2;
	for(i = 0; i < size; i++)
	{
		if(is_elem_deleted == false && (temp->data != temp2->data)) //Validation 1: Check absence of deleted element in original set s1
		{
			is_elem_deleted = true;

			if(temp2->next != NULL)
				temp2 = temp2->next;

			if(i == (size - 1)) //End of elements in s1, no more to check. So last element should be the deleted element
			{
				cout<<"\n----Validation 1: Check Deleted element----";
				cout<<"\nExpected deleted index = "<<(size - 1 - del_index);
				cout<<"\nObtained deleted index = "<<i;
				cout<<"\nResult: PASSED\n";
				cout<<"\n----Validation 2: Check Data integity----";
				cout<<"\nExpected output: Values of original data set s1 must not be altered apart from deleted element.";
				cout<<"\nResult: PASSED\n";
				return 1;
			}
		}

		if(temp->data != temp2->data) //Validation 2: Check if any other element mismatches
		{
			cout<<"\nValue mismatch at detected at index "<<i;
			check_all_elem = false;
			cout<<"\nResult: FAILED";
			return 0; //Validation result immediately marked as: Fail
		}

		if(temp->next != NULL) //Check needed to stop traversal of original set s1 in case of deleting of last element
			temp = temp->next;
		if(temp2->next != NULL)
			temp2 = temp2->next;
	}

	cout<<"\n----Validation 1: Check Deleted element----";
	if(is_elem_deleted == true)
	{
		cout<<"\nGiven deleted index = "<<(del_index); //Since 'i' would have incremented extra, after the for loop 
		cout<<"\nExpected deleted index = "<<expected_del_index;
		cout<<"\nResult: PASSED\n";
	}
	else
		cout<<"\nResult: FAILED\n\n";

	cout<<"\n----Validation 2: Check Data integity----";
	if(check_all_elem == true)
	{
		cout<<"\nExpected output: Values of original data set s1 must not be altered apart from deleted element.";
		cout<<"\nResult: PASSED\n";
	}
	else
		cout<<"\nResult: FAILED\n\n";

	if(is_elem_deleted == true && check_all_elem == true)
		return 1;
	else
		return 0;
}

node* node::createCopy(int val)
{

	node *temp = new node;
	if(head2 == NULL)
	{
		temp->data = val;
		temp->next = NULL;
		head2 = temp;
	}
	else
	{
		node *ptr;
		ptr = head2;
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		temp->data = val;
		temp->next = NULL;
		ptr->next = temp;
	}

	return head2;
}

node* node::deleteNode()
{
	node* bef_node= NULL, *curr = NULL, *aft_node= NULL;
	int curr_pos = 0;
	curr = head;

	if(del_index == (size - 1))
	{
		curr = head;
		cout<<". So actual element to be deleted = "<<curr->data<<" at index = "<<(size - del_index - 1)<<endl;
		expected_del_index = (size - 1);
		head = head->next;
		free(curr);
		size--;
		cout<<"New elements are:\n";
		display(head);
		return head;
	}

	while(curr_pos < ((size - 1) - del_index)) 
	{
		curr_pos++;
		bef_node = curr;
		curr = curr->next;
	}

	expected_del_index = curr_pos;
	cout<<"\nActual element to be deleted = "<<curr->data<<" at index = "<<curr_pos<<endl;
	
	//Deleting node pointed by curr
	bef_node->next = curr->next;
	free(curr);
	size--;
	cout<<"New elements are:\n";
	display(head);
	return head;
}

void node::add(int val)
{
	node *temp = new node;
	if(head == NULL)
	{
		temp->data = val;
		temp->next = NULL;
		head = temp;
	}
	else
	{
		node *ptr;
		ptr = head;
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		temp->data = val;
		temp->next = NULL;
		ptr->next = temp;
	}
}

void node::display(node *x)
{
	node *temp;
	int idx = 0;
	temp = x;
	while(temp != NULL)
	{
		cout<<endl<<"Data = ["<<temp->data<<"] -- index = "<<idx++;
		temp = temp->next;
	}
}

int main()
{
	int i = 0, sample[10] = {0}, pass_count = 0, ch = 0;
	node s1, s2;
	for(i = 0; i < 10; i++)
	{
		sample[i] = ((rand() % 50) + 10); //restricting generated number from 10 to 60
		s1.add(sample[i]);
		s2.createCopy(sample[i]);
	}
	s1.size = i;
	s2.size = i;
	cout<<"\nOriginal Data Set generated:";
	s1.display(head);

	cout<<"\n\n----- Validation engine begins -----\n\n"; 
	cout<<"1. Deleting node at index = 0 by giving del_index = "<<(s2.size - 1)<<"\n2. Deleting node at any other given index\n3. Deleting node at last index = "<<(s2.size - 1)<<" by giving del_index = 0"<<endl;
	cout<<"\nEnter which test case to be executed: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
		{
			del_index = (s2.size - 1);
			cout<<"\n1. Deleting node at index = 0 by giving del_index = "<<del_index;
			head = s1.deleteNode();
			pass_count = s2.validationEngine();
			if(pass_count)
				cout<<"\nOverall result: Deleted node successfully at index = "<<(s2.size - 1 - del_index)<<" by giving del_index = "<<del_index<<endl;
			else
				cout<<"\nFailed.....\n";
			break;
		}
		case 2:
		{
			cout<<"\nEnter a random index number to be deleted apart from 0 or 10: ";
			cin>>del_index;
			if(del_index <= 0 || del_index >= 10)
			{
				cout<<"\nInvalid index provided";
				return 0;
			}
			cout<<"\n2. Deleting node at any other given del_index = "<<del_index;
			head = s1.deleteNode();
			pass_count = s2.validationEngine();
			if(pass_count)
				cout<<"\nOverall result: Deleted node successfully at index = "<<(s2.size - 1 - del_index)<<" by giving del_index = "<<del_index<<endl;
			else
				cout<<"\nFailed.....\n";
			break;
		}
		case 3:
		{
			del_index = 0;
			cout<<"\n3. Deleting node at last index = "<<(s2.size - 1)<<" by giving first index 0 as input"<<endl;
			head = s1.deleteNode();
			pass_count = s2.validationEngine();
			if(pass_count)
				cout<<"\nOverall result: Deleted node successfully at index = "<<(s2.size - 1 - del_index)<<" by giving del_index = "<<del_index<<endl;
			else
				cout<<"\nFailed.....\n";
			break;
		}
		default:
		{
			cout<<"\nInvalid user choice given.";
			return 0;
		}
	}
	return 0;
} 
