//
// Created by Mathis Saillot on 01/07/2022.
//

#include "VisitorFilter.h"

template<class T, typename FILTER>
void VisitorFilter<T, FILTER>::accept(const T &obj) const {
        obj.visit(filter(obj) ? visitor_filter : visitor_default);
}