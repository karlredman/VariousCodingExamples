/* class_TickerBase.h
   Abstract base class for Tickers
 */

//an abstract template class
template <class T1, class T2, class T3>
class TickerBase 
{
 public:

  virtual void init(T1 raw_tick, T2 feed, T3 msms) = 0;
  //virtual int get_feed_data() = 0;
  //virtual int convert_data() = 0;
  //virtual int save_raw_tick() = 0;
  //virtual int send_tick() = 0;
  //virtual int get_tick() = 0;
  //virtual int connect() = 0;

 protected:
  T1 RawTick;
  T2 Feed;
  T3 MSMS;
};

//a template instantiation of a template class
template <class T1, class T2, class T3>
class Ticker_Thing1 : public TickerBase <T1, T2, T3>
{
 public:

  //an init function from the base class
  void init(T1 raw_tick, T2 feed, T3 msms)
    { RawTick = raw_tick; }

 private:
  
};

//a class instantiation from a template base class
class Ticker_Thing2 : public TickerBase <int, int, int>
{
 public:

  //a constructor that sets init
  Ticker_Thing2 (int raw_tick, int feed, int msms)
    { init(raw_tick, feed, msms); }

  //this must be defined via the base class
  void init(int raw_tick, int feed, int msms)
    {}

 private:
  
};
