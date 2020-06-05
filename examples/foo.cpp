#include <cassert>
#include <iostream>
#include "leveldb/db.h"

using namespace std;

int main(int argc, char *argv[]) {
  // �����ݿ⡣����������򴴽�
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  options.compression = leveldb::kNoCompression;
  leveldb::Status s = leveldb::DB::Open(options, "./foo_db", &db);
  if (!s.ok()) {
    cerr << s.ToString() << endl;
    return 1;
  }

  // ��д����
  std::string k = "foo";
  std::string v;
  s = db->Put(leveldb::WriteOptions(), k, "bar");
  s = db->Get(leveldb::ReadOptions(), k, &v);

  // �����������ݿ�
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
  }
  if (!it->status().ok()) {
    cerr << it->status().ToString() << endl;
  }
  delete it;

  // �ر����ݿ�
  delete db;
  return 0;
}
