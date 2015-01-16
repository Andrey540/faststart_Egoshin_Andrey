// lab5-1.cpp: определяет точку входа для консольного приложения.
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

shared_ptr<CBody> GetBodyFromStream(const string& bodyName, istream& stream);
shared_ptr<CParallelepiped> GetParallelepiped(istream& stream);
shared_ptr<CCone> GetCone(istream& stream);
shared_ptr<CCylinder> GetCylinder(istream& stream);
shared_ptr<CSphere> GetSphere(istream& stream);
double ReadDoubleValue(istream& stream);
bool CompareWeightInWater(CBody & b1, CBody & b2);

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
            threeDimensionalBody.push_back(GetBodyFromStream(newString, cin));
            cout << "Body added" << endl;
        }
        catch(std::exception const& e)
        {
            cout << e.what() << endl;
        }        
        cin >> newString;
    }
    cout << "Body with max weight:" << endl;
    auto body = max_element(threeDimensionalBody.begin(), threeDimensionalBody.end(), 
                            [](const shared_ptr<CBody>& b1, const shared_ptr<CBody>& b2) {
                                 return b1->GetWeight() < b2->GetWeight();
                             });

    cout << (*body)->ToString() << endl;

    cout << "Body wich has min weight in water:" << endl;
    body = min_element(threeDimensionalBody.begin(), threeDimensionalBody.end(), 
                            [](shared_ptr<CBody> b1, shared_ptr<CBody> b2) {
                                 return CompareWeightInWater(*b1, *b2);
                             });
    cout << (*body)->ToString() << endl;

	return 0;
}

bool CompareWeightInWater(CBody & b1, CBody & b2)
{
    double weight1 = (b1.GetDensity() - WATER_DENSITY) * ACCELERATION_OF_GRAVITY * b1.GetVolume();
    double weight2 = (b2.GetDensity() - WATER_DENSITY) * ACCELERATION_OF_GRAVITY * b2.GetVolume();
    return weight1 < weight2;
}

shared_ptr<CBody> GetBodyFromStream(const string& bodyName, istream& stream)
{    
    if (bodyName == "Parallelepiped")
    {
        return GetParallelepiped(stream);
    }
    else if (bodyName == "Cone")
    {
        return GetCone(stream);
    }
    else if (bodyName == "Cylinder")
    {
        return GetCylinder(stream);
    }
    else if (bodyName == "Sphere")
    {
        return GetSphere(stream);
    }
    else
    {
        throw runtime_error("Cant identify body " + bodyName + " ");
    }
}

shared_ptr<CParallelepiped> GetParallelepiped(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double width   = ReadDoubleValue(stream);
    double height  = ReadDoubleValue(stream);
    double depth   = ReadDoubleValue(stream);
    return make_shared<CParallelepiped>(CParallelepiped(density, width, height, depth));
}

shared_ptr<CCone> GetCone(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double radius  = ReadDoubleValue(stream);
    double height  = ReadDoubleValue(stream);
    return make_shared<CCone>(CCone(density, radius, height));
}

shared_ptr<CCylinder> GetCylinder(istream& stream)
{
    double density = ReadDoubleValue(stream);
    double radius  = ReadDoubleValue(stream);
    double height  = ReadDoubleValue(stream);
    return make_shared<CCylinder>(CCylinder(density, radius, height));
}

shared_ptr<CSphere> GetSphere(istream& stream)
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