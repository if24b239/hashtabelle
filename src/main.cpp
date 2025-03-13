#include <hashtab.h>

#include <iostream>

int main() {

    HashTable* data = new HashTable();
    Share test("test", "bal", "blkoa");
    Share test1("test", "alb", "blloqwjma");
    Share test2("test", "bla", "blloiqa");

    data->save_in_map(test);
    data->save_in_map(test1);
    data->save_in_map(test2);

    data->delete_from_map(test.getToken());

    data->print_map();

    
    delete data;
}