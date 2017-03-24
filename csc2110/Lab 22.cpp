// Lab 22 written by Caleb Latimer
#include<iostream>
using namespace std;
struct node
{
	int data;
	node*link;
};
void compare(struct node*, struct node*);
int main() 
{
	node * head = NULL;
	node * current = NULL;
	for (int i = 1; i == 1; i++) 
	{
		node * current = new node;
		current->data = i;
		current->link = head;
		head = current;
	}
	cout << "First list : ";
	cout << head->data << " ";
	//while (head!=NULL) {
	//	cout << head->data << " ";
	//	//head = head->link;
	//}
	cout << endl;
	node * head2 = NULL;
	node * current2 = NULL;
	for (int j = 5; j == 5; j--)
	{
		node * current2 = new node;
		current2->data = j;
		current2->link = head2;
		head2 = current2;
	}
	cout << "Second list : ";
	cout << head2->data << " ";
	//while (head2 != NULL) {
	//	cout << head2->data << " ";
	//	//head2 = head2->link;
	//}
	cout << endl;
	compare(head, head2);
	return 0;
}

void compare(struct node* head1, struct node* head2)
{
	bool check =true;
	while ((head1->data != NULL) && (head2->data != NULL))
	{
		if (head1->data != head2->data)
		{
			check = false;
			break;
		}
		head1 = head1->link;
		head2 = head2->link;
	}
	
		if (check == false)
			cout << "The list is NOT EQUAL" << endl;
		else
			cout << "The list is EQUAL" << endl;
}