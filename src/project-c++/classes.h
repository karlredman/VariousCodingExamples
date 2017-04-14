//classes.h

//abstract class
class myAbstract
{
 public:
  virtual void *getData() = 0;

 private:
};

class myclass : public myAbstract
{
  public:

  myclass() :
    data(1)
    {}
    
  void *getData()
    {return &data;}

 private:
  int data;
};
