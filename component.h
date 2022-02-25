#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
#include "interface.h"


class File : public Component
{
    using type_shaps = std::shared_ptr<Component>;
    std::string _file;
    std::list<type_shaps> _shaps;
public:
    
    File(const std::string& file) : _file(file) {}

    void createShape(type_shaps cord) override
    {
        _shaps.push_back(cord);
    }

    void deleteShape(type_shaps shape)
    {
        auto it = std::find(_shaps.cbegin(), _shaps.cend(), shape);
        _shaps.erase(it);
    }

    void draw() override
    {
        std::cout << "Draw file " << _file << std::endl;
        for(auto& s: _shaps)
            s->draw();
    }
};

class Dot : public Component
{
   coordinates _cord;
    
public:

    Dot(const coordinates& cord) : _cord(cord) {}

    void draw() override
    {
       std::cout << "Draw Dot: (.) x" << _cord._x <<" y:"<< _cord._y << std::endl;
    }

};

class Line : public Component
{
   Dot _one;
   Dot _two;
    
public:

    Line(const Dot& one, const Dot& two) : _one(one), _two(two) {}

    void draw() override
    {
       std::cout << "Draw Line: ------------" << std::endl;
         _one.draw();
         _two.draw();
    }

};