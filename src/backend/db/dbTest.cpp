#include "database.h"
#include "collection.h"
#include "document.h"
#include <iostream>

using namespace std;

int main() {
    
    // TEST CASE 1
    Document doc1(1);   // create Document
    Collection collect1("collect1");    // create Collection
    Database db1("myDB", "collect1");   // create Database
    if (db1.get_name() == "myDB") {
        cout << db1.get_name() << " test 1 PASSED" << endl;
    }
    else {
        cout << db1.get_name() << "is not myDB  test 1 FAILED" << endl;
    }


    return 0;
}