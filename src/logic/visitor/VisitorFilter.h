//
// Created by Mathis Saillot on 01/07/2022.
//

#ifndef HACKNSLPROJECT_VISITORFILTER_H
#define HACKNSLPROJECT_VISITORFILTER_H

#include <AbstractVisitor.h>
#include <Station.h>
#include <Connexion.h>


template<class T, typename FILTER>
class VisitorFilter : public AbstractVisitor<T> {
protected:
    AbstractVisitor<T> * visitor_filter, * visitor_default;
    FILTER filter;
public:

    void accept(const T &obj) const override{
        obj.visit(filter(obj) ? visitor_filter : visitor_default);
    }

    virtual ~VisitorFilter() {
        delete visitor_filter;
        delete visitor_default;
    }

    VisitorFilter(AbstractVisitor<T> *visitorFilter, AbstractVisitor<T> *visitorDefault, FILTER filter)
            : visitor_filter(visitorFilter), visitor_default(visitorDefault), filter(filter) {}


};

#endif //HACKNSLPROJECT_VISITORFILTER_H