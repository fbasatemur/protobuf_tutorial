#include <iostream>
#include <fstream>
#include "person_info.pb.h"

int main(){
    personcontact::AddressBook address_book;
    personcontact::Person* person = address_book.add_people();
    person->set_name("Bjarne Stroustrup");
    person->set_age(72);
    person->set_height(1.75);
    person->set_address("USA");

    personcontact::Person_Contact* contact = person->add_contact();
    contact->set_email("CwC@bell.com");
    contact->add_phone("0123456789");

    // data serialize and write to local file
    std::fstream out_stream("../encoding_cpp.pbuf", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!address_book.SerializePartialToOstream(&out_stream))
    {
        std::cerr << "Failed to write adress book" << std::endl;
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}