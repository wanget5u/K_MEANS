#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <ranges>

#include "Iris.h"
#include "utils.h"

std::vector<Iris> parseFile(std::string const& fileName, int const& k, int const& ATTRIBUTES_LENGTH)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {std::cerr << "can't open file: " << fileName << std::endl; std::exit(1);}

    std::string line;

    std::vector<Iris> irisList;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(1, k + 1);

    while (std::getline(file, line))
    {
        std::vector irisData(utils::split(line, ';'));

        std::vector irisAttributes(irisData.begin(), irisData.end() - 1);

        if (irisAttributes.size() == ATTRIBUTES_LENGTH)
        {
            irisList.emplace_back(
            utils::parseStringVectorToFloatVector(irisAttributes),
            irisData.at(irisData.size() - 1),
            distribution(generator));
        }
        else
        {std::cout << "skipping invalid data.." << std::endl;}
    }

    return irisList;
}

void compute(std::vector<Iris> & irisList, int const& k, int const& ATTRIBUTES_LENGTH)
{
    bool changed(true);

    while (changed)
    {
        changed = false;

        std::vector<std::vector<float>> centroids;

        for (int x = 1; x < k + 1; x++)
        {
            std::vector<Iris> group;

            for (Iris const& iris: irisList)
            {
                if (iris.getGroupNumber() == x)
                {group.emplace_back(iris);}
            }

            std::vector<float> centroid;

            for (int y = 0; y < ATTRIBUTES_LENGTH; y++)
            {
                float sum = 0;

                for (Iris const& iris : group)
                {sum += iris.getAttributeAt(y);}

                float average(sum / static_cast<float>(group.size()));

                centroid.emplace_back(average);
            }

            centroids.emplace_back(centroid);
        }

        for (Iris & iris : irisList)
        {
            int const currentGroup(iris.getGroupNumber());
            int closestGroup(-1);
            float minDistance = std::numeric_limits<float>::max();

            for (int x = 0; x < centroids.size(); x++)
            {
                std::vector const centroid(centroids.at(x));
                float distance(0.f);

                for (int y = 0; y < ATTRIBUTES_LENGTH; y++)
                {distance += utils::euclideanDistance(iris.getAttributeAt(y), centroid.at(y));}

                if (distance < minDistance)
                {
                    minDistance = distance;
                    closestGroup = x + 1;
                }
            }

            if (currentGroup != closestGroup)
            {
                iris.setGroupNumber(closestGroup);
                changed = true;
            }
        }

        for (int x = 0; x < centroids.size(); x++)
        {
            float distance(0.f);

            for (Iris const& iris : irisList)
            {
                for (int i = 0; i < ATTRIBUTES_LENGTH; i++)
                {
                    if (iris.getGroupNumber() == x + 1)
                    {distance += utils::euclideanDistance(centroids.at(x).at(i), iris.getAttributeAt(i));}
                }
            }
            std::cout << "Group: " << x + 1 << ", distance: " << distance << "; ";
        }
        std::cout << std::endl;
    }
}

auto main(int const argc, char const* argv[]) -> int
{
    if (argc != 4)
    {std::cerr << "usage: main.cpp <k> <fileName> <attributesLength>" << std::endl; std::exit(1);}

    int k;
    std::string fileName;
    int ATTRIBUTES_LENGTH;

    try
    {
        k = std::stoi(argv[1]);
        fileName = argv[2];
        ATTRIBUTES_LENGTH = std::stoi(argv[3]);
    }
    catch ([[maybe_unused]] std::exception const& exception)
    {std::cerr << "invalid arguments " << exception.what() << std::endl; std::exit(1);}

    std::vector irisList(parseFile(fileName, k, ATTRIBUTES_LENGTH));

    compute(irisList, k, ATTRIBUTES_LENGTH);

    // for (int i = 1; i < k + 1; i++)
    // {
    //     for (Iris const& iris : irisList)
    //     {
    //         if (iris.getGroupNumber() == i)
    //         {utils::printIris(iris);}
    //     }
    // }
}