#ifndef ITERATOR_H
#define ITERATOR_H

struct sol_Iter {
  void *(*next)(void *);
};

#endif
