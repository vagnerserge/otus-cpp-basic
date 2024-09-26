#include "vector_container.h"
#include"list_container.h"
template <typename T>
void print_container( T& container )
{
	for ( size_t i = 0; i < container.size(); ++i )
	{
		if ( i != 0 )
			std::cout << ' ';
		std::cout << container[i];
	}
}


template <typename T>
void PerformData( T& int_container ){
	for ( int i = 0; i <= 9; ++i ) {
		int_container.push_back( i );
	}
	print_container( int_container );
	std::cout << std::endl;
	std::cout << int_container.size() << std::endl;
	int_container.erase( 3 );
  int_container.erase( 4 );
  int_container.erase( 5 );
 	print_container( int_container );
	std::cout << std::endl;

	int_container.insert( 0, 10 );
	print_container(int_container);
	std::cout << std::endl;

	int_container.insert( 4, 20 );
	print_container( int_container );
	std::cout << std::endl;

	int_container.insert( int_container.size(), 30 );
	print_container( int_container );
	std::cout << std::endl;
}

int main()
{
	ListContainer<int> int_list;
	VectorContainer<int> int_vector;
	PerformData( int_list );
	PerformData( int_vector );
	return 0;
}