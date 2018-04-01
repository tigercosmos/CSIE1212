#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Data {
  string date;
  string currency;
  string exchange;
  float low;
  float high;
  int capital;
};

static void split(Data &d, const string &s, char delimiter) {
  string token;
  istringstream tokenStream(s);
  int i = 0;
  while (getline(tokenStream, token, delimiter)) {
    switch (i) {
    case 0:
      d.date = token;
      break;
    case 1:
      d.currency = token;
      break;
    case 2:
      d.exchange = token;
      break;
    case 3:
      d.low = stof(token);
      break;
    case 4:
      d.high = stof(token);
      break;
    case 5:
      d.capital = stol(token);
      break;
    default:
      break;
    }
    i++;
  }
}

static bool exchangeCmp(Data const &a, Data const &b) {
  return a.exchange < b.exchange;
}

static bool dateCmp(Data const &a, Data const &b) { return a.date < b.date; }

static bool currencyCmp(Data const &a, Data const &b) {
  return a.currency < b.currency;
}

static bool lowCmp(Data const &a, Data const &b) { return a.low < b.low; }

static bool highCmp(Data const &a, Data const &b) { return a.high < b.high; }

static bool capitalCmp(Data const &a, Data const &b) {
  return a.capital < b.capital;
}

int main(int argc, char *argv[]) {

  vector<Data> datum_query;
  vector<Data> datum_m;
  datum_query.reserve(2000000);
  datum_m.reserve(2000000);

  // input data from file and store in datum_query
  do {
    ifstream input(argv[1]);
    for (string line; getline(input, line);) {
      Data *data = new Data();
      split(*data, line, '\t');
      datum_query.push_back(*data);
      datum_m.push_back(*data);
      delete data;
    }
  } while (0);

  // sort query
  sort(datum_query.begin(), datum_query.end(), currencyCmp);
  stable_sort(datum_query.begin(), datum_query.end(), dateCmp);
  stable_sort(datum_query.begin(), datum_query.end(), exchangeCmp);
  // sort min
  sort(datum_m.begin(), datum_m.end(), dateCmp);
  stable_sort(datum_m.begin(), datum_m.end(), currencyCmp);

  Data *tmp = new Data();

  for (string line; getline(std::cin, line);) {
    string token;
    vector<string> tokens;
    istringstream tokenStream(line);

    while (getline(tokenStream, token, '\t')) {
      tokens.push_back(token);
    }

    if (tokens[0] == "query") {
      tmp->date = tokens[1];
      tmp->currency = tokens[2];
      tmp->exchange = tokens[3];
      vector<Data>::iterator date_low, date_up;
      vector<Data>::iterator currency_low;
      vector<Data>::iterator exchange_low, exchange_up;

      exchange_low = lower_bound(datum_query.begin(), datum_query.end(), *tmp,
                                 exchangeCmp);
      exchange_up = upper_bound(datum_query.begin(), datum_query.end(), *tmp,
                                exchangeCmp);
      if (exchange_low->exchange != tmp->exchange) {
        cout << "none" << endl;
        continue;
      }
      if (exchange_low->exchange != tmp->exchange) {
        exchange_up -= 1;
      }

      // binary search lower and upper
      date_low = lower_bound(exchange_low, exchange_up, *tmp, dateCmp);
      date_up = upper_bound(exchange_low, exchange_up, *tmp, dateCmp);
      // if not find
      if (date_low->date != tmp->date) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (date_up->date != tmp->date) {
        date_up -= 1;
      }

      currency_low = lower_bound(date_low, date_up, *tmp, currencyCmp);
      if (currency_low->currency != tmp->currency) {
        cout << "none" << endl;
        continue;
      }

      int index = distance(datum_query.begin(), currency_low);
      cout << fixed << setprecision(4) << datum_query[index].low << " "
           << datum_query[index].high << " " << datum_query[index].capital
           << endl;
    } else if (tokens[0] == "price") {
      vector<Data>::iterator date_low, date_up;
      vector<Data>::iterator currency_low, currency_up;
      vector<Data>::iterator m_low, m_high; // min or max
      // arguments
      tmp->date = tokens[2];
      tmp->currency = tokens[3];

      currency_low = lower_bound(date_low, date_up, *tmp, currencyCmp);
      currency_up = upper_bound(date_low, date_up, *tmp, currencyCmp);

      // binary search lower and upper
      currency_low =
          lower_bound(datum_m.begin(), datum_m.end(), *tmp, currencyCmp);
      currency_up =
          upper_bound(datum_m.begin(), datum_m.end(), *tmp, currencyCmp);

      if (currency_low->currency != tmp->currency) {
        cout << "none" << endl;
        continue;
      }
      if (currency_up->currency != tmp->currency) {
        currency_up -= 1;
      }

      date_low = lower_bound(currency_low, currency_up, *tmp, dateCmp);
      date_up = upper_bound(currency_low, currency_up, *tmp, dateCmp);
      // if not find
      if (date_low->date != tmp->date) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (date_up->date != tmp->date) {
        date_up -= 1;
      }

      if (tokens[1] == "min") {
        sort(date_low, date_up + 1, lowCmp);
        cout << fixed << setprecision(4) << date_low->low << endl;
      } else {
        sort(date_low, date_up + 1, highCmp);
        cout << fixed << setprecision(4) << date_up->high << endl;
      }
    } else if (tokens[0] == "cap") {
      vector<Data>::iterator date_low, date_up;
      vector<Data>::iterator exchange_low, exchange_up;
      tmp->date = tokens[1];
      tmp->exchange = tokens[2];

      // binary search lower and upper
      exchange_low = lower_bound(datum_query.begin(), datum_query.end(), *tmp,
                                 exchangeCmp);
      exchange_up = upper_bound(datum_query.begin(), datum_query.end(), *tmp,
                                exchangeCmp);
      // if not find
      if (exchange_low->exchange != tmp->exchange) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (exchange_low->exchange != tmp->exchange) {
        exchange_up -= 1;
      }

      // binary search lower and upper
      date_low = lower_bound(exchange_low, exchange_up, *tmp, dateCmp);
      date_up = upper_bound(exchange_low, exchange_up, *tmp, dateCmp);
      // if not find
      if (date_low->date != tmp->date) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (date_up->date != tmp->date) {
        date_up -= 1;
      }

      long sum = 0;
      for (vector<Data>::iterator it = date_low; it <= date_up; it++) {
        sum += it->capital;
      }
      cout << sum << endl;
    } else {
      break;
    }
  }
}