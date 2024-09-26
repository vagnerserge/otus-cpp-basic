
#include <gtest/gtest.h>
#include <list>
#include <random>  // Для генерации случайных чисел

struct ListTest : public testing::Test {

  const size_t size = 10;
  std::list<double> doubleList; //the same list instance for all test cases
  // Per-test set-up
  void SetUp() override {
    std::cout << "SetUp" << std::endl;
    // Create list with elementCount elements
    for (size_t i = 0; i < size; ++i)
      doubleList.push_back(static_cast<double>(i));
  } 
};

// 1
TEST(List, Emptyness) {
  std::list<bool> emptyList;
  ASSERT_EQ( emptyList.size(), 0 );
  ASSERT_TRUE( emptyList.empty() );
} 

// 2
TEST_F(ListTest, PushBack) {
   doubleList.push_back(0.5);
   ASSERT_EQ(doubleList.size(), 11);
   ASSERT_EQ(doubleList.back(), 0.5);
}

// 3
TEST_F(ListTest, PopBack) {
  doubleList.pop_back();
  ASSERT_EQ(doubleList.size(), 9);
  ASSERT_EQ(doubleList.back(), 8.); 
}

// 4
TEST_F(ListTest, PushFront) {
  doubleList.push_front(20.);
  ASSERT_EQ(doubleList.size(), 11);
  ASSERT_EQ(doubleList.front(), 20);
}

// 5
TEST_F(ListTest, PopFront) {
  doubleList.pop_front();
  ASSERT_EQ(doubleList.size(), 9);
  ASSERT_EQ(doubleList.front(), 1);

}

// 6
TEST_F(ListTest, Size) {
  ASSERT_EQ(doubleList.size(), 10);
}


// 7
TEST_F(ListTest, Clear) {
  doubleList.clear();
  ASSERT_EQ(doubleList.size(), 0);
  ASSERT_TRUE(doubleList.empty());
}

// 8
TEST_F( ListTest, Reverse ) {
  doubleList.reverse();  // Разворачиваем список
  ASSERT_EQ( doubleList.front(), 9. );  // Проверяем, что последний элемент стал первым
  ASSERT_EQ( doubleList.back(), 0.0 );  // Проверяем, что первый элемент стал последним
}

// 9
TEST_F( ListTest, Merge ) {
  std::list<double> anotherList = { 1.1, 3.3, 5.5 };
  doubleList.merge( anotherList );  // Слияние двух списков (оба должны быть отсортированы)

  ASSERT_EQ( doubleList.size(), 13 );  // Проверяем размер
  ASSERT_TRUE( anotherList.empty() );  // Проверяем, что другой список пуст после слияния
}

// 10
TEST_F( ListTest, Swap ) {
  std::list<double> anotherList = { 1.1, 2.2, 3.3 };
  doubleList.swap( anotherList );  // Меняем содержимое двух списков

  ASSERT_EQ( doubleList.size(), 3 );  // Проверяем, что doubleList теперь имеет 3 элемента
  ASSERT_EQ( doubleList.front(), 1.1 );  // Проверяем первый элемент
  ASSERT_EQ( anotherList.size(), 10 );  // Проверяем, что другой список теперь имеет 10 элементов
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}