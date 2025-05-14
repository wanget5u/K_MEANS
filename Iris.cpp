//
// Created by s31230 on 2025-05-14.
//

#include "Iris.h"

Iris::Iris(std::vector<float> const& attributes, std::string const& className, int const& groupNumber)
{
    this -> attributes = attributes;
    this -> className = className;
    this -> groupNumber = groupNumber;
}

int const & Iris::getGroupNumber() const
{return this -> groupNumber;}

void Iris::setGroupNumber(int const& number)
{this -> groupNumber = number;}

std::string const & Iris::getClassName() const
{return this -> className;}

std::vector<float> const& Iris::getAttributes() const
{return this -> attributes;}

float const& Iris::getAttributeAt(int const& index) const
{return this -> attributes.at(index);}
