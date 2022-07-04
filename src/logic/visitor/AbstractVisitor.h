//
// Created by Mathis Saillot on 01/07/2022.
//

#ifndef HACKNSLPROJECT_ABSTRACTVISITOR_H
#define HACKNSLPROJECT_ABSTRACTVISITOR_H

template<class T>
class AbstractVisitor {
public:
    virtual void accept(const T & obj) const = 0;

    virtual ~AbstractVisitor() = default;
};

#define DECLAREVISITMETHOD(classname) virtual inline void visit(AbstractVisitor<classname> * visitor) const { \
                                   visitor->accept(*this);                                                                           \
}

#endif //HACKNSLPROJECT_ABSTRACTVISITOR_H
