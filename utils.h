#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>

namespace utils
{
    template <typename T>
    void printVector(std::vector<T> const& vector)
    {
        std::cout << '{';
        for (int x = 0; x < vector.size(); x++)
        {
            if (x != vector.size() - 1)
            {std::cout << vector.at(x) << ", ";}
            else
            {std::cout << vector.at(x) << '}' << std::endl;}
        }
    }

    inline void printIris(Iris const& iris)
    {
        std::cout << iris.getClassName() << " | " << iris.getGroupNumber() << " | ";
        printVector(iris.getAttributes());
    }

    inline std::vector<std::string> split(std::string const& text, char const& separator)
    {
        std::vector<std::string> data;
        std::istringstream iss(text);
        std::string fragment;

        while (std::getline(iss, fragment, separator))
        {data.push_back(fragment);}

        return data;
    }

    inline std::pair<int, int> parseTwoInts(std::string const& line)
    {
        std::istringstream iss(line);
        int a, b;
        iss >> a >> b;
        return {a, b};
    }

    inline std::vector<float> parseStringVectorToFloatVector(std::vector<std::string> const& data)
    {
        std::vector<float> parsedData;

        for (std::string const& element : data)
        {parsedData.push_back(std::stof(element));}

        return parsedData;
    }

    inline float euclideanDistance(float const& x, float const& y)
    {return std::pow(x - y, 2);}
}