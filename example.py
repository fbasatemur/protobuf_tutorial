from p_imports.person_info_pb2 import AddressBook


if __name__ == "__main__":
	address_book_from_file = AddressBook()
	file_name = "./encoding_cpp.pbuf"
	with open(file_name,"rb") as file:
		address_book_from_file.ParseFromString(file.read())

	print(address_book_from_file)