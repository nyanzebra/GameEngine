#pragma once

#include <memory>
#include <map>

#define MAX_ENTRIES 1000
#define MAX_TABLES 100

typedef std::pair<std::string, std::string> TABLE_PAIR;
typedef std::multimap<std::string, std::string> TABLE;

class Table {
public:
	Table() = default;
	~Table() = default;

	void add(const std::string& column_name, const std::string& table_item) {
		if (table.size() == MAX_ENTRIES) {
			return;
		}

		table.insert(TABLE_PAIR(column_name, table_item));
	}

	void add(const std::string& column_name, const std::list<std::string>& table_items) {
		if (table.size() == MAX_ENTRIES) {
			return;
		}

		for (std::string table_item : table_items) {
			table.insert(TABLE_PAIR(column_name, table_item));
		}
	}
	
	TABLE::const_iterator operator[](const std::string& column_name) const {
		return table.find(column_name);
	}

	const unsigned entries(const std::string& column_name) const {
		return table.count(column_name);
	}

	const unsigned columns() {
		unsigned columns = 0;
		std::string previous_key = table.cbegin()->first;
		for (TABLE::const_iterator it = table.cbegin(); it != table.cend(); ++it) {
			if (previous_key != it->first) {
				columns++;
				previous_key = it->first;
			}
		}
		return columns;
	}

private:
	TABLE table;
};
