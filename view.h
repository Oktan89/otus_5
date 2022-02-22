#pragma once
#include <iostream>
// #include "model.h"
#include "interface.h"

class View : public IView
{
    using model_type = std::shared_ptr<IModelDoc>;
    using cont_type = std::shared_ptr<IController>;

    model_type _model;
    cont_type _cont;
public:

    View(model_type model, cont_type cont)
        : _model(model), _cont(cont)
    {
        _model->subscription(this);
        std::cout << "Create View" << std::endl;
    }

    void createDoc()
    {
        _cont->createDoc();
    }
    void update() override
    {
        std::cout << "Update View" << std::endl;
    }
    ~View()
    {
        _model->unsubscribe(this);
    }
};