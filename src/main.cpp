#include <hashtab.h>

#include <iostream>

int main() {

    HashTable* data = new HashTable();
    Share test("test", "bla", "blkoa");
    Share test1("test", "bla", "blloqwjma");
    Share test2("test", "bla", "blloiqa");

    data->save_in_map(test);
    data->save_in_map(test1);
    data->save_in_map(test2);

    data->print_map();

    if (data->search_map("bla") != nullptr) {
        std::cout << data->search_map("bla")->getToken() << std::endl;
    }

    if (data->search_map("bljf") != nullptr) {
        std::cout << data->search_map("bljf")->getToken();
    }


    delete data;
}