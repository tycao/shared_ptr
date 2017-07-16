#include <iostream>
#include <memory>
using namespace std;


struct connection {};
struct destination {};

connection connect(destination *p)
{
    cout << "打开连接" << endl;
    return connection();
}

void disconnect(connection c)
{
    cout << "关闭连接" << endl;
}

//未使用智能指针shared_ptr
void f(destination &d)
{
    cout << "直接管理connect...." << endl;
    connection c = connect(&d);

    //忘记调用disconnect函数，关闭连接
    cout << endl;
}

void end_connection(connection *c) { disconnect(*c); }

//使用shared_ptr管理内存
void ff(destination &d)
{
    cout << "使用shared_ptr管理connect....." << endl;
    connection c = connect(&d);

    std::shared_ptr<connection> p(&c, &end_connection);

    //忘记调用disconnect函数，来关闭连接

    cout << endl;
}

int main()
{
    destination d;
    f(d);
    ff(d);

    return 0;
}
