#include <iostream>
#include <memory>
#include "lib.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include "component.h"

int main(int, char**)
{   
    
    std::shared_ptr<Editor> model = std::make_shared<Editor>();
    std::shared_ptr<Controller> cont = std::make_shared<Controller>(model);
    auto view = View::create(model);
    
    std::unique_ptr<Dot> dt = std::make_unique<Dot>(5, 6);
    std::unique_ptr<Line> ln = std::make_unique<Line>(Dot{10, 4}, Dot{2, 4});
    std::unique_ptr<Line> ln2 = std::make_unique<Line>(Dot{100, 44}, Dot{20, 64});

        
    cont->createDoc("Test.jpg");
    cont->createShape(std::move(dt));
    cont->createShape(std::move(ln));
    cont->createShape(std::move(ln2));
    cont->deleteShape(7);
    
    cont->exportDoc();
    return 0;
}