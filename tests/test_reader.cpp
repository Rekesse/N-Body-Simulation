#include <gtest/gtest.h>
#include <Reader.hpp>

TEST(ReaderTest, readerFuncTest){
    Reader reader("../Data");
    const auto& dataMap = reader.getMap();
    
}