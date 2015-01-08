// lab4-2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Rectangle.h"

using namespace std;

bool PrepareRectangle(char* rectangleFilePath, CRectangle& rectangle);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect format - lab4-2.exe <rectangle_file1> <rectangle_file2>" << endl;
        return 1;
    }

    CRectangle rectangle1;
    CRectangle rectangle2;

    if (!PrepareRectangle(argv[1], rectangle1) || !PrepareRectangle(argv[2], rectangle2))
    {
        return 1;
    }

    rectangle1.Print("Rectangle 1:");
    rectangle2.Print("Rectangle 2:");
    rectangle1.Intersect(rectangle2);
    rectangle1.Print("Intersection rectangle:");

	return 0;
}

bool PrepareRectangle(char* rectangleFilePath, CRectangle& rectangle)
{
    ifstream rectangleFile(rectangleFilePath);
    if (!rectangleFile.is_open())
    {
        cout << "Cant open 'rectangle_file':" << rectangleFilePath << endl;
        return false;
    }

    string command;
    while (rectangleFile >> command)
    {
        if (command == "Rectangle")
        {
            int left;
            int top;
            int width;
            int height;
            rectangleFile >> left;
            rectangleFile >> top;
            rectangleFile >> width;
            rectangleFile >> height;
            rectangle = CRectangle(left, top, width, height); 
        }
        else if (command == "Move")
        {
            int dx;
            int dy;
            rectangleFile >> dx;
            rectangleFile >> dy;
            rectangle.Move(dx, dy); 
        }
        else if (command == "Scale")
        {
            int sx;
            int sy;
            rectangleFile >> sx;
            rectangleFile >> sy;
            rectangle.Scale(sx, sy); 
        }
        else
        {
            cout << "Undefined command!" << endl;
        }
    }

    return true;
}


