// RUN: %clang_cc1 -std=c++11 %s -verify

namespace std {
  typedef decltype(nullptr) nullptr_t;
}

template<int *ip> struct IP {  // expected-note 2 {{template parameter is declared here}}
  IP<ip> *ip2;
};

constexpr std::nullptr_t get_nullptr() { return nullptr; }

std::nullptr_t np;

IP<0> ip0; // expected-error{{null non-type template argument must be cast to template parameter type 'int *'}}
IP<(0)> ip1; // expected-error{{null non-type template argument must be cast to template parameter type 'int *'}}
IP<nullptr> ip2;
IP<get_nullptr()> ip3;
IP<(int*)0> ip4;
IP<np> ip5;

struct X { };
template<int X::*pm> struct PM { // expected-note 2 {{template parameter is declared here}}
  PM<pm> *pm2;
};

PM<0> pm0; // expected-error{{null non-type template argument must be cast to template parameter type 'int X::*'}}
PM<(0)> pm1; // expected-error{{null non-type template argument must be cast to template parameter type 'int X::*'}}
PM<nullptr> pm2;
PM<get_nullptr()> pm3;
PM<(int X::*)0> pm4;
PM<np> pm5;

template<int (X::*pmf)(int)> struct PMF { // expected-note 2 {{template parameter is declared here}}
  PMF<pmf> *pmf2;
};

PMF<0> pmf0; // expected-error{{null non-type template argument must be cast to template parameter type 'int (X::*)(int)'}}
PMF<(0)> pmf1; // expected-error{{null non-type template argument must be cast to template parameter type 'int (X::*)(int)'}}
PMF<nullptr> pmf2;
PMF<get_nullptr()> pmf3;
PMF<(int (X::*)(int))0> pmf4;
PMF<np> pmf5;


template<std::nullptr_t np> struct NP { // expected-note 2{{template parameter is declared here}}
  NP<np> *np2;
};

NP<nullptr> np1;
NP<np> np2;
NP<get_nullptr()> np3;
NP<0> np4; // expected-error{{null non-type template argument must be cast to template parameter type 'std::nullptr_t' (aka 'nullptr_t')}}
constexpr int i = 7;
NP<i> np5; // expected-error{{non-type template argument of type 'const int' cannot be converted to a value of type 'std::nullptr_t'}}
