#include <gtest/gtest.h>
#include <Reader.hpp>
#include <fstream>
#include <filesystem>

class ReaderTest : public::testing::Test{
    protected:
        std::filesystem::path fs{"testFolder"};
        std::filesystem::path testFile{"testFolder/TestFile.txt"};
        
        void SetUp(){
            std::filesystem::create_directory(fs);
            std::ofstream file{"testFolder/testFile.txt"};
            if(file.is_open()){
                file << "Hello '\n!!";
                file << "I'm learing C++'\n";

                file <<"$$SOE\n";
                file << "231132.0, Data, 1.5, 23.5, 4.56, 32.1, 4.21, 7.7\n";

                file.close();
            }
        }

        void TearDown() override {
            std::filesystem::remove_all(fs);
        }
};

TEST_F(ReaderTest, readerFuncTest){
    Reader reader("testFolder");
    reader.readData();
    const auto& dataMap = reader.getMap();

    EXPECT_DOUBLE_EQ(dataMap.at("testFile.txt")[0],1.5);
    
};