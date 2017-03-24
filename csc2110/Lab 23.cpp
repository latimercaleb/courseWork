// Lab 23 for CSC 2111 by Caleb Latimer 
#include<iostream>
using namespace std;
struct node
{
	int data;
	node * link;
};
void printReverse(struct node*head)
{
	node *next;
	if (head == NULL) 
		return;
	printReverse(head->link);
	cout << head->data << " ";
	//printf("%d ", head->data);
}
void printList(node*head)
{
	node *current = head;
	while (current!= NULL)
	{
		cout << current->data << " ";
		current = current->link;
	}
	cout << endl;
}
node *addNode(node *head, int newVal)
{
	node * current;
	current = new node;
	current->data = newVal;
	current->link = NULL;
	head->link = current;
	return current;
}
int main()
{
	node * head;
	head = new node;
	head->data = 0;
	head->link = NULL;
	node * next;
	next = addNode(head,10);
	node *mid;
	mid = addNode(next, 8);
	node *last = addNode(mid, 4);
	cout << "Our list has : ";
	printList(head);
	cout << "The reverse has : ";
	printReverse(head);
	return 0;
}