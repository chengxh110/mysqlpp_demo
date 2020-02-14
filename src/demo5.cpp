#include <mysql++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
using namespace mysqlpp;

// insert into c1(id, name, status) values(22, "laoyang", "ok");
const char* g_szInsertFormat =
    "insert into c1(id, name, status) values(%d, \"%s\", \"%s\");";
const char* g_szUpdateFormat = "update c1 set name = \"%s\" where id = %d;";
const char* g_szDeleteFormat = "delete from c1 where id = %d;";
const char* g_szSearchFormat = "select * from c1;";

// #define DATEBASE_NAME "demo5"
// // #define DATEBASE_IP "192.168.1.1"
// #define DATEBASE_SERVER "localhost"
// #define DATEBASE_USERNAME "root"
// #define DATEBASE_PWD "123"

const char *db = "demo5";
const char *server = "localhost";
const char *user = "root";
const char *password = "123";


#define DATA_BUF_SIZE 2048

//增
void insertFun(Query* pQuery) {
  cout << "Inserting test" << endl;
  char szInsert[DATA_BUF_SIZE] = {0};
  memset(szInsert, 0, DATA_BUF_SIZE);
  int iId = 66;
  const char* pszName = "Miss Zhangx";
  const char* pszStatus = "OK";

  sprintf((char*)szInsert, g_szInsertFormat, iId, pszName, pszStatus);
  cout << "szInsert = " << szInsert << endl;

  *pQuery << szInsert;
  SimpleResult res = pQuery->execute();
  // Report successful insertion
  cout << "Inserted into c1 table, ID =" << res.insert_id() << endl;
  cout << endl;
}

//删
void deleteFun(Query* pQuery) {
  cout << "deleting test" << endl;
  char szDelete[DATA_BUF_SIZE] = {0};
  int iId = 44;
  memset(szDelete, 0, DATA_BUF_SIZE);
  sprintf((char*)szDelete, g_szDeleteFormat, iId);
  cout << "szDelete = " << szDelete << endl;

  *pQuery << szDelete;
  if (pQuery->exec()) {
    cout << "deleted success!" << endl;
  }
  cout << endl;
}

//改
void updateFun(Query* pQuery) {
  cout << "updating test" << endl;
  char szUpdate[DATA_BUF_SIZE] = {0};
  memset(szUpdate, 0, DATA_BUF_SIZE);

  int iId = 2;
  const char* pszNewName = "new line 2 revise";

  sprintf((char*)szUpdate, g_szUpdateFormat, pszNewName, iId);
  cout << "szUpdate = " << szUpdate << endl;

  *pQuery << szUpdate;
  if (pQuery->exec()) {
    cout << "updated success!" << endl;
  }
  cout << endl;
}

//查
void searchFun(Query* pQuery) {
  /* Now SELECT */
  cout << "selecting test:" << endl;
  *pQuery << g_szSearchFormat;
  StoreQueryResult ares = pQuery->store();
  cout << "ares.num_rows() = " << ares.num_rows() << endl;
  for (size_t i = 0; i < ares.num_rows(); i++) {
    cout << "id: " << ares[i]["id"] << "\t - Name: " << ares[i]["name"]
         << "\t - Status: " << ares[i]["status"] << "\t - Modified_at"
         << ares[i]["modified_at"] << endl;
  }

  /* Let's get a count of something */
  *pQuery << "SELECT COUNT(*) AS row_count FROM c1";
  StoreQueryResult bres = pQuery->store();
  cout << "Total rows: " << bres[0]["row_count"] << endl;
  cout << endl;
}

int main() {
  try {
    Connection conn(false);
    // conn.connect(DATEBASE_NAME, DATEBASE_SERVER, DATEBASE_USERNAME,
    // DATEBASE_PWD);
    if (conn.connect(db, server, user, password)) {
      Query query = conn.query();

      /*insert , delete , update, search testing */
      (void)insertFun(&query);
      (void)deleteFun(&query);
      (void)updateFun(&query);
      (void)searchFun(&query);
    }
  } catch (BadQuery er) {  // handle any connection or
    // query errors that may come up
    cerr << "Error: " << er.what() << endl;
    return -1;
  } catch (const BadConversion& er) {
    // Handle bad conversions
    cerr << "Conversion error: " << er.what() << endl
         << "\tretrieved data size: " << er.retrieved
         << ", actual size: " << er.actual_size << endl;
    return -1;
  } catch (const Exception& er) {
    // Catch-all for any other MySQL++ exceptions
    cerr << "Error: " << er.what() << endl;
    return -1;
  }

  return (EXIT_SUCCESS);
}
