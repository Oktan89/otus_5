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
    std::list<std::weak_ptr<IView>> _subs; 

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

    void connect(const std::shared_ptr<IView>& view) override
    {
        _subs.emplace_back(view);
    }

    void disconnect(const std::shared_ptr<IView>& view) override
    {
        auto it = std::find_if(_subs.cbegin(), _subs.cend(), [&](const std::weak_ptr<IView>& sub){
            auto itr = sub.lock();
            return itr == view;
        });
        if(it != _subs.end())
            _subs.erase(it);
    }

protected:
    void notification() override
    {
        for(auto itr = _subs.begin(); itr != _subs.end(); ++itr)
        {
            auto sub = itr->lock();
            if(sub)
            {
                sub->update();
            }
            else
            {
                _subs.erase(itr);
            }
        }
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
//IVisitor * expo = new ExportSerializer;//std::unique_ptr
std::unique_ptr<IVisitor> expo;

public:

    Editor(std::unique_ptr<IVisitor> _expo = std::make_unique<ExportSerializer>()) : expo(std::move(_expo)) {}

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
    
    void importDoc(File& file) override
    {
        std::cout << "Model: import document" << std::endl;
        component->SetObjectFile(file);
        notification();
    }
    
    void exportDoc() override
    {
        std::cout << "Model: Export document" << std::endl;
        component->save(expo.get());
    }

    void createShape(std::unique_ptr<Component> shape) override
    {
        std::cout << "Shape: create" << std::endl;
        if(component)
        {
            component->createShape(std::move(shape));
            notification();
        }
        else throw std::runtime_error("Create shape error: the file does not exist");
    }
    
    void deleteShape(std::size_t id) override
    {
        std::cout << "Shape: delete" << std::endl;
        if(component)
        {
            if(component->deleteShape(id))
                notification();
        }
        else throw std::runtime_error("Delete shape error: the file does not exist");
    }

};

