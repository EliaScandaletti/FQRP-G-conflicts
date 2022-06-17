#include <parser/parse.h>
#include <parser/print.h>

#include <fstream>
#include <tuple>
#include <vector>

using fqrp::vehicle_t;
using fqrp::aggregators::dist_count;
using parser::parse;
using parser::print_table;
using parser::print_tables;
using std::cerr;
using std::endl;

template <typename... T> void ignore(T...);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " input_file output_prefix" << endl;
    return 1;
  }

  std::ifstream ifs(argv[1]);
  if (!ifs) {
    cerr << "File " << argv[1] << " not found" << endl;
    return 1;
  }

  std::vector<std::tuple<vehicle_t, dist_count>> counts = parse(ifs);
  ifs.close();

  print_tables(argv[2], counts);

  return 0;
}
