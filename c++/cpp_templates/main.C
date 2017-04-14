/* 
 */

#include "class_TickerBase.h"

int main()
{
  int x,y,z;
  Ticker_Thing1<int, int, int> ticker1;
  Ticker_Thing2 ticker2(x,y,z);

  ticker1.init(x,y,z);
}
