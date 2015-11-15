#include "pos.h"
#include <iostream>

//namespace pos {
using std::endl;
using namespace pos;
int main(){
//    Money book_price(10,RMB);
//    ProductDescription* pd = new ProductDescription("this is book", 1212, book_price);
////    cout << book_price.GetCount() << endl;
//    cout << pd->GetDesc() << endl;
//    SalesLineItem *sl = new SalesLineItem(pd, 3);
//    std::cout << sl->GetSubTotal() << endl;
//    delete pd;
//    delete sl;
    Register* reg = new Register();
    reg->CreateItemStore();
    reg->AddCatalog();
    reg->MakeNewSale();
    reg->EnterItem(0, 3);
//    Money* m = new Money(100, RMB);
    Money m(100, RMB);
    reg->MakePayment(m);
    float rem = reg->GetRemain();
    std::cout << "Remain " << rem << std::endl; 
    reg->EndSale();
//    delete m;
    delete reg;
    return 0;
}
//}

