#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Data {
public:
  void setDate(string i) { date = i; }
  void setCurrency(string s) { currency = s; }
  void setExchange(string s) { exchange = s; }
  void setLow(float f) { low = f; }
  void setHigh(float f) { high = f; }
  void setCapital(long l) { capital = l; }
  string getDate() { return date; }
  string getCurrency() { return currency; }
  string getExchange() { return exchange; }
  float getLow() { return low; }
  float getHigh() { return high; }
  long getCapital() { return capital; }
  void split(const string &s, char delimiter);
  void print();
  void printInLine();

  string date;
  string currency;
  string exchange;
  float low;
  float high;
  long capital;
};

void Data::split(const string &s, char delimiter) {
  string token;
  istringstream tokenStream(s);
  int i = 0;
  while (getline(tokenStream, token, delimiter)) {
    switch (i) {
    case 0:
      setDate(token);
      break;
    case 1:
      setCurrency(token);
      break;
    case 2:
      setExchange(token);
      break;
    case 3:
      setLow(stof(token));
      break;
    case 4:
      setHigh(stof(token));
      break;
    case 5:
      setCapital(stol(token));
      break;
    default:
      break;
    }
    i++;
  }
}

void Data::print() {
  cout << fixed << setprecision(4) << "date: " << date << endl
       << "currency: " << currency << endl
       << "exchange: " << exchange << endl
       << "low: " << low << endl
       << "high: " << high << endl
       << "capital: " << capital << endl;
}

void Data::printInLine() {
  cout << fixed << setprecision(4) << "date: " << date << '\t'
       << "currency: " << currency << '\t' << "exchange: " << exchange << '\t'
       << "low: " << low << '\t' << "high: " << high << '\t'
       << "capital: " << capital << endl;
}

void printVector(vector<Data> &v) {
  for (int i = 0; i < v.size(); i++) {
    v[i].printInLine();
  }
}

bool exchangeCmp(Data const &a, Data const &b) {
  return a.exchange < b.exchange;
}

bool dateCmp(Data const &a, Data const &b) { return a.date < b.date; }

bool currencyCmp(Data const &a, Data const &b) {
  return a.currency < b.currency;
}

bool lowCmp(Data const &a, Data const &b) { return a.low < b.low; }

bool highCmp(Data const &a, Data const &b) { return a.high < b.high; }

bool capitalCmp(Data const &a, Data const &b) { return a.capital < b.capital; }

int main(int argc, char *argv[]) {

  vector<Data> datum_query;
  vector<Data> datum_min;
  vector<Data> datum_max;
  vector<Data> datum_cap;

  // input data from file and store in datum_query
  ifstream input(argv[1]);
  for (string line; getline(input, line);) {
    Data *data = new Data();
    data->split(line, '\t');
    datum_query.push_back(*data);
  }
  // copt vector to all vector
  datum_min.assign(datum_query.begin(), datum_query.end());
  datum_max.assign(datum_query.begin(), datum_query.end());
  datum_cap.assign(datum_query.begin(), datum_query.end());

  // sort query
  sort(datum_query.begin(), datum_query.end(), exchangeCmp);
  stable_sort(datum_query.begin(), datum_query.end(), currencyCmp);
  stable_sort(datum_query.begin(), datum_query.end(), dateCmp);
  // sort min
  sort(datum_min.begin(), datum_min.end(), lowCmp);
  stable_sort(datum_min.begin(), datum_min.end(), currencyCmp);
  stable_sort(datum_min.begin(), datum_min.end(), dateCmp);

  // sort max
  sort(datum_max.begin(), datum_max.end(), highCmp);
  stable_sort(datum_max.begin(), datum_max.end(), currencyCmp);
  stable_sort(datum_max.begin(), datum_max.end(), dateCmp);
  // sort cap
  sort(datum_max.begin(), datum_max.end(), exchangeCmp);
  stable_sort(datum_max.begin(), datum_max.end(), dateCmp);

  // printVector(datum_query);

  for (string line; getline(std::cin, line);) {
    Data *tmp = new Data();
    string token;
    vector<string> tokens;
    istringstream tokenStream(line);

    while (getline(tokenStream, token, '\t')) {
      tokens.push_back(token);
    }

    if (tokens[0] == "query") {
      tmp->setDate(tokens[1]);
      tmp->setCurrency(tokens[2]);
      tmp->setExchange(tokens[3]);
      vector<Data>::iterator date_low, date_up;
      vector<Data>::iterator currency_low, currency_up;
      vector<Data>::iterator exchange_low;
      // binary search lower and upper
      date_low =
          lower_bound(datum_query.begin(), datum_query.end(), *tmp, dateCmp);
      date_up =
          upper_bound(datum_query.begin(), datum_query.end(), *tmp, dateCmp);
      // if not find
      if (date_low->getDate() != tmp->getDate()) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (date_up->getDate() != tmp->getDate()) {
        date_up -= 1;
      }

      currency_low = lower_bound(date_low, date_up, *tmp, currencyCmp);
      currency_up = upper_bound(date_low, date_up, *tmp, currencyCmp);
      if (currency_low->getCurrency() != tmp->getCurrency()) {
        cout << "none" << endl;
        continue;
      }
      if (currency_up->getCurrency() != tmp->getCurrency()) {
        currency_up -= 1;
      }

      exchange_low = lower_bound(currency_low, currency_up, *tmp, exchangeCmp);
      if (exchange_low->getExchange() != tmp->getExchange()) {
        cout << "none" << endl;
        continue;
      }

      int index = distance(datum_query.begin(), exchange_low);
      cout << fixed << setprecision(4) << datum_query[index].getLow() << " "
           << datum_query[index].getHigh() << " "
           << datum_query[index].getCapital() << endl;
    } else if (tokens[0] == "price") {
      vector<Data> vd;
      vector<Data>::iterator date_low, date_up;
      vector<Data>::iterator currency_low, currency_up;
      vector<Data>::iterator m_low, m_high; // min or max
      // arguments
      tmp->setDate(tokens[2]);
      tmp->setCurrency(tokens[3]);
      if (tokens[1] == "min") {
        vd = datum_min;
      } else {
        vd = datum_max;
      }
      // binary search lower and upper
      date_low = lower_bound(vd.begin(), vd.end(), *tmp, dateCmp);
      date_up = upper_bound(vd.begin(), vd.end(), *tmp, dateCmp);
      // if not find
      if (date_low->getDate() != tmp->getDate()) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (date_up->getDate() != tmp->getDate()) {
        date_up -= 1;
      }

      currency_low = lower_bound(date_low, date_up, *tmp, currencyCmp);
      currency_up = upper_bound(date_low, date_up, *tmp, currencyCmp);
      if (currency_low->getCurrency() != tmp->getCurrency()) {
        cout << "none" << endl;
        continue;
      }
      if (currency_up->getCurrency() != tmp->getCurrency()) {
        currency_up -= 1;
      }

      if (tokens[1] == "min") {
        m_low = lower_bound(currency_low, currency_up, *tmp, lowCmp);
        cout << fixed << setprecision(4) << m_low->getLow() << endl;
      } else {
        m_high = upper_bound(currency_low, currency_up, *tmp, highCmp);
        cout << fixed << setprecision(4) << m_high->getHigh() << endl;
      }
    } else if (tokens[0] == "cap") {
      vector<Data>::iterator date_low, date_up;
      vector<Data>::iterator exchange_low, exchange_up;
      tmp->setDate(tokens[1]);
      tmp->setExchange(tokens[2]);

      // binary search lower and upper
      date_low = lower_bound(datum_cap.begin(), datum_cap.end(), *tmp, dateCmp);
      date_up = upper_bound(datum_cap.begin(), datum_cap.end(), *tmp, dateCmp);
      // if not find
      if (date_low->getDate() != tmp->getDate()) {
        cout << "none" << endl;
        continue;
      }
      // check the upper bound
      if (date_up->getDate() != tmp->getDate()) {
        date_up -= 1;
      }

      exchange_low = lower_bound(date_low, date_up, *tmp, exchangeCmp);
      exchange_up = upper_bound(date_low, date_up, *tmp, exchangeCmp);
      if (exchange_low->getExchange() != tmp->getExchange()) {
        cout << "none" << endl;
        continue;
      }
      long sum = 0;
      for (vector<Data>::iterator it = exchange_low; it <= exchange_up; it++) {
        sum += it->getCapital();
      }
      cout << sum << endl;
    } else {
      break;
    }
  }
}