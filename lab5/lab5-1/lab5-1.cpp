// lab5-1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Body.h"
#include "Sphere.h"
#include "Cone.h"
#include "Parallelepiped.h"
#include "Cylinder.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

shared_ptr<CBody> CreateBodyFromStream(const string& bodyName, istream& stream);
shared_ptr<CParallelepiped> CreateParallelepiped(istream& stream);
shared_ptr<CCone> CreateCone(istream& stream);
shared_ptr<CCylinder> CreateCylinder(istream& stream);
shared_ptr<CSphere> CreateSphere(istream& stream);
double ReadDoubleValue(istream& stream);
bool CompareWeightInWater(const CBody & b1, const CBody & b2);
double CalculateWeightInWater(const CBody & body);

const double WATER_DENSITY = 1000;
const double ACCELERATION_OF_GRAVITY = 10;

int main(int argc, char* argv[])
{
    cout << "Enter 'Exit' for exit" << endl;
    string newString;
    cin >> newString;
    vector<shared_ptr<CBody>> threeDimensionalBody;
    while (newString != "Exit")
    {
        try
        {
            threeDimensionalBody.push_back(CreateBodyFromStream(newString, cin));
            cout << "Body added" << endl;
        }
        catch(std::exception const& e)
        {
            cout << e.what() << endl;
        }        
        cin >> newString;
    }

    if (threeDimensionalBody.size() == 0)
    {
        cout << "There are no bodies" << endl;
        return 0;
    }

    cout << "Body with max weight:" << endl;
    auto body = max_element(threeDimensionalBody.begin(), threeDimensionalBody.end(), 
                            [](const shared_ptr<CBody>& b1, const shared_ptr<CBody>& b2) {
                                 return b1->GetWeight() < b2->GetWeight();
                             });

    cout << (*body)->ToString() << endl;

    cout << "Body wich has min weight in water:" << endl;
    body = min_element(threeDimensionalBody.begin(), threeDimensionalBody.end(), 
                            [](const shared_ptr<CBody>& b1, const shared_ptr<CBody>& b2) {
                                 return CompareWeightInWater(*b1, *b2);
                             });
    cout << (*body)->ToString() << endl;

	return 0;
}

bool CompareWeightInWater(const CBody & b1, const CBody & b2)
{
    return CalculateWeightInWater(b1) < CalculateWeightInWater(b2);
}

double CalculateWeightInWater(const CBody & body)
{
    return (body.GetDensity() - WATER_DENSITY) * ACCELERATION_OF_GRAVITY * body.GetVolume();
}

shared_ptr<CBody> CreateBodyFromStream(const string& bodyName, istream& stream)
{    
    if (bodyName == "Parallelepiped")
    {
        return CreateParallelepiped(stream);
    }
    else if (bodyName == "Cone")
    {
        return CreateCone(stream);
    }
    else if (bodyName == "Cylinder")
    {
        return CreateCylinder(stream);
    }
    else if (bodyName == "Sphere")
    {
        return CreateSphere(stream);
    }
    else
    {
        throw runtime_error("Cant identify body " + bodyName + " ");
    }
}

shared_ptr<CParallelepiped> CreateParallelepiped(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double width   = ReadDoubleValue(stream);
    double height  = ReadDoubleValue(stream);
    double depth   = ReadDoubleValue(stream);
    return make_shared<CParallelepiped>(CParallelepiped(density, width, height, depth));
}

shared_ptr<CCone> CreateCone(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double radius  = ReadDoubleValue(stream);
    double height  = ReadDoubleValue(stream);
    return make_shared<CCone>(CCone(density, radius, height));
}

shared_ptr<CCylinder> CreateCylinder(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double radius  = ReadDoubleValue(stream);
    double height  = ReadDoubleValue(stream);
    return make_shared<CCylinder>(CCylinder(density, radius, height));
}

shared_ptr<CSphere> CreateSphere(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double radius  = ReadDoubleValue(stream);
    return make_shared<CSphere>(CSphere(density, radius));
}


double ReadDoubleValue(istream& stream)
{
    string str;
    stream >> str;
    try
    {        
        double value = stod(str);
        if (value <= 0)
        {
            throw domain_error(str + " must be greater than 0");
        }
        return value;
    }
    catch (invalid_argument const&)
    {
        throw domain_error("Value " + str + " must be a number");
    }
}