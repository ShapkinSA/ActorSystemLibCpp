//
// Created by user on 21.02.24.
//

#ifndef ACTORSYSTEM_DATAEXCHANGER_H
#define ACTORSYSTEM_DATAEXCHANGER_H

#include <string>
#include <memory>
#include <any>
#include <typeindex>
#include "code/messageBox/MessageBox.h"


class DataExchanger {
public:

    DataExchanger(std::string sender, std::string receiver, const MessageBox* messageBox);
    ~DataExchanger();

public:
    std::string sender;
    std::string receiver;
    const MessageBox *messageBox = nullptr;
};

#endif //ACTORSYSTEM_DATAEXCHANGER_H
