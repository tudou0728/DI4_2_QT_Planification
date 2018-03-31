#include "ttype.h"

TType::TType()
{

}

int TType::getId() const
{
    return id;
}

void TType::setId(int value)
{
    id = value;
}

QString TType::getLabel() const
{
    return label;
}

void TType::setLabel(const QString &value)
{
    label = value;
}
