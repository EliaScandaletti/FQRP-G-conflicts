#include <parser/print.h>

#include <fstream>

using fqrp::vehicle_t;
using fqrp::aggregators::dist_count;
using fqrp::utils::distribution;
using std::cerr;
using std::endl;
using std::get;
using std::ofstream;
using std::string;
using std::tuple;
using std::vector;

void parser::print_table(const string &name,
                         const vector<tuple<vehicle_t, distribution>> &counts) {
  ofstream ofs(name + ".dat");
  if (!ofs) {
    cerr << "Unable to create file " + name + ".dat";
    cerr << "Check if the directory exists";
    throw "Unable to create file " + name + ".dat";
  }

  ofs << "n\tvalue\tfreq" << endl;
  for (auto &&tup : counts) {
    const vehicle_t &size = get<0>(tup);
    const distribution &dist = get<1>(tup);
    const vector<size_t> &_dist = dist.get();
    for (vehicle_t i = dist.min(); i <= dist.max(); i++) {
      ofs << size << '\t' << i << '\t' << _dist[i] << endl;
    }
  }

  ofs.close();
}

void parser::print_tables(const string &dir,
                          const vector<tuple<vehicle_t, dist_count>> &counts) {

  vector<tuple<vehicle_t, distribution>> arcType;
  vector<tuple<vehicle_t, distribution>> AType;
  vector<tuple<vehicle_t, distribution>> BType;

  vector<tuple<vehicle_t, distribution>> CGraph_max_length;
  vector<tuple<vehicle_t, distribution>> CGraph_tree_num;
  vector<tuple<vehicle_t, distribution>> CGraph_arcs_num;
  vector<tuple<vehicle_t, distribution>> CGraph_chain_num;
  vector<tuple<vehicle_t, distribution>> CGraph_vehicles_num;

  vector<tuple<vehicle_t, distribution>> MForest_tree_num;
  vector<tuple<vehicle_t, distribution>> MForest_max_tree_size;
  vector<tuple<vehicle_t, distribution>> MForest_nodes_num;
  vector<tuple<vehicle_t, distribution>> MForest_edges_num;

  for (auto &&tup : counts) {
    const vehicle_t &sample_size = get<0>(tup);
    const dist_count &count = get<1>(tup);

    arcType.push_back({sample_size, count.arcType});
    AType.push_back({sample_size, count.AType});
    BType.push_back({sample_size, count.BType});

    CGraph_max_length.push_back({sample_size, count.c_graph_dist.max_length});
    CGraph_tree_num.push_back({sample_size, count.c_graph_dist.tree_num});
    CGraph_arcs_num.push_back({sample_size, count.c_graph_dist.arcs_num});
    CGraph_chain_num.push_back({sample_size, count.c_graph_dist.chain_num});
    CGraph_vehicles_num.push_back(
        {sample_size, count.c_graph_dist.vehicles_num});

    MForest_tree_num.push_back({sample_size, count.mixed_forest_dist.tree_num});
    MForest_max_tree_size.push_back(
        {sample_size, count.mixed_forest_dist.max_tree_size});
    MForest_nodes_num.push_back(
        {sample_size, count.mixed_forest_dist.nodes_num});
    MForest_edges_num.push_back(
        {sample_size, count.mixed_forest_dist.edges_num});
  }

  print_table(dir + "arcType", arcType);
  print_table(dir + "AType", AType);
  print_table(dir + "BType", BType);

  print_table(dir + "CGraph_max_length", CGraph_max_length);
  print_table(dir + "CGraph_tree_num", CGraph_tree_num);
  print_table(dir + "CGraph_arcs_num", CGraph_arcs_num);
  print_table(dir + "CGraph_chain_num", CGraph_chain_num);
  print_table(dir + "CGraph_vehicles_num", CGraph_vehicles_num);

  print_table(dir + "MForest_tree_num", MForest_tree_num);
  print_table(dir + "MForest_max_tree_size", MForest_max_tree_size);
  print_table(dir + "MForest_nodes_num", MForest_nodes_num);
  print_table(dir + "MForest_edges_num", MForest_edges_num);
}