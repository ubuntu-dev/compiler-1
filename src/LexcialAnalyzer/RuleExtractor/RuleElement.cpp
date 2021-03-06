/*
 * RuleElement.cpp
 * Created on: Mar 17, 2018
 * Author: Amr Hendy
 */

#include "../../../header/LexcialAnalyzer/RuleExtractor/RuleElement.h"

RuleElement::RuleElement(char ch,
                         Type type)
{
    // TODO Auto-generated constructor stub
    content           = ch;
    RuleElement::type = type;
}

RuleElement::~RuleElement()
{
    // TODO Auto-generated destructor stub
}

char RuleElement::getContent()
{
    return content;
}

bool RuleElement::isOperation()
{
    return type == Type::operation;
}

bool RuleElement::isAlpha()
{
    return type == Type::alpha;
}


//~ Formatted by Jindent --- http://www.jindent.com
