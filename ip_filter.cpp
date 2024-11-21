#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
static
std::vector<std::string> SplitBySymbol(const std::string & str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

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


int main( int argc, char const * argv[] )
{
  try {
    std::ifstream file( "ip_filter.tsv" ); // Открываем файл
    if ( !file.is_open() ) {
      std::cerr << "Opening file error!" << std::endl;
      return 1;
    }

    std::vector<std::vector<std::string> > ipPool;
    for ( std::string line; std::getline( file, line ); ) {
      auto v = SplitBySymbol( line, '\t' ); // std::vector<std::string>
      ipPool.push_back( SplitBySymbol( v.at( 0 ), '.' ) ); // Берем только первую часть и разбиваем символом '.'. Остальное отбрасываем.
    }

    // Сортируем IP-адреса в обратном лексикографическом порядке
    std::sort( ipPool.begin(), ipPool.end(), [] ( const std::vector<std::string> & ip1, const std::vector<std::string> & ip2 ) {
      const auto ip1Num = ParseIp( ip1 ); // std::vector<int>
      const auto ip2Num = ParseIp( ip2 ); // std::vector<int>
      return ip1Num > ip2Num; // Сравниваем вектора int'ов.
    } );


    // Запись результата в файл
    std::ofstream output( "ip_filter_sort.tsv" );
    if ( !output.is_open() ) {
      std::cerr << "Opening file error!" << std::endl;
      return 1;
    }


    // Написать метод для вывод котирый будут принимать lambda для выбора правильных ip
    // 
    // 
    // 
    // 1. Полный список адресов после сортировки.
    for ( const auto & ip : ipPool ) {
      for ( size_t i = 0; i < ip.size(); ++i ) {
        output << ip[i];
        if ( i < ip.size() - 1 ) {
          output << '.';
        }
      }
      output << '\n'; // Перенос строки после вывода IP
    }

    // 2. Cписок адресов, первый байт которых равен 1.
    for ( const auto & ip : ipPool ) {
      if ( ip.size() == 4 ) {
        const int fNum = std::stoi( ip[0] );
        if ( fNum == 1 ) {
          for ( size_t i = 0; i < ip.size(); ++i ) {
            output << ip[i];
            if ( i < ip.size() - 1 ) {
              output << '.';
            }
          }
          output << '\n'; // Перенос строки после вывода IP
        }
      }
    }

    // 3. Cписок адресов, первый байт которых равен 46, а второй 70
    for ( const auto & ip : ipPool ) {
      if ( ip.size() == 4 ) {
        const int fNum = std::stoi( ip[0] );
        const int thNum = std::stoi( ip[2] );
        if ( fNum == 46 && 70 ) {
          for ( size_t i = 0; i < ip.size(); ++i ) {
            output << ip[i];
            if ( i < ip.size() - 1 ) {
              output << '.';
            }
          }
          output << '\n'; // Перенос строки после вывода IP
        }
      }
    }

    // 4. Cписок адресов, первый байт которых равен 46, а второй 70
    for ( const auto & ip : ipPool ) {
      if ( ip.size() == 4 ) {
        const int fNum = std::stoi( ip[0] );
        const int thNum = std::stoi( ip[2] );
        if ( fNum == 46 && 70 ) {
          for ( size_t i = 0; i < ip.size(); ++i ) {
            output << ip[i];
            if ( i < ip.size() - 1 ) {
              output << '.';
            }
          }
          output << '\n'; // Перенос строки после вывода IP
        }
      }
    }


    std::cout << "Sorted IP-addresses have been write in ip_filter_sort.tsv" << std::endl;
  }
  catch ( const std::exception & e ) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
