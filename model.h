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
// #include "view.h"

/**
 * @brief Базовый класс для моделей работы векторного редактора
 * 
 */
class __BaseModelDoc : public IModelDoc
{
    std::list<IView*> _subs;
 
public:
   
    void subscription(IView* view) override
    {
        _subs.push_back(view);
    }

    void unsubscribe(IView* view) override
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

     __BaseModelDoc() = default;
    ~__BaseModelDoc() = default;
};

class Doc : public __BaseModelDoc
{

public:

    void createDoc() override
    {
        std::cout << "Model: create document" << std::endl;
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

};
