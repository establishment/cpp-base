#ifndef CPPBASE_UNCOPYABLE_HPP
#define CPPBASE_UNCOPYABLE_HPP

namespace base {

class Uncopyable  {
  protected:
    Uncopyable () {}
    ~Uncopyable () {}

  private:
    Uncopyable (const Uncopyable&);
    Uncopyable& operator=(const Uncopyable &);
};

} // namespace base

#endif // CPPBASE_UNCOPYABLE_HPP
