#ifndef BASE_UNCOPYABLE_HPP
#define BASE_UNCOPYABLE_HPP

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

#endif // BASE_UNCOPYABLE_HPP