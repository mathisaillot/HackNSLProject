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
    FILTER * filter;
public:

    VisitorFilter(AbstractVisitor<T> *visitorFilter, AbstractVisitor<T> *visitorDefault, FILTER *filter)
            : visitor_filter(visitorFilter), visitor_default(visitorDefault), filter(filter) {}


    void accept(const T &obj) const override;
};

#endif //HACKNSLPROJECT_VISITORFILTER_H