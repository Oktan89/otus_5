#pragma once
#include <iostream>
// #include "model.h"
#include "interface.h"

class View : public IView
{
    using model_type = std::shared_ptr<IModel>;
    using cont_type = std::shared_ptr<IController>;

    model_type _model;
    cont_type _cont;
public:

    View(const model_type model, const cont_type cont) : _model(model), _cont(cont)
    {
        _model->connect(this);
        std::cout << "Create View" << std::endl;
    }

    void update() override
    {
        std::cout << "Update View" << std::endl;
        _model->draw();
    }
    ~View()
    {
        _model->disconnect(this);
    }
};