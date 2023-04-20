#include "collection.h"
#include <iostream>
using namespace std;
Collection::Collection(string name){
    this->name=name;
}
void Collection::add_document(int id){
//    Document temp = Document(id);
   collection.insert({id,Document(id)});
}
Document Collection::get_document(int id){
    return collection[id];
}
string Collection::get_name(){
    return name;
}