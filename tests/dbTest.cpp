// #include "../src/backend/db/database.h"
// #include "../src/backend/db/database.h"
// #include "../src/backend/db/collection.h"
// #include "../src/backend/db/document.h"
// #include <iostream>

// using namespace std;

// int main() {
    
//     // TEST CASE 1
//     Document doc1(1);   // create Document
//     Collection collect1(1, "collect1");    // create Collection
//     Database db1(1, "myDB", "collect1");   // create Database

//     if (db1.get_name() == "myDB") {
//         cout << db1.get_name() << " is myDB - test 1 PASSED" << endl;
//     }
//     else {
//         cout << db1.get_name() << "is not myDB - test 1 FAILED" << endl;
//     }

//     if (db1.get_id() == 1) {
//         cout << db1.get_id() << " is 1 - test 2 PASSED" << endl;
//     }
//     else {
//         cout << db1.get_id() << " is not 1 - test 2 FAILED" << endl;
//     }


//     // Database db2();

//     // if (db2.get_name() == "default db") {
//     //     cout << db2.get_name() << " is default db - test 3 PASSED" << endl;
//     // }
//     // else {
//     //     cout << db2.get_name() << " is not default db - test 3 FAILED" << endl;
//     // }

//     // if (db2.get_id() == 9999) {
//     //     cout << db2.get_id() << " is 9999 - test 4 PASSED" << endl;
//     // }
//     // else {
//     //     cout << db2.get_id() << " is not 9999 - test 4 FAILED" << endl;
//     // }

//     // TEST 3
//     Database db3(3,"", "collect2");
//     Database db4(4, "myDB", "");

    

//     return 0;
// }
