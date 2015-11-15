#include "pos.h"
#include <iostream>

namespace pos {

Money::Money() {}


Money::Money(float ct, Unit ut) {
    this->count_ = ct;
    this->unit_ = ut;
}


Money::~Money() {
}


float Money::GetCount() const {
    return this->count_;
}

Unit Money::GetUnit() const {
    return this->unit_;
}

ProductDescription::ProductDescription(string desc, int id, Money pc):description_(desc), item_id_(id), price_(pc) {
}

ProductDescription::~ProductDescription() {}

string ProductDescription::GetDesc() const {
    return this->description_;
}

int ProductDescription::GetItemid() const {
    return this->item_id_;
}
Money ProductDescription::GetItemprice() const {
    return this->price_;
}


SalesLineItem::SalesLineItem(ProductDescription* pdsc, int qty):product_desc_(pdsc), quality_(qty) {}

float SalesLineItem::GetSubTotal() const {
    return quality_ * product_desc_->GetItemprice().GetCount();
}

void ProductCatalog::AddDesc(int item_id, ProductDescription* pdesc) {
    this->item_desc_[item_id] = pdesc;
}
ProductDescription* ProductCatalog::get_pdesc(int item_id) {
    ProductDescription* tmp = this->item_desc_[item_id];
    return tmp;
}


float Sale::GetTotal() {
    float total = 0.0;

    for(list_it it = sale_items_.begin(); it != sale_items_.end(); it++) {
        total += (*it)->GetSubTotal();
        std::cout << "total " << total << std::endl;
    }
    return total;
}
void Sale::MakePayment(Money pay_money) {
    payment_ = new Payment(pay_money);
}
void Sale::MakeLineItem(ProductDescription* pdsc, int qty) {
    SalesLineItem* tmp_sale = new SalesLineItem(pdsc, qty);
    this->sale_items_.push_back(tmp_sale);

}
void Sale::BecomeComplete() {
    is_complete_ = true;
    delete payment_;

    for(list_it it = sale_items_.begin(); it != sale_items_.end(); it++) {
        delete *it;
    }
}


void Register::AddCatalog() {
    catalog = new ProductCatalog();
    for(list_it it = pdesc_storage.begin(); it != pdesc_storage.end(); it++) {
        catalog->AddDesc((*it)->GetItemid(), (*it));
    }
}

void Register::CreateItemStore() {
    Money m1 = Money(4.0, RMB);
    Money m2 = Money(5.0, RMB);
    Money m3 = Money(6.0, RMB);
    ProductDescription* pd1 = new ProductDescription("apple", 0, m1);
    ProductDescription* pd2 = new ProductDescription("Perl", 1, m2);
    ProductDescription* pd3 = new ProductDescription("banana", 2, m3);
    pdesc_storage.push_back(pd1);
    pdesc_storage.push_back(pd2);
    pdesc_storage.push_back(pd3);
}

void Register::MakeNewSale() {
    sale = new Sale();
}

void Register::EnterItem(int item_id, int qty) {
    ProductDescription* pd = catalog->get_pdesc(item_id);
    sale->MakeLineItem(pd, qty);
}

void Register::MakePayment(Money money) {
    sale->MakePayment(money);
}

void Register::EndSale() {
    sale->BecomeComplete();
    delete sale;
}
void Register::Clear() {

    for(list_it it = pdesc_storage.begin(); it != pdesc_storage.end(); it++) {
        delete *it;
    }
    delete this->catalog;
}

float Register::GetRemain() const {
    return sale->get_payment()->get_pay_money().GetCount() - sale->GetTotal();
}

}






