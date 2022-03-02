/**
 * @file component.h
 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief 
 * @version 0.1
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
#include "interface.h"


class File : public Component
{
    using type_shaps = std::unique_ptr<Component>;

    std::size_t _id = id;
    std::string _file;
    std::list<type_shaps> _shaps;
   
public:
    
    File(const std::string& file) : _file(file) {}

    std::size_t getId() const override
    {
        return _id;
    }

    std::string getName() const
    {
        return _file;
    }

    std::size_t getCountShaps() const
    {
        return _shaps.size();
    }

    void createShape(type_shaps cord)
    {
        _shaps.push_back(std::move(cord));
    }

    bool deleteShape(std::size_t shape_id)
    {   
        auto it = std::find_if(_shaps.cbegin(), _shaps.cend(), [&shape_id](const type_shaps& shap){
            return shap->getId() == shape_id;
        });
        if(it != _shaps.cend())
        {
            _shaps.erase(it);
            return true;
        }
        else return false;
    }

    void SetObjectFile(File& file)
    {
        _file = file._file;
        _id = file._id;
        _shaps.clear();
        _shaps = std::move(file._shaps);
    }

    void accept(IVisitor * vis) override
    {
        vis->visit(this);        
    }
    
    void save(IVisitor* save)
    {
        accept(save);
        for(const auto& s : _shaps)
        {
            s->accept(save);      
        }
    }

    void draw() override
    {
        ///@todo Место отрисовки документа
        std::cout << "Draw file " << _file << std::endl;
   
        for(const auto& s : _shaps)
        {
            s->draw();      
        }      
    }
};


class Dot : public Component
{
   coordinates _cord;
   std::size_t _id = id;
    
public:
    
    Dot(const coordinates& cord) : _cord(cord) {}
    Dot(std::size_t x, std::size_t y) : _cord(x, y) {}
    
    std::size_t getId() const override
    {
        return _id;
    }

    void accept(IVisitor * vis) override
    {
        vis->visit(this);
    }

    void draw() override
    {
       std::cout << "Draw Dot id "<<_id<<": (.) x" << _cord._x <<" y:"<< _cord._y << std::endl;
    }

};

class Line : public Component
{
private:
   Dot _one;
   Dot _two;
   std::size_t _id = id;
public:

    Line(const Dot& one, const Dot& two) : _one(one), _two(two) {}

    std::size_t getId() const override
    {
        return _id;
    }

    void accept(IVisitor * vis) override
    {
        vis->visit(this);
    }

    void draw() override
    {
       std::cout << "Draw Line "<<_id<<": ------------" << std::endl;
         _one.draw();
         _two.draw();
    }

};