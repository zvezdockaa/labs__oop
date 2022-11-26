// structurees.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
struct Marsh {
    std::string begst;
    std::string term;
    int numer;

};
int main()
{
    Marsh* traffic = new Marsh[8];
    std::cout << "Input root data";
    for (int i = 0; i < 8; i++) {
        std::cin >> traffic[i].begst;
        std::cin >> traffic[i].term;
        std::cin >> traffic[i].numer;

    }
    int number_of_input_root;
    bool check_in= false;
    std::cout << "Input number of root";
    std::cin >> number_of_input_root;
    for (int i = 0; i < 8; i++) {
            if (number_of_input_root == traffic[i].numer) {
                check_in = true;
                std::cout << traffic[i].begst;
                std::cout << traffic[i].term;

            }
            
        }
    
        if (check_in == false) {
            std::cout << "No root to find";

        }
    }


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
