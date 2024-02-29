//
// Created by user on 21.02.24.
//

#ifndef ACTORSYSTEM_DATAEXCHANGER_H
#define ACTORSYSTEM_DATAEXCHANGER_H

#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <list>
#include "../messageBox/MessageBox.h"


class DataExchanger {
public:

    DataExchanger(std::string sender, const std::list<std::string> &receivers, const MessageBox* messageBox);
    ~DataExchanger();

public:
    const std::string sender;
    const std::list<std::string> receivers;
    const MessageBox *messageBox = nullptr;
};

#endif //ACTORSYSTEM_DATAEXCHANGER_H
