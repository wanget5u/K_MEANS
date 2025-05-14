#pragma once
#include <string>
#include <vector>

struct Iris
{
    private:
    std::vector<float> attributes;
    std::string className;
    int groupNumber = 0;

    public:
    Iris(std::vector<float> const& attributes, std::string const& className, int const& groupNumber);

    [[nodiscard]] int const& getGroupNumber() const;

    void setGroupNumber(int const& number);

    [[nodiscard]] std::string const& getClassName() const;

    [[nodiscard]] std::vector<float> const& getAttributes() const;

    [[nodiscard]] float const& getAttributeAt(int const& index) const;
};
