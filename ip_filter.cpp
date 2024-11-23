#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
static
std::vector<std::string> SplitBySymbol( const std::string & str, char d )
{
  std::vector<std::string> r;
  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of( d );
  while ( stop != std::string::npos ) {
    r.push_back( str.substr( start, stop - start ) );
    start = stop + 1;
    stop = str.find_first_of( d, start );
  }
  r.push_back( str.substr( start ) );
  return r;
}

// Преобразование массива IP в массив чисел.
static
std::vector<int> ParseIp( const std::vector<std::string> & ip ) {
  std::vector<int> result;
  for ( const auto & octet : ip ) {
    result.push_back( std::stoi( octet ) );
  }
  return result;
}

static
void WriteIpAddresses( std::ofstream & output, const std::vector<std::vector<std::string>> & ipPool,
                       const std::function<bool( const std::vector<std::string> & )> & filter = nullptr ) {
  for ( const auto & ip : ipPool ) {
    if ( !filter ||    // Фильтр не задан.
         filter( ip )  // Фильтр задан. 
         ) {
      for ( size_t i = 0; i < ip.size(); ++i ) {
        output << ip[i];
        if ( i < ip.size() - 1 ) {
          output << '.';
        }
      }
      output << '\n';
    }
  }
}


int main( int argc, char const * argv[] ) {
  try {
    std::ifstream file( "ip_filter.tsv" ); // Открываем файл
    if ( !file.is_open() ) {
      std::cerr << "Opening file error!" << std::endl;
      return 1;
    }

    // Читаем ip-адреса и сохраняем только значимые данные
    std::vector<std::vector<std::string>> ipPool;
    for ( std::string line; std::getline( file, line ); ) {
      auto v = SplitBySymbol( line, '\t' );
      ipPool.push_back( SplitBySymbol( v.at( 0 ), '.' ) );
    }

    // Сортируем IP-адреса в обратном лексикографическом порядке
    std::sort( ipPool.begin(), ipPool.end(), [] ( const std::vector<std::string> & ip1, const std::vector<std::string> & ip2 ) {
      return ParseIp( ip1 ) > ParseIp( ip2 );
    } );

    // Открываем файл для записи
    std::ofstream output( "ip_filter_sort.tsv" );
    if ( !output.is_open() ) {
      std::cerr << "Opening file error!" << std::endl;
      return 1;
    }

    // Записываем результаты с фильтрацией
    WriteIpAddresses( output, ipPool ); // Полный список
    WriteIpAddresses( output, ipPool, [] ( const std::vector<std::string> & ip ) {
      return ip.size() == 4 && std::stoi( ip[0] ) == 1; // Первый байт равен 1
    } );
    WriteIpAddresses( output, ipPool, [] ( const std::vector<std::string> & ip ) {
      return ip.size() == 4 && std::stoi( ip[0] ) == 46 && std::stoi( ip[1] ) == 70; // Первый байт равен 46, второй 70
    } );
    WriteIpAddresses( output, ipPool, [] ( const std::vector<std::string> & ip ) {
      return std::any_of( ip.begin(), ip.end(), [] ( const std::string & byte ) {
        return byte == "46"; // Любой байт равен 46
      } );
    } );
    std::cout << "Sorted IP-addresses have been written to ip_filter_sort.tsv" << std::endl;
  }
  catch ( const std::exception & e ) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
