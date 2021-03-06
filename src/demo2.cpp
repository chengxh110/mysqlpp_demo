#include "cmdline.h"
// #include "printdata.h"

#include <mysql++.h>

#include <iomanip>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  // Get database access parameters from command line
  mysqlpp::examples::CommandLine cmdline(argc, argv);
  if (!cmdline) {
    return 1;
  }

  // Connect to the sample database.
  mysqlpp::Connection conn(false);
  if (conn.connect(mysqlpp::examples::db_name, cmdline.server(), cmdline.user(),
                   cmdline.pass())) {
    // Retrieve the sample stock table set up by resetdb
    mysqlpp::Query query = conn.query("select * from stock");
    mysqlpp::StoreQueryResult res = query.store();

    // Display results
    if (res) {
      // Display header
      cout.setf(ios::left);
      cout << setw(31) << "Item" 
           << setw(10) << "Num" 
           << setw(10) << "Weight"
           << setw(10) << "Price"
           << "Date" << endl
           << endl;

      // Get each row in result set, and print its contents
      for (size_t i = 0; i < res.num_rows(); ++i) {
        cout << setw(30) << res[i]["item"] << ' ' 
        << setw(9) << res[i]["num"] << ' ' 
        << setw(9) << res[i]["weight"] << ' ' 
        << setw(9) << res[i]["price"] << ' ' 
        << setw(9) << res[i]["sdate"] << endl;
      }
    } else {
      cerr << "Failed to get stock table: " << query.error() << endl;
      return 1;
    }

    return 0;
  } else {
    cerr << "DB connection failed: " << conn.error() << endl;
    return 1;
  }
}