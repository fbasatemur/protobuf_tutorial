# protobuf cpp <-> python tutorial

In this repository, a common packet structure will be established between Python and C++ languages using protobuf. Afterwards, the contents of the packet will be observed by performing encode and decode operations. For the sake of simplicity, packet reading will be done through a file instead of using an RPC server and client.

Useful resources for analyzing the example and gaining knowledge about protobuf:

- https://blog.conan.io/2019/03/06/Serializing-your-data-with-Protobuf.html
- https://opensource.com/article/19/10/protobuf-data-interchange

Helpful main resource for creating a proto file. -> [google/proto](https://developers.google.com/protocol-buffers/docs/proto3)

![uml_img](https://github.com/fbasatemur/protobuf_tutorial/blob/main/docs/uml_img.png)

A common packet structure for communication. (.proto file)

```c
message AddressBook
{
    repeated Person people = 1;
}

message Person{
    string name = 1;         // encoding sequence length
    uint32 age = 2;          // encoding varint length
    float height = 3;        // encoding fixed length
    string address = 4;      // encoding sequence length
    
    repeated Contact contact = 5;    

    message Contact
    {
        string email = 1;
        repeated string phone = 2;      // "repeated" can be repeated any number of times (including zero) in a well-formed message. 
    }

}
```


Header files should be generated using the protoc compiler to provide message packet definition.
The Python and C++ header files are generated in the `p_imports` folder.

```cpp
protoc --cpp_out=p_imports person_info.proto            // person_info.pb.h person_info.pb.cc
protoc --python_out=p_imports person_info.proto         // person_info_pb2.py 
```

`example.cc`
```cpp
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
```


Let's produce the encoded data. (Data serilization)
```bash
mkdir build && cd build 
cmake .. && make && ./encoding_cpp
```
`example.py`

```python
if __name__ == "__main__":
	address_book_from_file = AddressBook()
	file_name = "./encoding_cpp.pbuf"
	with open(file_name,"rb") as file:
		address_book_from_file.ParseFromString(file.read())

	print(address_book_from_file)
```

The result obtained when running the `example.py` file.

![msg_img](https://github.com/fbasatemur/protobuf_tutorial/blob/main/docs/output_img.png)



