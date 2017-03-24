#include "Figure.h"
void Figure::erase()
{
	cout << "This is the function of Figure::erase()";
}

void Figure::draw()
{
	cout << "This is the function of Figure::draw()";
}

void Figure::center()
{
	cout << "The member function center is called to erase and draw ";
	erase();
	draw();

}