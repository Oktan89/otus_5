#include <iostream>
#include <memory>
#include "lib.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include "component.h"

int main(int, char**)
{   
    
    auto model = std::make_shared<Editor>();
    auto cont = std::make_shared<Controller>(model);
    auto view = View::create(model);
    
    auto dt = std::make_unique<Dot>(5, 6);
    auto ln = std::make_unique<Line>(Dot{10, 4}, Dot{2, 4});
    auto ln2 = std::make_unique<Line>(Dot{100, 44}, Dot{20, 64});


    cont->createDoc("Test.jpg");
    cont->createShape(std::move(dt));
    cont->createShape(std::move(ln));
    cont->createShape(std::move(ln2));
    cont->deleteShape(7);
    cont->exportDoc();

    {
        auto test = std::make_unique<File>("test.png");
        test->createShape(std::make_unique<Dot>(10,12));
        test->createShape(std::make_unique<Dot>(100,152));
        cont->importDoc(std::move(test));
    }
    cont->createShape(std::make_unique<Line>(Dot{10, 4}, Dot{2, 4}));
    return 0;
}