/**
 * @file component.h
 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief Файл компонентов
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

/**
 * @brief Класс File унаследованный от абстрактного класса Component
 * 
 * Используется патерн компановщик для отрисовки содержимого документа
 */
class File : public Component
{
    using type_shaps = std::unique_ptr<Component>;

    std::size_t _id = id;
    std::string _file;
    std::list<type_shaps> _shaps;
   
public:
    
    /**
     * @brief Конструктор объекта File
     * 
     * @param file Имя фала
     */
    File(const std::string& file) : _file(file) {}

    /**
     * @brief Получить ID объекта
     * 
     * @return std::size_t 
     */
    std::size_t getId() const override
    {
        return _id;
    }

public:
    /**
     * @brief Получить имя файла
     * 
     * @return std::string 
     */
    std::string getName() const
    {
        return _file;
    }

    /**
     * @brief Получить колличество графических примитивов
     * 
     * @return std::size_t 
     */
    std::size_t getCountShaps() const
    {
        return _shaps.size();
    }

    /**
     * @brief Создание графического приметива в фале
     * 
     * @param shap Объект графического примитива унаследованного от Component 
     */
    void createShape(type_shaps shap)
    {
        _shaps.push_back(std::move(shap));
    }

    /**
     * @brief Удаление графического примитива
     * 
     * @param shape_id ID удаляемого объекта
     * @return true Объект успешно удален
     * @return false Объект не удален или не найден
     */
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

    /**
     * @brief Импорт файла
     * 
     * @param file Объект подготовленного файла
     */
    void SetObjectFile(std::unique_ptr<File> file)
    {
        _file = file->_file;
        //_id = file->_id;
        _shaps.swap(file->_shaps);
        
        reIndex(Component::id = 0);
    }

    /**
     * @brief Метод для патерна "посетитель"
     * 
     * @param vis Класс для сериализации объектов 
     */
    void accept(IVisitor * vis) override
    {
        vis->visit(this);        
    }
    
    /**
     * @brief Метод для начала сериализации (патерн "посетитель")
     * 
     * @param save 
     */
    void save(IVisitor* save)
    {
        accept(save);
        for(const auto& s : _shaps)
        {
            s->accept(save);      
        }
    }

    /**
     * @brief Метод ототрисоки объектов редактора (патерн "компоновщик")
     * 
     */
    void draw() override
    {
        ///@todo Место отрисовки документа
        std::cout << "Draw file " << _file << std::endl;
   
        for(const auto& s : _shaps)
        {
            s->draw();      
        }      
    }

    /**
     * @brief Метод переиндексации объектов после импорта
     * 
     * @param n_id Начальное значение ID объектов
     * @warning Требуется передать обнуленный статический член ID объекта Component::id
     */
   void reIndex(std::size_t& n_id) override
    {
        _id = ++n_id;
        for(auto& s : _shaps)
        {
            s->reIndex(++n_id);
        }    
    }
};

/**
 * @brief Класс точка
 * 
 * Реализует абстрактный класс Component
 * Рисует точку в графическом редакторе
 */
class Dot : public Component
{
   coordinates _cord;
   std::size_t _id = id;
    
public:
    /**
     * @brief Конструктор объекта Точка
     * 
     * @param cord Структора координат
     */
    Dot(const coordinates& cord) : _cord(cord) {}
    /**
     * @brief Конструктор объекта Точка
     * 
     * @param x координата х
     * @param y координата у
     */
    Dot(std::size_t x, std::size_t y) : _cord(x, y) {}
    
    /**
     * @brief Получить ID объекта
     * 
     * @return std::size_t 
     */
    std::size_t getId() const override
    {
        return _id;
    }
protected:
    void reIndex(std::size_t& id) override
    {
        _id = id;
    }
public:
    /**
     * @brief Метод начинающий сериализацию объекта
     * 
     * @param vis Объект посетитель
     */
    void accept(IVisitor * vis) override
    {
        vis->visit(this);
    }

    /**
     * @brief Метод отрисовки точки в редакторе
     * 
     */
    void draw() override
    {
       std::cout << "Draw Dot id "<<_id<<": (.) x" << _cord._x <<" y:"<< _cord._y << std::endl;
    }

};

/**
 * @brief Класс линия
 * 
 * Реализует абстрактный класс Component
 * Рисует линию в графическом редакторе по двум точкам
 */
class Line : public Component
{
private:
   Dot _one;
   Dot _two;
   std::size_t _id = id;
public:
    /**
     * @brief Конструктор Линии
     * 
     * @param one структура координат точки 1
     * @param two структура координат точки 2
     */
    Line(const Dot& one, const Dot& two) : _one(one), _two(two) {}

    /**
     * @brief Получить ID объекта
     * 
     * @return std::size_t 
     */
    std::size_t getId() const override
    {
        return _id;
    }

protected:
    void reIndex(std::size_t& id) override
    {
        _id = id;
    }
public:
    /**
     * @brief Метод начинающий сериализацию объекта
     * 
     * @param vis Объект посетитель
     */
    void accept(IVisitor * vis) override
    {
        vis->visit(this);
    }

    /**
    * @brief Метод отрисовки линии в редакторе
    * 
    */
    void draw() override
    {
       std::cout << "Draw Line "<<_id<<": ------------" << std::endl;
         _one.draw();
         _two.draw();
    }

};