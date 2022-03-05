#include "lib.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "component.h"
#include "model.h"
#include "controller.h"
#include "view.h"
#include <string>




TEST(testVersionGoogle, ValidVersion) {

  EXPECT_GT(version(), 0);
}

class TestEditor : public ::testing::Test
{
protected:
  void SetUp() override
  {
      model = std::make_shared<Editor>();
      cont = std::make_shared<Controller>(model);
      view = View::create(model);
  }
  void TearDown() override
  {
  
  }
  std::shared_ptr<Editor> model;
  std::shared_ptr<Controller> cont;
  std::shared_ptr<View> view;
};

TEST_F(TestEditor, CreateDoc)
{
  cont->createDoc("test.jpg");
  auto name = model->getFileName();
  ASSERT_STREQ(name.c_str(), "test.jpg");
}

TEST_F(TestEditor, CreateShapsAndDeleteShaps)
{
  auto dot = std::make_unique<Dot>(10, 10);
  auto line = std::make_unique<Line>(Dot{1, 2}, Dot{100, 200});
  cont->createDoc("test.jpg");
  std::size_t id = cont->createShape(std::move(dot));
  cont->createShape(std::move(line));
  ASSERT_EQ(2, model->getCountShapes());
  cont->deleteShape(id);
  ASSERT_EQ(1, model->getCountShapes());
}

TEST_F(TestEditor, ImportDoc)
{
  cont->createDoc("test.jpg");
  cont->createShape(std::make_unique<Dot>(10, 10));
  cont->createShape(std::make_unique<Line>(Dot{1, 2}, Dot{100, 200}));
  cont->createShape(std::make_unique<Line>(Dot{12, 23}, Dot{10, 210}));
  ASSERT_EQ(3, model->getCountShapes());

    {
        auto test = std::make_unique<File>("test2.png");
        test->createShape(std::make_unique<Dot>(10,12));
        test->createShape(std::make_unique<Dot>(100,152));
        cont->importDoc(std::move(test));
    }
  auto name = model->getFileName();
  ASSERT_STREQ(name.c_str(), "test2.png");
  ASSERT_EQ(2, model->getCountShapes());
}