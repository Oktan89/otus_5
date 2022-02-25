/**
 * @file model.h
 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief Файл классов модели (MVC)
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <list>
#include <algorithm>
#include <string>
#include "interface.h"
#include "component.h"



/**
 * @brief Базовый класс для моделей работы векторного редактора
 * 
 */
class __BaseModel : public IModel
{
    std::list<IView*> _subs;
protected:
    std::unique_ptr<Component> component; 

public:
   
    void connect(IView* view) override
    {
        _subs.push_back(view);
    }

    void disconnect(IView* view) override
    {
        auto it = std::find(_subs.cbegin(), _subs.cend(), view);
        _subs.erase(it);
    }

protected:
    void notification() const override
    {
        for(const auto& s : _subs)
            s->update();
    }

     __BaseModel() = default;

    ~__BaseModel(){}
};

class Editor : public __BaseModel
{

public:

    void draw() override
    {
        component->draw();
    }

    void createDoc(const std::string& file) override
    {
        std::cout << "Model: create document " << file << std::endl;
        component = std::make_unique<File>(file);
        notification();
    }
    
    void importDoc() override
    {
        std::cout << "Model: import document" << std::endl;
        notification();
    }
    
    void exportDoc() override
    {
        std::cout << "Model: Export document" << std::endl;
        notification();        
    }

    void createShape(std::shared_ptr<Component> shape) override
    {
        std::cout << "Shape: create" << std::endl;
        if(component)
        {
            component->createShape(shape);
            notification();
        }
        else throw std::runtime_error("File not created");
    }
    
    void deleteShape(std::shared_ptr<Component> shape) override
    {
        std::cout << "Shape: delete" << std::endl;
        component->deleteShape(shape);
        notification();
    }

};
