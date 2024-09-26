#include <gtest/gtest.h>
#include <vector>

struct VectorTest : public testing::Test {

  const size_t elementCount = 10;
  std::vector<size_t> vector; //the same vector instance for all test cases
  // Per-test set-up
  void SetUp() override {
    std::cout << "SetUp" << std::endl;
    // Create vector with elementCount elements
    for ( size_t i = 0; i < elementCount; ++i )
      vector.push_back( i );
  }

};


TEST(vector, Create) {
  std::vector<int> vector;
  ASSERT_EQ(vector.size(), 0);
  ASSERT_TRUE(vector.empty());
}

TEST_F(VectorTest, PushBack) {
  vector.push_back(20);
  ASSERT_EQ(vector.size(), 11);
  ASSERT_EQ(vector.back(), 20);
}

TEST_F(VectorTest, PopBack) {
  vector.pop_back();
  ASSERT_EQ(vector.size(), 9);
  ASSERT_EQ(vector.back(), 8);

}

TEST_F(VectorTest, Insert) {
  vector.insert(vector.begin() + 5, 60);
  ASSERT_EQ(vector.size(), 11); //вставка произошла
  // проверяем, что элемент 60 вставился между 4 и 5.
  ASSERT_EQ(vector[6], 5);
  ASSERT_EQ(vector[5], 60);
  ASSERT_EQ(vector[4], 4);

}

TEST_F(VectorTest, PushFront) {
  vector.insert(vector.begin(),20);
  ASSERT_EQ(vector.size(), 11);
  ASSERT_EQ(vector.front(), 20);
}

TEST_F(VectorTest, PopFront) {
  vector.erase(vector.begin());
  ASSERT_EQ(vector.size(), 9);
  ASSERT_EQ(vector.front(), 1);

}

TEST_F(VectorTest, Erase) {
  vector.erase(vector.begin()+5);
  ASSERT_EQ(vector.size(), 9); //удаление произошло
  // проверяем, что удалился элемент между 4 и 6.
  ASSERT_EQ(vector[4], 4);
  ASSERT_EQ(vector[5], 6);

}

TEST_F(VectorTest, Size) {
  ASSERT_EQ(vector.size(), 10);
}

TEST_F(VectorTest, Getelement) {
  size_t arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  size_t i = 0;

  for (size_t elem : vector)
    ASSERT_EQ(elem, arr[i++]); //can't understand where is failure
}

TEST_F(VectorTest, Clear) {
  vector.clear();
  ASSERT_EQ(vector.size(), 0);
  ASSERT_TRUE(vector.empty());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}