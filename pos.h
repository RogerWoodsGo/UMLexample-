#ifndef __POS_H
#define __POS_H
#include <string>
#include <map>
#include <list>
#include <iostream>
using namespace std;
namespace pos {
enum Unit {
    RMB, DOLLAR, PONDS
};
class Money {
public:
    Money();
    Money(float ct, Unit ut);
    ~Money();
    Money& operator= (const Money& A) {
        count_ = A.count_;
        unit_ = A.unit_;
    };
    Money(const Money& A):count_(A.count_), unit_(A.unit_) {
    };
    Unit GetUnit() const;
    float GetCount() const;

private:
    float count_;
    Unit unit_;

};

class ProductDescription {
public:
    //    ProductDescription();
    ProductDescription(string desc, int id, Money pc);
    ProductDescription(const ProductDescription& A):description_(A.description_), item_id_(A.item_id_), price_(A.price_) {

    };
    ~ProductDescription();
    string GetDesc() const;
    int GetItemid() const;
    Money GetItemprice() const;

private:
    string description_;
    Money price_;
    int item_id_;
};

class SalesLineItem {
public:
    SalesLineItem();
    SalesLineItem(ProductDescription* pdsc, int qty);
    float GetSubTotal() const;
private:
    int quality_;
    ProductDescription* product_desc_;
};

class ProductCatalog {
public:
    void AddDesc(int item_id, ProductDescription* pdesc);
    ProductDescription* get_pdesc(int item_id) ;
private:
    std::map<int, ProductDescription*> item_desc_;
};

class Payment {
public:
    Payment(Money money):pay_money_(money) {};
    Money get_pay_money() const {
        return this->pay_money_;
    };
private:
    Money pay_money_;
};

class Sale {
public:
    float GetTotal();
    void MakePayment(Money pay_money);
    void MakeLineItem(ProductDescription* pdsc, int qty);
    void BecomeComplete();
    bool is_complete() const {
        return is_complete_;
    };
    Payment* get_payment() const {
        return payment_;
    };

private:
    typedef std::list<SalesLineItem*>::iterator list_it;
    bool is_complete_;
    Payment* payment_;
    std::list<SalesLineItem*> sale_items_;
};

class Register {
public:
    void CreateItemStore();
    void AddCatalog();
    void MakeNewSale();
    void EnterItem(int item_id, int qty);
    void MakePayment(Money money);
    void EndSale();
    float GetRemain() const;
    void Clear();
private:
    typedef std::list<ProductDescription*>::iterator list_it;
    Sale* sale;
    ProductCatalog* catalog;
    std::list<ProductDescription*> pdesc_storage;
};
}
#endif






