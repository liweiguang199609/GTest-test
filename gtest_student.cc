#include<gtest/gtest.h>
#include<map>
#include<iostream>
using namespace std;
class Student{
public:
    Student(){
        age_=0;
    }
    Student(int age){
        age_=age;
    }
    int GetAge(){
        return age_;
    } 
    void SetAge(int age){
        age_ = age;
    } 
    void print(){
        cout<<"*********** "<<age_<<" **********"<<endl;;
    }   
private:
    int age_;
};
class FooEnvironment : public testing::Environment{
public:
    FooEnvironment(){
        cout << "lwg";
    }
    virtual void SetUp()
    {
        std::cout << "Foo FooEnvironment SetUP" << std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "Foo FooEnvironment TearDown" << std::endl;
    }
private:
    Student *s_;
};
//在第一个test之前，最后一个test之后调用SetUpTestCase()和TearDownTestCase()
class TestMap:public testing::Test
{
public:
    TestMap(){
        s_ = new Student(23);
    }
    TestMap(int n){
        s_ = new Student(n);
    }

    ~TestMap(){

    }

    void ChangeStudentAge(int n){
        share_ = n;
        s_->SetAge(n);
        cout << "Student age is " << s_->GetAge() << "; share_ is "<< share_ <<endl;
    }
    void PrintAge(){
        cout << "Student age is " << s_->GetAge() << "; share_ is "<< share_ <<endl;
    }

    /*下述两个函数针对一个TestSuite*/
    static void SetUpTestCase()
    {
        cout<<"SetUpTestCase()"<<endl;
    }
 
    static void TearDownTestCase()
    {
        //delete s;
        cout<<"TearDownTestCase()"<<endl;
    }
    /* 下述两个函数针对每个TEST*/
    void SetUp()//构造后调用
    {
        cout<<"SetUp() is running"<<endl;
         
    }
    void TearDown()//析构前调用
    {
        cout<<"TearDown()"<<endl;
    }  
private:
    Student *s_;
    static int share_;
};

class IsPrimeParamTest : public::testing::TestWithParam<int>{};

TEST_P(IsPrimeParamTest, HandleTrueReturn)
{
    int n =  GetParam();
    cout << n << endl;
}
INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3,4,7));
 
int TestMap::share_ = 0;
TEST_F(TestMap, Test1)
 {
    ChangeStudentAge(5);
    //ChangeStudentAge(55)
    // you can refer to s here
    //print();
}
TEST_F(TestMap, Test2)
 {
    ChangeStudentAge(55);
    // you can refer to s here
    //print();
}
TEST_F(TestMap, Test3)
 {
    PrintAge();
    // you can refer to s here
    //print();
}

int main(int argc, char  **argv)
{
    testing::AddGlobalTestEnvironment(new FooEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

