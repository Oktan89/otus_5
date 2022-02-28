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
protected:
   
    ///@brief Контейнер с подписчиками на событие update()
    std::list<IView*> _subs; 

    ///@brief Объект File с графическими примитивами
    std::unique_ptr<File> component; 

public:
    /**
     * @brief Получить объект с именем файла
     * 
     * @return std::string 
     */
    std::string getFileName() const
    {
        return component->getName();
    }

    /**
     * @brief Получить количество фигур объекта
     * 
     * @return std::size_t 
     */
    std::size_t getCountShapes() const
    {
        return component->getCountShaps();
    }

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

class ExportSerializer : public IVisitor
{
public:

    void visit(Dot* dot) override
    {
        std::cout << "Serializer Dot_"<< dot->getId() << std::endl;
    }

    void visit(Line* line) override
    {
        std::cout << "Serializer Line_" << line->getId() << std::endl;
    }

    void visit(File* file) override
    {
        std::cout << "Serializer File_" << file->getName() << std::endl;
    }
private:
    ///@todo методы сериализации
};

class Editor : public __BaseModel
{
IVisitor * expo = new ExportSerializer;//std::unique_ptr
public:

    void draw() const override
    {
        component->draw();
    }

    void createDoc(const std::string& file) override
    {
        std::cout << "Model: create document " << file << std::endl;
        component = std::make_unique<File>(file);
        notification();
    }
    
    void importDoc(const File& file) override
    {
        std::cout << "Model: import document" << std::endl;
        component->SetObjectFile(file);
        notification();
    }
    
    void exportDoc() override
    {
        std::cout << "Model: Export document" << std::endl;
        component->save(expo);
    }

    void createShape(std::shared_ptr<Component> shape) override
    {
        std::cout << "Shape: create" << std::endl;
        if(component)
        {
            component->createShape(shape);
            notification();
        }
        else throw std::runtime_error("Create shape error: the file does not exist");
    }
    
    void deleteShape(std::shared_ptr<Component> shape) override
    {
        std::cout << "Shape: delete" << std::endl;
        if(component)
        {
            component->deleteShape(shape);
            notification();
        }
        else throw std::runtime_error("Delete shape error: the file does not exist");
    }

};

